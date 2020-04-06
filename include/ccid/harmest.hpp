#ifndef HARMEST_H
#define HARMEST_H

#include <cassert>
#include <cmath>
#include <cinttypes>
#include <complex>
#include <fftw3.h>
#include <volk/volk.h>

const char* fftwversion();// {	return fftwf_version; };

class harmest
{
private:
	uint32_t d_size_in;
	uint32_t d_size_out;
	fftwf_plan d_plan;
	float* d_input;
	float* d_magnitude;
	fftwf_complex* d_output;
public:
	void execute();
	int size_in();
	int size_out();
	fftwf_complex* output();
	float* input();
	float* magnitude();
	void cpydata(float* d);
    void cpydata(int16_t* d, int numel);
	void print();

	harmest(int size);
	~harmest();
};

#endif