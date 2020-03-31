#include <ccid/harmest.hpp>

#include <cstdio>
#include <pthread.h>
#include <curses.h>
#include <string>
#include <iostream>

void
*prtfun(void* s)
{
	std::cout << *(std::string*) s << std::endl;
}

int
main(){
	float a = 9.;
	pthread_t t1, t2;
	std::string m1 = "this is t1";
	std::string m2 = "this is t2";

	printf("Using ALSA version: %s\n", alsaversion() );
	printf("Using FFTW version: %s\n", fftwversion() );
	printf("a         = %9.4f\n", a );
	printf("sqrt(a)   = %9.4f\n", sqrt(a) );
	printf("2*sqrt(a) = %9.4f\n", doublesqrt(a) );

	int r = pthread_create(&t1, NULL, prtfun, (void*) &m1);
	r = pthread_create(&t2, NULL, prtfun, (void*) &m2);
	initscr();
	cbreak();
	noecho();
	clear();
	int ch = getch();

	endwin();
	std::cout << ch << " 🥳 " << std::endl;

	pthread_exit(NULL);
	return(0);
}