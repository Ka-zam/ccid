#include <ccid/harmest.hpp>

float
doublesqrt(float x)
{
	float res;
	res = 2.f*sqrtf(x);
	return res;
}

const char* fftwversion()
{
	return fftwf_version;
}

harmest::harmest(int size)
{
	d_size_in = size;
	d_size_out = d_size_in/2 + 1;

	d_input = (float*)          
	         volk_malloc( sizeof(float)*d_size_in, volk_get_alignment() );
	d_output = (fftwf_complex*) 
	          volk_malloc( sizeof(fftwf_complex)*d_size_out, volk_get_alignment() );
	d_plan = fftwf_plan_dft_r2c_1d(d_size_in, d_input, d_output, FFTW_ESTIMATE);	
}

harmest::~harmest()
{
	fftwf_destroy_plan(d_plan);
	//printf("Trying to clean up...\n%p\n%p\n", d_input, d_output);
	volk_free(d_input);
	volk_free(d_output);
}

int
harmest::size_in()
{
	return d_size_in;
}

int
harmest::size_out()
{
	return d_size_out;
}

float*
harmest::input()
{
	return d_input;
}

fftwf_complex*
harmest::output()
{
	return d_output;
}

void
harmest::print()
{
	for (int i = 0; i < d_size_in; ++i)
	{
		printf("d_input[%d] = %6.3f\n", i, d_input[i]);
	}
	for (int i = 0; i < d_size_out; ++i)
	{
		printf("d_output[%d] = %6.3f %+6.3fj\n", i, d_output[i][0], d_output[i][1]);
	}	
}

void 
harmest::cpydata(float* d)
{
	for (int i = 0; i < d_size_in; ++i)
	{
		d_input[i] = *d;
		d++;
	}
	return;
}

void
harmest::execute()
{
	fftwf_execute(d_plan);
	return;
}
