// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

// A color scheme function takes an output stream and a smooth value on [0,1].
// It writes an RGB pixel (3 bytes) to the output stream.
typedef void (*ColorFn)(FILE *, double);

// The alpha color scheme function.
void alpha(FILE *out, double v);

#endif
