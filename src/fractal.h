// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#ifndef FRACTAL_H
#define FRACTAL_H

// A fractal function tests whether a point is in a fractal set, given an
// integer number of iterations to perform and some other data.
typedef bool (*FractalFn)(complex double, int, void *);

bool julia(complex double z, int iterations, complex double *c);

bool mandelbrot(complex double z, int iterations, void *);

bool tricorn(complex double z, int iterations, void *);

#endif
