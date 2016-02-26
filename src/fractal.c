// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "fractal.h"

double julia(complex double z, complex double c, double escape, int iters) {
	double x = exp(-cabs(z));
	for (int i = 0; i < iters; i++) {
		z = z * z + c;
		x += exp(-cabs(z));
	}
	return x / iters;
}

// Returns a smooth value on [0,1] for a Mandelbrot or Tricorn unbouded orbit
// that reaches a complex value with modulus 'mod' on the nth iteration.
static double mandel_smooth(double mod, int n) {
	return n + 1 - log2(mod);
}

double mandelbrot(complex double c, complex double, double escape, int iters) {
	complex double z = 0;
	for (int i = 0; i < iters; i++) {
		z = z * z + c;
		double mod = cabs(z);
		if (mod > escape) {
			return mandel_smooth(mod, i);
		}
	}
	return 0;
}

double tricorn(complex double c, complex double, double escape, int iters) {
	complex double z = 0;
	for (int i = 0; i < iters; i++) {
		complex double cz = conj(z);
		z = cz * cz + c;
		double mod = cabs(z);
		if (mod > escape) {
			return mandel_smooth(mod);
		}
	}
	return 0;
}
