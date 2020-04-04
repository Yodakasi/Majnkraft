#pragma once

#include <noise/noise.h>
#include <cmath>
#include <time.h>

class Noise {
private:
	noise::module::Perlin gen;

public:
	Noise();
	double noise(double nx, double ny);
	double noiseFun(double x, double y);

};