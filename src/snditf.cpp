#include <ccid/snditf.hpp>

/** 
* \brief Callback driven sound interface class
*
* Class that allows JACK style callback driven DSP functions.
* http://tedfelix.com/software/c++-callbacks.html
*/


Snditf::Snditf(jack_client_t* client)
{
	/*
	d_client = jack_client_open("snditf", JackNullOption, &d_status );
	if (d_client == NULL){
		fprintf(stderr, "%s %2.0x\n", "Failed to open client:", d_status);
	}
	*/

	//jack_set_process_callback(d_client, std::bind(&snditf::work, this, _1), 0);
	//jack_set_process_callback(d_client, std::bind(&snditf::work, this, _1), 0);
/*
	d_in = jack_port_register (d_client, "in", JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
    d_out = jack_port_register (d_client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
    if (jack_activate (d_client)) {
            fprintf (stderr, "cannot activate client");
    }    
    //prt();
    */
    d_nprocessed = 0;
    d_client = client;
	d_in =  jack_port_register(d_client, "in" , JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput , 0);
    d_out = jack_port_register(d_client, "out", JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);
}


Snditf::~Snditf()
{
    //jack_client_close(d_client);
}

void
Snditf::prt()
{
	printf("Processed samples: %ld\n", d_nprocessed );
}

int 
Snditf::work(jack_nframes_t nframes, void *arg)
{
    jack_default_audio_sample_t *in, *out;

    in =  (jack_default_audio_sample_t*) jack_port_get_buffer(d_in, nframes);
    out = (jack_default_audio_sample_t*) jack_port_get_buffer(d_out, nframes);

    // Do some actual audio processing
    memcpy (out, in, sizeof(jack_default_audio_sample_t) * nframes);
    d_nprocessed += nframes;
    
	return 0;
}

/*
const char* alsaversion()
{
	return SND_LIB_VERSION_STR;
}

const char* volkversion()
{
	return volk_version();
}
*/