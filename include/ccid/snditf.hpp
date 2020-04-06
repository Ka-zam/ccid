#ifndef SNDITF_H
#define SNDITF_H

#include <cmath>
#include <cstdint>
#include <alsa/asoundlib.h>
#include <volk/volk.h>
#include <volk/constants.h>

const char* alsaversion();
const char* volkversion();

class snditf
{
private:
	char* d_device;
	snd_pcm_t* d_handle;
	snd_pcm_hw_params_t* d_params;
	snd_pcm_uframes_t d_frames;
	uint8_t* d_buff;

public:
	snditf();
    snditf(const char* dev);
	~snditf();
	void prt();
};

#endif