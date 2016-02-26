// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "color.h"

#include <math.h>

void alpha(FILE *out, double v) {
	unsigned char g = (unsigned char)(v * 255 + 0.5);
	putc(g, out);
	putc(g, out);
	putc(g, out);
}
