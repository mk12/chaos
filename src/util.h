// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>
#include <stdio.h>

// Performs necessary setup. Must be called once when the program starts.
void setup_util(const char *program_name, const char *usage_msg);

// Prints the usage message to the given output stream.
void print_usage(FILE *out);

// Prints an error message to stderr with printf syntax.
void printf_error(const char *format, ...);

// Parses a string as an int. Stores the result in 'out' and returns true on
// success; prints an error message and returns false on failure.
bool parse_int(int *out, const char *str);

// Parses a string as double. Stores the result in 'out' and returns true on
// success; prints an error message and returns false on failure.
bool parse_double(double *out, const char *str);

#endif
