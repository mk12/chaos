// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#include "plot.h"

#include "color.h"
#include "fractal.h"
#include "util.h"

#include <complex.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A Task specifies a set of rows to plot. Performing a Task consists of writing
// 'height' rows to the raster buffer, beginning at row index 'y', using the
// fractal function 'compute' and color scheme function 'write'.
struct Task {
	FractalFn compute;
	ColorFn write;
	int y, height;
	unsigned char *raster;
	const struct Parameters *params;
};

// Looks up a fractal function by name. Returns NULL if it cannot be found.
static FractalFn lookup_fractal(char name) {
	switch (name) {
	case 'j':
	case 'J':
		return julia;
	case 'm':
	case 'M':
		return mandelbrot;
	case 't':
	case 'T':
		return tricorn;
	default:
		return NULL;
	}
}

// Looks up a color scheme function by name. Returns NULL if it cannot be found.
static ColorFn lookup_color_scheme(char name) {
	switch (name) {
	case 'g':
	case 'G':
		return grayscale;
	case 'r':
	case 'R':
		return rainbow;
	default:
		return NULL;
	}
}

// Converts a pixel to a point for the viewport defined by the parameters.
static complex double pixel_to_point(
		int x, int y, const struct Parameters *params) {
	double hw = params->width / 2.0;
	double hh = params->height / 2.0;
	double divisor = hh;
	double nx = (x + 0.5 - hw) / divisor;
	double ny = (y + 0.5 - hh) / divisor;
	double real = nx / params->scale + params->cx;
	double imag = -ny / params->scale + params->cy;
	return real + imag * I;
}

// Writes a PPM image to the output file specified in 'params'. Expects 'raster'
// to be an array of 'size' bytes in row-major RGB format. Returns true on
// success; prints an error message and returns false on failure.
static bool write_ppm(
		unsigned char *raster, size_t size, const struct Parameters *params) {
	FILE *file = fopen(params->ofile, "w");
	if (!file) {
		goto error;
	}
	if (fprintf(file, "P6 %d %d 255\n", params->width, params->height) < 0) {
		fclose(file);
		goto error;
	}
	if (fwrite(raster, 1, size, file) != size) {
		fclose(file);
		goto error;
	}
	fclose(file);
	return true;

error:
	printf_error("%s: %s", params->ofile, strerror(errno));
	return false;
}

// Performs the Task 'arg'. Always returns NULL.
static void *perform_task(void *arg) {
	const struct Task *task = (struct Task *)arg;
	const struct Parameters *params = task->params;

	int end_y = task->y + task->height;
	unsigned char *out = task->raster + task->y * params->width * 3;
	complex double c = params->a + params->b * I;
	for (int y = task->y; y < end_y; y++) {
		for (int x = 0; x < params->width; x++) {
			complex double z = pixel_to_point(x, y, params);
			double v = task->compute(z, c, params->escape, params->iterations);
			task->write(out, pow(v, params->power));
			out += 3;
		}
	}
	return NULL;
}

// Breaks 'task' into 'n' subtasks and performs them in parallel. Returns true
// on success; prints an error message and returns false on failure. Waits for
// all subtask threads to terminate before returning.
static bool perform_in_parallel(const struct Task *task, int n) {
	pthread_t threads[n];
	struct Task subtasks[n];
	int height = task->params->height / n;
	int extra = task->params->height % n;

	for (int i = 0; i < n; i++) {
		subtasks[i] = *task;
		subtasks[i].y = i * height;
		subtasks[i].height = i == n - 1 ? height + extra : height;
		int err = pthread_create(&threads[i], NULL, perform_task, &subtasks[i]);
		if (err != 0) {
			printf_error("error creating thread #%d: %s", i, strerror(err));
			return false;
		}
	}
	for (int i = 0; i < n; i++) {
		int err = pthread_join(threads[i], NULL);
		if (err != 0) {
			printf_error("error joining thread #%d: %s", i, strerror(err));
			return false;
		}
	}
	return true;
}

int plot(const struct Parameters *params) {
	FractalFn fractal_fn = lookup_fractal(params->name);
	if (!fractal_fn) {
		printf_error("%c: invalid fractal name", params->name);
		return 1;
	}
	ColorFn color_fn = lookup_color_scheme(params->color_scheme);
	if (!color_fn) {
		printf_error("%c: invalid color scheme name", params->color_scheme);
		return 1;
	}

	size_t size = (size_t)(params->width * params->height * 3);
	unsigned char *raster = malloc(size);
	struct Task task = {
		.compute = fractal_fn,
		.write = color_fn,
		.y = 0,
		.height = params->height,
		.raster = raster,
		.params = params
	};
	if (params->jobs == 1) {
		perform_task(&task);
	} else {
		if (!perform_in_parallel(&task, params->jobs)) {
			free(raster);
			return 1;
		}
	}

	bool success = write_ppm(raster, size, params);
	free(raster);
	return success ? 0 : 1;
}
