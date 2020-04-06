#include <ccid/snditf.hpp>


const char* alsaversion()
{
	return SND_LIB_VERSION_STR;
}

const char* volkversion()
{
	return volk_version();
}

snditf::snditf()
{
	int res;
	//char* dev = dev_name;
	printf("%s %d\n", "plughw:2,0", res);
	if (res = snd_pcm_open(&d_handle, "plughw:2,0", SND_PCM_STREAM_PLAYBACK, 0) < 0) 
	{
		printf("ERROR: Can't open \"%s\" PCM device. %s\n",	"plughw:2,0", snd_strerror(res));	
	}
	printf("Opened \"%s\" PCM device. %s\n",	"plughw:2,0", snd_strerror(res));			
}

snditf::snditf(const char* dev)
{
	int res;
	d_device = (char*) dev;
	if (res = snd_pcm_open(&d_handle, dev, SND_PCM_STREAM_PLAYBACK, 0) < 0) 
	{
		printf("ERROR: Can't open \"%s\" PCM device. %s\n",	dev, snd_strerror(res));	
	}
	else
	{
		printf("Opened \"%s\" PCM device: %s\n",	dev, snd_strerror(res));			
	}

	/* Allocate parameters object and fill it with default values*/
	snd_pcm_hw_params_alloca(&d_params);

	snd_pcm_hw_params_any(d_handle, d_params);

	/* Set parameters */
	if (res = snd_pcm_hw_params_set_access(d_handle, d_params,
					SND_PCM_ACCESS_RW_INTERLEAVED) < 0) 
		printf("ERROR: Can't set interleaved mode. %s\n", snd_strerror(res));

	if (res = snd_pcm_hw_params_set_format(d_handle, d_params,
						SND_PCM_FORMAT_S16_LE) < 0) 
		printf("ERROR: Can't set format. %s\n", snd_strerror(res));

	if (res = snd_pcm_hw_params_set_channels(d_handle, d_params, 2) < 0) 
		printf("ERROR: Can't set channels number. %s\n", snd_strerror(res));

	uint32_t rate = 44100;
	if (res = snd_pcm_hw_params_set_rate_near(d_handle, d_params, &rate, 0) < 0) 
		printf("ERROR: Can't set rate. %s\n", snd_strerror(res));

	/* Write parameters */
	if (res = snd_pcm_hw_params(d_handle, d_params) < 0)
		printf("ERROR: Can't set harware parameters. %s\n", snd_strerror(res));	
}

snditf::~snditf()
{
	snd_pcm_close(d_handle);
}

void
snditf::prt()
{
	printf("%s\n", d_device);
}