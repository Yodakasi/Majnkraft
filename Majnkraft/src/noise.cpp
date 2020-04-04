#include "noise.h"

#include<iostream>

Noise::Noise() : gen() {
    srand(time(0));
    gen.SetSeed(rand());
}

double Noise::noise(double nx, double ny) {
    // Rescale from -1.0:+1.0 to 0.0:1.0
    return gen.GetValue(nx, ny, 0) / 2.0 + 0.5;
}


double Noise::noiseFun(double x, double y) {
    double res;
    double nx = x / 128 - 0.5,
        ny = y / 128 - 0.5;
    double e = 1 * noise(1 * nx, 1 * ny)
        + 0.5 * noise(2 * nx, 2 * ny)
        + 0.25 * noise(4 * nx, 4 * ny);
    res = pow(e, 0.75);
    return res;
}