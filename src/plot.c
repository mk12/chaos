// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "plot.h"

#include "color.h"
#include "fractal.h"
#include "util.h"

#include <complex.h>
#include <errno.h>
#include <stdbool.h>
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

// Writes a PPM image to the output file specified in 'params'. Expects 'raster'
// to be an array of 'size' bytes in row-major RGB format. Returns true on
// success; prints an error message and returns false on failure.
static bool write_ppm(
		unsigned char *raster, size_t size, const struct Parameters *params) {
	FILE *file = fopen(params->ofile, "w");
	if (!file) {
		goto error;
	}
	if (fprintf(file, "P6 %d %d 255\n", params->width, params->height) < 0) {
		fclose(file);
		goto error;
	}
	if (fwrite(raster, 1, size, file) != size) {
		fclose(file);
		goto error;
	}
	fclose(file);
	return true;

error:
	printf_error("%s: %s", params->ofile, strerror(errno));
	return false;
}

int plot(const struct Parameters *params) {
	FractalFn fractal_fn = lookup_fractal(params->name);
	if (!fractal_fn) {
		printf_error("%c: invalid fractal name", params->name);
		return 1;
	}
	ColorFn color_fn = lookup_color_scheme(params->color_scheme);
	if (!fractal_fn) {
		printf_error("%c: invalid color scheme name", params->color_scheme);
		return 1;
	}

	size_t bufsize = (size_t)(params->width * params->height * 3);
	unsigned char *buf = malloc(bufsize);
	unsigned char *pixel = buf;

	complex double c = params->a + params->b * I;
	for (int y = 0; y < params->height; y++) {
		for (int x = 0; x < params->width; x++) {
			complex double z = pixel_to_point(x, y, params);
			double v = fractal_fn(z, c, params->escape, params->iterations);
			color_fn(pixel, v);
			pixel += 3;
		}
	}
	return write_ppm(buf, bufsize, params) ? 0 : 1;
}
