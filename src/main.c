// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// String constants.
static const char *prog_name; // set in main
static const char *const usage_msg =
	"usage: chaos [-a A] [-b B] [-s size] [-o file]\n";

// Default parameter values.
static const double default_a = -0.687;
static const double default_b = 0.312;
static const int default_size = 500;
static const char *default_ofile = "chaos.ppm";

// Parse a string as an int. Exits on failure.
static int parse_int(const char *str) {
	char *end;
	int n = (int)strtol(str, &end, 0);
	if (*end) {
		fprintf(stderr, "%s: %s: not an integer\n", prog_name, str);
		exit(1);
	}
	return n;
}

// Parse a string as a double. Exits on failure.
static double parse_double(const char *str) {
	char *end;
	double d = strtod(str, &end);
	if (*end) {
		fprintf(stderr, "%s: %s: not a number\n", prog_name, str);
		exit(1);
	}
	return d;
}

int main(int argc, char **argv) {
	// Set the program name to be used in error messages.
	prog_name = argv[0];

	// Initialize parameters to default values.
	double a = default_a;
	double b = default_b;
	int size = default_size;
	const char *ofile = default_ofile;

	// Get command line options.
	int c;
	extern char *optarg;
	extern int optind, optopt;
	while ((c = getopt(argc, argv, "ha:b:s:o:")) != -1) {
		switch (c) {
		case 'h':
			fputs(usage_msg, stdout);
			return 0;
		case 'a':
			a = parse_double(optarg);
			break;
		case 'b':
			b = parse_double(optarg);
			break;
		case 's':
			size = parse_int(optarg);
			break;
		case 'o':
			ofile = optarg;
			break;
		}
	}
	// Make sure all arguments were processed.
	if (optind != argc) {
		fputs(usage_msg, stderr);
		return 1;
	}

	// Print the c-value.
	printf("%f + %fi\n", a, b);
	return 0;
}
