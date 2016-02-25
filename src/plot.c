// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "plot.h"

#include "fractal.h"
#include "util.h"

#include <complex.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Looks up a fractal function by name. Returns NULL if it cannot be found.
static FractalFn lookup_fractal(char name) {
	switch (name) {
	case 'j':
		return julia;
	case 'm':
		return mandelbrot;
	case 't':
		return tricorn;
	default:
		return NULL;
	}
}

// Converts a pixel to a point for the viewport defined by the parameters.
static complex double pixel_to_point(
		int x, int y, const struct Parameters *params) {
	double hw = params->width / 2.0;
	double hh = params->height / 2.0;
	double nx = (x + 0.5 - hw) / hw;
	double ny = (y + 0.5 - hh) / hh;
	double real = nx * params->scale;
	double imag = -ny * params->scale;
	return real + imag * I;
}

int plot(const struct Parameters *params) {
	FractalFn in_fractal = lookup_fractal(params->name);
	if (!in_fractal) {
		printf_error("%c: invalid fractal name", params->name);
		return 1;
	}

	FILE *file = fopen(params->ofile, "w");
	if (!file) {
		printf_error("%s: %s", params->ofile, strerror(errno));
		return 1;
	}

	fprintf(file, "P6 %d %d 255\n", params->width, params->height);

	complex double c = params->a + params->b * I;
	for (int y = 0; y < params->height; y++) {
		for (int x = 0; x < params->width; x++) {
			complex double z = pixel_to_point(x, y, params);
			if (in_fractal(z, c, params->escape, params->iterations)) {
				putc(0, file);
				putc(0, file);
				putc(0, file);
			} else {
				putc(255, file);
				putc(255, file);
				putc(255, file);
			}
		}
	}

	fclose(file);
	return 0;
}
