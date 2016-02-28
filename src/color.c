// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "color.h"

#include <math.h>

// Rainbow color scheme saturation and value.
#define RAINBOW_SAT 0.8
#define RAINBOW_VAL 0.7

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

// Converts an HSV color to RGB and writes it to the output location with sRGB
// encoding. Assumes 'h', 's', and 'v' are on the interval [0,1].
static void hsv(unsigned char *out, double h, double s, double v) {
	static int map[6][3] = {
		{0, 3, 1}, {2, 0, 1}, {1, 0, 3}, {1, 2, 0}, {3, 1, 0}, {0, 1, 2}
	};

	double h6 = h * 6;
	double f = h6 - (int)h6;
	double vars[4] = {
		v,
		v * (1 - s),
		v * (1 - (s * f)),
		v * (1 - (s * (1 - f)))
	};
	int i = ((int)h6 % 6 + 6) % 6;
	out[0] = srgb(vars[map[i][0]]);
	out[1] = srgb(vars[map[i][1]]);
	out[2] = srgb(vars[map[i][2]]);
}

void rainbow(unsigned char *out, double v) {
	if (v <= 0 || !isfinite(v)) {
		out[0] = 0;
		out[1] = 0;
		out[2] = 0;
	} else {
		hsv(out, v, RAINBOW_SAT, RAINBOW_VAL);
	}
}
