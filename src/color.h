// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

// A color scheme function takes an output location and a smooth value on [0,1].
// It writes an RGB pixel (3 bytes) to the output location.
typedef void (*ColorFn)(unsigned char *, double);

// A grayscale color scheme.
void grayscale(unsigned char *out, double v);

#endif
