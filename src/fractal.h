// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#ifndef FRACTAL_H
#define FRACTAL_H

#include <complex.h>
#include <stdbool.h>

// A fractal function takes a complex input and returns a smooth value on [0,1].
// It returns 0 if the input is in the fractal set. The function also takes
// additional parameters: a complex constant (used only by Julia), the escape
// threshold used for determining if an orbit is bounded, and the number of
// iterations to perform.
typedef double (*FractalFn)(complex double, complex double, double, int);

// Fractal function for the Julia set for a particular constant 'c'.
double julia(complex double z, complex double c, double escape, int iters);

// Fractal function for the Madelbrot set.
bool mandelbrot(complex double z, complex double, double escape, int iters);

// Fractal function for the Tricorn set (also called the Mandelbar set).
bool tricorn(complex double z, complex double, double escape, int iters);

#endif
