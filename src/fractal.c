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

bool mandelbrot(complex double c, int iterations, complex double arg) {
	(void)arg;
	complex double z = 0;
	for (int i = 0; i < iterations; i++) {
		z = z * z + c;
		if (cabs(z) > 2) {
			return false;
		}
	}
}

bool tricorn(complex double c, int iterations, complex double arg) {
	(void)arg;
	complex double z = 0;
	for (int i = 0; i < iterations; i++) {
		complex double cz = conj(z);
		z = cz * cz + c;
		if (cabs(z) > 2) {
			return false;
		}
	}
}
