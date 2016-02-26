// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "plot.h"
#include "util.h"

#include <stdio.h>
#include <unistd.h>

// The usage message for the program.
static const char *usage_msg =
	"[-n name] [-a A] [-b B] [-x centre_x] [-y centre_y] [-s scale] [-e escape]"
	" [-i iterations] [-w width] [-h height] [-c color_scheme] [-o file]";

int main(int argc, char **argv) {
	setup_util(argv[0], usage_msg);

	// Initialize the default parameters.
	struct Parameters params = {
		.name = 'j',
		.a = 0,
		.b = 0,
		.cx = 0,
		.cy = 0,
		.scale = 1,
		.escape = 2,
		.iterations = 1000,
		.width = 500,
		.height = 500,
		.color_scheme = 'a',
		.ofile = "chaos.ppm"
	};

	// Get command line options.
	int c;
	extern char *optarg;
	extern int optind, optopt;
	while ((c = getopt(argc, argv, "n:a:b:x:y:s:e:i:w:h:c:o:")) != -1) {
		switch (c) {
		case 'n':
			params.name = *optarg;
			break;
		case 'a':
			if (!parse_double(&params.a, optarg)) {
				return 1;
			}
			break;
		case 'b':
			if (!parse_double(&params.b, optarg)) {
				return 1;
			}
			break;
		case 'x':
			if (!parse_double(&params.cx, optarg)) {
				return 1;
			}
			break;
		case 'y':
			if (!parse_double(&params.cy, optarg)) {
				return 1;
			}
			break;
		case 's':
			if (!parse_double(&params.scale, optarg)) {
				return 1;
			}
			break;
		case 'e':
			if (!parse_double(&params.escape, optarg)) {
				return 1;
			}
			break;
		case 'i':
			if (!parse_int(&params.iterations, optarg)) {
				return 1;
			}
			if (params.iterations <= 0) {
				printf_error("%s: iterations must be positive", optarg);
				return 1;
			}
			break;
		case 'w':
			if (!parse_int(&params.width, optarg)) {
				return 1;
			}
			if (params.width <= 0) {
				printf_error("%s: width must be positive", optarg);
				return 1;
			}
			break;
		case 'h':
			if (!parse_int(&params.height, optarg)) {
				return 1;
			}
			if (params.height <= 0) {
				printf_error("%s: height must be positive", optarg);
				return 1;
			}
			break;
		case 'c':
			params.color_scheme = *optarg;
			break;
		case 'o':
			params.ofile = optarg;
			break;
		case '?':
			print_usage(stderr);
			return 1;
		}
	}
	// Make sure all arguments were processed.
	if (optind != argc) {
		print_usage(stderr);
		return 1;
	}

	return plot(&params);
}
