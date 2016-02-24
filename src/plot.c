// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "plot.h"

#include "fractal.h"
#include "util.h"

#include <complex.h>
#include <stdlib.h>

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
	return 0;
}
