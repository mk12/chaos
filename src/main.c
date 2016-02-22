// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "plot.h"
#include "util.h"

#include <stdio.h>
#include <unistd.h>

// The usage message for the program.
static const char *usage_msg =
	"[-n name] [-x origin_x] [-y origin_y] [-s scale] [-i iterations]"
	" [-w width] [-h height] [-o file] [c]";

int main(int argc, char **argv) {
	setup_util(argv[0], usage_msg);

	// Initialize the default parameters.
	struct Parameters params = {
		.name = 'j',
		.cx = 0,
		.cy = 0,
		.scale = 1,
		.iterations = 1,
		.width = 500,
		.height = 500,
		.ofile = "chaos.ppm",
		.n_args = 0,
		.args = NULL
	};

	// Get command line options.
	int c;
	extern char *optarg;
	extern int optind, optopt;
	while ((c = getopt(argc, argv, "hn:x:y:s:i:w:h:o:")) != -1) {
		switch (c) {
		case 'h':
			print_usage(stdout);
			return 0;
		case 'n':
			params.name = *optarg;
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
		case 'i':
			if (!parse_int(&params.iterations, optarg)) {
				return 1;
			}
			break;
		case 'w':
			if (!parse_int(&params.width, optarg)) {
				return 1;
			}
			break;
		case 'h':
			if (!parse_int(&params.height, optarg)) {
				return 1;
			}
			break;
		case 'o':
			params.ofile = optarg;
			break;
		case '?':
			print_usage(stderr);
			return 1;
		}
	}
	params.n_args = argc - optind;
	params.args = argv + optind;
	return plot(params);
}
