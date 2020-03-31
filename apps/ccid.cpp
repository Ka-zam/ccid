#include <ccid/harmest.hpp>

#include <cstdio>

int
main(){
	float a = 9.;
	printf("Using ALSA version: %s\n", alsaversion() );
	printf("Using FFTW version: %s\n", fftwversion() );
	printf("a         = %9.4f\n", a );
	printf("sqrt(a)   = %9.4f\n", sqrt(a) );
	printf("2*sqrt(a) = %9.4f\n", doublesqrt(a) );
	return(0);
}