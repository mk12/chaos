// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#ifndef FRACTAL_H
#define FRACTAL_H

#include <complex.h>
#include <stdbool.h>

// A fractal function tests whether a point is in a fractal set, given an
// integer number of iterations to perform and a complex parameter.
typedef bool (*FractalFn)(complex double, int, complex double);

// Returns true if 'z' is in the Julia set for constant 'c'.
bool julia(complex double z, int iterations, complex double c);

// Returns true if 'z' is in the Mandelbrot set.
bool mandelbrot(complex double c, int iterations, complex double);

// Returns true if 'z' is in the Tricorn set.
bool tricorn(complex double c, int iterations, complex double);

#endif
