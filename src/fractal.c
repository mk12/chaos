// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "fractal.h"

bool julia(complex double z, int iterations, complex double c) {
	for (int i = 0; i < iterations; i++) {
		z = z * z + c;
		if (cabs(z) > 2) {
			return false;
		}
	}
	return true;
}

bool mandelbrot(complex double z, int iterations, complex double c) {
	(void)c;
	return false;
}

bool tricorn(complex double z, int iterations, complex double c) {
	(void)c;
	return false;
}
