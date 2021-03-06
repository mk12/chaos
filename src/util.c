// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "util.h"

#include <stdarg.h>
#include <stdlib.h>

// The name of the program.
static const char *program_name = NULL;

void setup_util(const char *the_program_name) {
	program_name = the_program_name;
}

void printf_error(const char *format, ...)
	__attribute__((__format__ (__printf__, 1, 2)));
void printf_error(const char *format, ...) {
	va_list args;
	va_start(args, format);
	fprintf(stderr, "%s: ", program_name);
	vfprintf(stderr, format, args);
	putc('\n', stderr);
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
