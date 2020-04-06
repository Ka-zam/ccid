#ifndef HARMEST_H
#define HARMEST_H

#include <cmath>
#include <complex>
#include <fftw3.h>
#include <volk/volk.h>

//using namespace std::string_literals;

float doublesqrt(float x);
const char* fftwversion();

class harmest
{
private:
	int d_size_in;
	int d_size_out;
	fftwf_plan d_plan;
	float* d_input;
	fftwf_complex* d_output;
public:
	void execute();
	int size_in();
	int size_out();
	fftwf_complex* output();
	float* input();
	void cpydata(float* d);
	void print();

	harmest(int size);
	~harmest();
};

#endif