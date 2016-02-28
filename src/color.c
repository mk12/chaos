// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "color.h"

#include <math.h>

// Applies sRGB gamma encoding and converts to an 8-bit value.
static unsigned char srgb(double x) {
	if (x < 0.0031308) {
		x *= 12.92;
	} else {
		x = (1 + 0.055) * pow(x, 1 / 2.4) - 0.055;
	}
	return (unsigned char)(x * 255 + 0.5);
}

void grayscale(unsigned char *out, double v) {
	unsigned char g = srgb(v);
	out[0] = g;
	out[1] = g;
	out[2] = g;
}
