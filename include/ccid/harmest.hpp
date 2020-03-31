#ifndef HARMEST_H
#define HARMEST_H

#include <cmath>
#include <complex>
#include <fftw3.h>
#include <alsa/asoundlib.h>

float doublesqrt(float x);
char* alsaversion();
char* fftwversion();

#endif