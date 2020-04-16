#include <ccid/harmest.hpp>
#include <ccid/snditf.hpp>

#include <cstdio>
#include <pthread.h>
#include <curses.h>
#include <string>
#include <iostream>
#include <complex>
#include <unistd.h>



void
*prtfun(void* s)
{
	std::cout << *(std::string*) s << std::endl;
}

int
main(){
    jack_client_t *jclient;
    jack_status_t  jstatus;	
	//float a = 9.;
	// pthread_t t1, t2;
	// std::string m1 = "this is t1";
	// std::string m2 = "this is t2";

	// printf("Using ALSA version: %s\n", alsaversion() );
	printf("Using FFTW version: %s\n", fftwversion() );
	// printf("Using VOLK version: %s\n", volkversion() );

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
	constexpr int N = 5;
	harmest h(N);

	int16_t* vec = NULL;
	vec = (int16_t*) malloc(sizeof(int16_t)*N);

	for (int i = 0; i < N; ++i)
	{
		vec[i] = 1000*(i - N/2); 
		printf("vec[%d] = %d\n", i, vec[i]);		
	}

	h.cpydata(vec, N);
	h.execute();
	h.print();

	free(vec);

	//const char* c = "hw:4,0";
	//Connect JACK to this object
	jclient = jack_client_open("ccid", JackNullOption, &jstatus );
	if (jclient == NULL){
		fprintf(stderr, "%s %2.0x\n", "Failed to open client:", jstatus);
	}
	Snditf ad(jclient);

	Callback<int(jack_nframes_t, void*)>::func = std::bind(&Snditf::work, ad, std::placeholders::_1, std::placeholders::_2);
    // Convert callback-function to c-pointer.
    int (*audiocbf)(jack_nframes_t, void*) = static_cast<decltype(audiocbf)>(Callback<int(jack_nframes_t, void*)>::callback);

	jack_set_process_callback(jclient, audiocbf, NULL);

    if (jack_activate(jclient)) {
            fprintf (stderr, "cannot activate client");
            exit(-1);
    }

	sleep(13);
	ad.prt();
	jack_deactivate(jclient);
	jack_client_close(jclient);

	return(0);
}