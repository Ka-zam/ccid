#include <ccid/harmest.hpp>

#include <cstdio>
#include <cmath>

int
main(){
	float a = 2.;
	fftw_complex b;
	//b.real(1.);
	printf("sqrt(2) = %9.7f\n", sqrt(a) );
	printf("2*sqrt(2) = %9.7f\n", doublesqrt(a) );
	return(0);
}