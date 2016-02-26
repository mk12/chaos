// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "fractal.h"

#include <math.h>

double julia(complex double z, complex double c, double escape, int iters) {
	(void)escape;
	double x = exp(-cabs(z));
	for (int i = 0; i < iters; i++) {
		z = z * z + c;
		x += exp(-cabs(z));
	}
	return x / iters;
}

double mandelbrot(
		complex double c, complex double unused, double escape, int iters) {
	(void)unused;
	complex double z = 0;
	for (int i = 0; i < iters; i++) {
		z = z * z + c;
		double mod = cabs(z);
		if (mod > escape) {
			return (i + 1 - log2(log(mod))) / iters;
		}
	}
	return 0;
}

double tricorn(
		complex double c, complex double unused, double escape, int iters) {
	(void)unused;
	complex double z = 0;
	for (int i = 0; i < iters; i++) {
		complex double cz = conj(z);
		z = cz * cz + c;
		double mod = cabs(z);
		if (mod > escape) {
			return (i + 1 - log2(log(mod))) / iters;
		}
	}
	return 0;
}
