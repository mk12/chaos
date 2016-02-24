// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#ifndef FRACTAL_H
#define FRACTAL_H

#include <complex.h>
#include <stdbool.h>

// A fractal function tests whether a point is in a fractal set, given the point
// as a complex value, a complex constant (only used by Julia), the escape
// threshold used for determining if an orbit is bounded, and an integer number
// of iterations to perform.
typedef bool (*FractalFn)(complex double, complex double, double, int);

// Returns true if 'z' is in the Julia set for constant 'c'.
bool julia(complex double z, complex double c, double escape, int iters);

// Returns true if 'z' is in the Mandelbrot set.
bool mandelbrot(complex double c, complex double, double escape, int iters);

// Returns true if 'z' is in the Tricorn set.
bool tricorn(complex double c, complex double, double escape, int iters);

#endif
