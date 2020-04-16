#include <ccid/harmest.hpp>
#include <ccid/snditf.hpp>

#include <cstdio>
#include <pthread.h>
#include <curses.h>
#include <string>
#include <iostream>
#include <complex>
#include <unistd.h>
//#include <jack/jack.h>


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
	snditf ad(jclient);

	//jack_set_process_callback(d_client, std::bind(&snditf::work, this, _1), 0);
	//jack_set_process_callback(d_client, std::bind(&snditf::work, this, _1), 0);

	//in = jack_port_register (d_client, "in", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    //d_out = jack_port_register (d_client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    std::function<int(unsigned int, void*)> cbf = &ad.work;
	jack_set_process_callback(jclient,
//		[&ad](jack_nframes_t f, void* a){ return ad.work(f, a); }, NULL);
//		[&ad](unsigned int f, void* a){ return ad.work(f, a); },
        cbf
		, 0);

    if (jack_activate(jclient)) {
            fprintf (stderr, "cannot activate client");
            exit(-1);
    }

	//ad.prt();
	//char* dev = "plughw:2,0";
	sleep(3);

	return(0);
}