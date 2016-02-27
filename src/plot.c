// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "plot.h"

#include "color.h"
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
	case 'J':
		return julia;
	case 'm':
	case 'M':
		return mandelbrot;
	case 't':
	case 'T':
		return tricorn;
	default:
		return NULL;
	}
}

// Looks up a color scheme function by name. Returns NULL if it cannot be found.
static ColorFn lookup_color_scheme(char name) {
	switch (name) {
	case 'a':
	case 'A':
		return alpha;
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
	double real = nx / params->scale + params->cx;
	double imag = -ny / params->scale + params->cy;
	return real + imag * I;
}

int plot(const struct Parameters *params) {
	// Look up the fractal function.
	FractalFn fractal_fn = lookup_fractal(params->name);
	if (!fractal_fn) {
		printf_error("%c: invalid fractal name", params->name);
		return 1;
	}

	// Look up the color scheme function.
	ColorFn color_fn = lookup_color_scheme(params->color_scheme);
	if (!fractal_fn) {
		printf_error("%c: invalid color scheme name", params->color_scheme);
		return 1;
	}

	// Open the file for writing.
	FILE *file = fopen(params->ofile, "w");
	if (!file) {
		printf_error("%s: %s", params->ofile, strerror(errno));
		return 1;
	}

	// Write the PPM header.
	fprintf(file, "P6 %d %d 255\n", params->width, params->height);

	// Calculate and write the pixel values.
	complex double c = params->a + params->b * I;
	for (int y = 0; y < params->height; y++) {
		for (int x = 0; x < params->width; x++) {
			complex double z = pixel_to_point(x, y, params);
			double v = fractal_fn(z, c, params->escape, params->iterations);
			color_fn(file, v);
		}
	}

	fclose(file);
	return 0;
}
