#include <ccid/harmest.hpp>
#include <ccid/snditf.hpp>

#include <cstdio>
#include <pthread.h>
#include <curses.h>
#include <string>
#include <iostream>
#include <complex>

void
*prtfun(void* s)
{
	std::cout << *(std::string*) s << std::endl;
}

int
main(){
	 float a = 9.;
	// pthread_t t1, t2;
	// std::string m1 = "this is t1";
	// std::string m2 = "this is t2";


	printf("Using ALSA version: %s\n", alsaversion() );
	printf("Using FFTW version: %s\n", fftwversion() );
	printf("Using VOLK version: %s\n", volkversion() );
	// printf("a         = %9.4f\n", a );
	// printf("sqrt(a)   = %9.4f\n", sqrt(a) );
	printf("2*sqrt(a) = %9.4f\n", doublesqrt(a) );
	printf("3+6       = %d\n", ret3p(6) );
	//std::cout << "h.size_in() = " << h.size_in() << std::endl;

	// int r = pthread_create(&t1, NULL, prtfun, (void*) &m1);
	// r = pthread_create(&t2, NULL, prtfun, (void*) &m2);
	// initscr();
	// cbreak();
	// noecho();
	// clear();
	// int ch = getch();

	// endwin();
	// std::cout << ch << " 🥳 " << std::endl;
	// std::cout << ret3p(ch) << " 🥳 " << std::endl;

	// pthread_exit(NULL);
	constexpr int N = 13;
	harmest h(N);

	int16_t* vec = NULL;
	float* fec = NULL;
	vec = (int16_t*) malloc(sizeof(int16_t)*N);
	fec = (float*) malloc(sizeof(float)*N);

	for (int i = 0; i < N; ++i)
	{
		vec[i] = 100*(i - N/2); 
		printf("vec[%d] = %d\n", i, vec[i]);		
	}

	int2float(fec, vec, N);

	for (int i = 0; i < N; ++i)
	{
		printf("fec[%d] = %5.2f\n", i, fec[i]);
	}

	h.cpydata(fec);
	h.execute();
	h.print();

	fftwf_complex* y = h.output();
	for (int i = 0; i < h.size_out(); ++i)
	{
		printf("out[%d] = %5.2f %5.2f*j\n", i, (*y)[0], (*y)[1]);
		y++;
	}



	//free(vec);
	//free(fec);
	return(0);
}