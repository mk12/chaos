// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "plot.h"

#include "fractal.h"

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

int plot(const struct Parameters *params) {
	FractalFn in_fractal = lookup_fractal(params->name);
	if (!in_fractal) {
		printf_error("%c: invalid fractal name", params->name);
		return 1;
	}
}
