# Chaos

Chaos is a C program that plots fractals. I was inspired to do this while reading [The Chaos Hypertextbook][ht]. It can plot Julia sets, the Mandelbrot set, and the Tricorn set (or Mandelbar set).

![The Mandelbrot set](http://i.imgur.com/UVuWeQj.jpg)

_Generated by_ `chaos -n m -x -0.575 -s 0.857 -i 50000 -w 800 -h 700 -c r -p -0.06`.

[ht]: http://hypertextbook.com/chaos/
[ppm]: http://netpbm.sourceforge.net/doc/ppm.html

## Build

Just run `make`.

## Usage

Run `chaos --help` to see the instructions:

```
usage: chaos [options]

  Default
    chaos -n j -a 0 -b 0
          -x 0 -y 0 -s 1 -e 2 -i 1000
          -w 500 -h 500 -c g -j 1 -o chaos.ppm

  Fractal
    -n  Fractal name: j/m/t for Julia/Mandelbrot/Tricorn
    -a  (Julia only) Real part of the constant c
    -b  (Julia only) Imaginary part of the constant c

  Settings
    -x  X-component of the centre of the viewport
    -y  Y-component of the centre of the viewport
    -s  Scale factor of the viewport
    -e  Escape threshold for determing if an orbit is unbounded
    -i  Integer number of iterations to perform

  Output
    -w  Width of the output image in pixels
    -h  Height of the output image in pixels
    -c  Color scheme: g/r for grayscale/rainbow
    -p  Power for the smooth value
    -j  Number of jobs to run in parallel
    -o  Output filename
```

If you have a multicore machine, be sure to use the `-j` option. Fractal rendering is ideal for parallelism, so you should see a linear decrease in execution time!

## Output

Chaos writes output in the [PPM image format][ppm]. The easiest way to view images is to run `convert chaos.ppm chaos.png`, assuming you have ImageMagick installed.

## License

© 2016 Mitchell Kember

Chaos is available under the MIT License; see [LICENSE](LICENSE.md) for details.
