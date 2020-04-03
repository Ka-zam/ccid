#include <ccid/harmest.hpp>

float
doublesqrt(float x)
{
	float res;
	res = 2.f*sqrtf(x);
	return res;
}



char* fftwversion()
{
	char* res = "3.3.8";
	return (char*) res;
}