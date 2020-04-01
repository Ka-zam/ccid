#include <ccid/snditf.hpp>


int ret3p(int a)
{
	return a + 3;
}

void
int2float(float* out, const int16_t* in, int pts)
{
	volk_16i_s32f_convert_32f(out, in, 100.f, pts);
}