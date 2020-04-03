#ifndef SNDITF_H
#define SNDITF_H

#include <cmath>
#include <cstdint>
#include <alsa/asoundlib.h>
#include <volk/volk.h>
#include <volk/constants.h>

int ret3p(int a);
void int2float(float* out, const int16_t* in, int pts);
char* alsaversion();
const char* volkversion();

#endif