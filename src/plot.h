// Copyright 2016 Mitchell Kember. Subject to the MIT License.

#ifndef PLOT_H
#define PLOT_H

// Parameters for plotting a fractal set as a raster image.
struct Parameters {
	char name;          // name of the fractal set (first letter)
	double a, b;        // complex constant c (only used by Julia)
	double cx, cy;      // centre of the viewport
	double scale;       // scale factor
	double escape;      // threshold for an unbounded orbit
	int iterations;     // number of iterations
	int width, height;  // image dimensions, in pixels
	const char *ofile;  // output filename
};

// Plots according to the given parameters. Returns 0 on success, 1 on failure.
int plot(const struct Parameters *params);

#endif
