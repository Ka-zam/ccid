#ifndef SNDITF_H
#define SNDITF_H

#include <cstring>
#include <cmath>
#include <cstdint>
#include <functional>
#include <jack/jack.h>
#include <volk/volk.h>
#include <volk/constants.h>

//const char* alsaversion();
//const char* volkversion();

// https://stackoverflow.com/questions/1000663/using-a-c-class-member-function-as-a-c-callback-function

template <typename T>
struct Callback;
{
  
};

class snditf
{
  public:
    snditf(jack_client_t* client);
    ~snditf();
    void prt();
    int work(jack_nframes_t nframes, void *arg);
  private:
    uint64_t d_nprocessed;
    jack_port_t*   d_in;
    jack_port_t*   d_out;
    jack_client_t* d_client;
    //jack_status_t d_status;
};

#endif