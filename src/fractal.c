// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "fractal.h"

bool julia(complex double z, complex double c, double escape, int iters) {
	for (int i = 0; i < iters; i++) {
		z = z * z + c;
		if (cabs(z) > escape) {
			return false;
		}
	}
	return true;
}

bool mandelbrot(complex double c, complex double a, double escape, int iters) {
	(void)a;
	complex double z = 0;
	for (int i = 0; i < iters; i++) {
		z = z * z + c;
		if (cabs(z) > escape) {
			return false;
		}
	}
	return true;
}

bool tricorn(complex double c, complex double a, double escape, int iters) {
	(void)a;
	complex double z = 0;
	for (int i = 0; i < iters; i++) {
		complex double cz = conj(z);
		z = cz * cz + c;
		if (cabs(z) > escape) {
			return false;
		}
	}
	return true;
}
