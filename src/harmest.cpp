#include <ccid/harmest.hpp>



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

	d_magnitude = (float*)          
	         volk_malloc( sizeof(float)*d_size_out, volk_get_alignment() );

	d_output = (fftwf_complex*) 
	          volk_malloc( sizeof(fftwf_complex)*d_size_out, volk_get_alignment() );
	d_plan = fftwf_plan_dft_r2c_1d(d_size_in, d_input, d_output, FFTW_ESTIMATE);	
}

harmest::~harmest()
{
	fftwf_destroy_plan(d_plan);
	volk_free(d_input);
	volk_free(d_magnitude);
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

float*
harmest::magnitude()
{
	return d_magnitude;
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
	for (int i = 0; i < d_size_out; ++i)
	{
		printf("d_magnitude[%d] = %6.3f\n", i, d_magnitude[i]);
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
harmest::cpydata(int16_t* d, int numel)
{
	assert(numel == d_size_in);
	constexpr float scale = powf(2.f,15);
	volk_16i_s32f_convert_32f(d_input, d, scale, numel);	
	return;
}

void
harmest::execute()
{
	fftwf_execute(d_plan);
	volk_32fc_magnitude_32f(d_magnitude, (const lv_32fc_t*) d_output, d_size_out);
	return;
}
