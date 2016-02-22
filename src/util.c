// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "util.h"

#include <stdlib.h>

// The name of the program.
static const char *program_name = NULL;

// The part of the usage message that lists the arguments.
static const char *usage_msg = NULL;

void setup_util(const char *p, const char *u) {
	program_name = p;
	usage_msg = u;
}

void print_usage(FILE *out) {
	fprintf(out, "usage: %s %s\n", program_name, usage_message);
}

void printf_error(const char *format, ...) {
	va_list args;
	va_start(args, format);
	fprintf(stderr, "%s: ", program_name);
	vfprintf(stderr, format, args);
	va_end(args);
}

bool parse_int(int *out, const char *str) {
	char *end;
	int n = (int)strtol(str, &end, 0);
	if (*end) {
		printf_error("%s: not an integer", str);
		return false;
	}
	*out = n;
	return true;
}

bool parse_double(double *out, const char *str) {
	char *end;
	double d = strtod(str, &end);
	if (*end) {
		printf_error("%s: not a number", str);
		return false;
	}
	*out = d;
	return true;
}
