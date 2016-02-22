// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#ifndef PLOT_H
#define PLOT_H

// Parameters for plotting a fractal set as a raster image.
struct Parameters {
	char name;
	double x, y;
	double scale;
	int iterations;
	int width, height;
	const char *ofile;
	int n_args;
	const char **args;
}

// Plots according to the given parameters. Returns 0 on success, 1 on failure.
int plot(const struct Parameters *params);

#endif
