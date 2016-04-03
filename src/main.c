// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "plot.h"
#include "util.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Maximum values for some parameters.
#define MAX_WIDTH 10000
#define MAX_HEIGHT 10000
#define MAX_JOBS 64

// The usage message for the program.
static const char *const usage_message =
	"usage: chaos [options]\n"
	"\n"
	"  Default\n"
	"    chaos -n j -a 0 -b 0\n"
	"          -x 0 -y 0 -s 1 -e 2 -i 1000\n"
	"          -w 500 -h 500 -c g -p 1 -j 1 -o chaos.ppm\n"
	"\n"
	"  Fractal\n"
	"    -n  Fractal name: j/m/t for Julia/Mandelbrot/Tricorn\n"
	"    -a  (Julia only) Real part of the constant c\n"
	"    -b  (Julia only) Imaginary part of the constant c\n"
	"\n"
	"  Settings\n"
	"    -x  X-component of the centre of the viewport\n"
	"    -y  Y-component of the centre of the viewport\n"
	"    -s  Scale factor of the viewport\n"
	"    -e  Escape threshold for determing if an orbit is unbounded\n"
	"    -i  Integer number of iterations to perform\n"
	"\n"
	"  Output\n"
	"    -w  Width of the output image in pixels\n"
	"    -h  Height of the output image in pixels\n"
	"    -c  Color scheme: g/r for grayscale/rainbow\n"
	"    -p  Power for the smooth value\n"
	"    -j  Number of jobs to run in parallel\n"
	"    -o  Output filename\n"
	"\n";

int main(int argc, char **argv) {
	setup_util(argv[0]);
	if (argc == 2 && strcmp(argv[1], "--help") == 0) {
		fputs(usage_message, stdout);
		return 0;
	}

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
		.color_scheme = 'g',
		.power = 1,
		.jobs = 1,
		.ofile = "chaos.ppm"
	};

	// Get command line options.
	int c;
	extern char *optarg;
	extern int optind, optopt;
	while ((c = getopt(argc, argv, "n:a:b:x:y:s:e:i:w:h:c:p:j:o:")) != -1) {
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
			if (params.width > MAX_WIDTH) {
				printf_error("%s: width too large (maximum %d)",
						optarg, MAX_WIDTH);
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
			if (params.height > MAX_HEIGHT) {
				printf_error("%s: height too large (maximum %d)",
						optarg, MAX_HEIGHT);
				return 1;
			}
			break;
		case 'c':
			params.color_scheme = *optarg;
			break;
		case 'p':
			if (!parse_double(&params.power, optarg)) {
				return 1;
			}
			break;
		case 'j':
			if (!parse_int(&params.jobs, optarg)) {
				return 1;
			}
			if (params.jobs <= 0) {
				printf_error("%s: jobs must be positive", optarg);
				return 1;
			}
			if (params.jobs > MAX_JOBS) {
				printf_error("%s: too many jobs (maximum %d)",
						optarg, MAX_JOBS);
				return 1;
			}
			break;
		case 'o':
			params.ofile = optarg;
			break;
		case '?':
			fputs(usage_message, stderr);
			return 1;
		}
	}
	// Make sure all arguments were processed.
	if (optind != argc) {
		fputs(usage_message, stderr);
		return 1;
	}

	return plot(&params);
}
