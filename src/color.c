// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "color.h"

void alpha(FILE *out, double v) {
	if (v < 0.5) {
		putc(0, out);
		putc(0, out);
		putc(0, out);
	} else {
		putc(255, out);
		putc(255, out);
		putc(255, out);
	}
}
