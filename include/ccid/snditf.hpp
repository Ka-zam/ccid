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

class jackhandler
{
public:
  void addhandler(std::function<void(int)> callback)
  {
    callback(1);
  }
}

class snditf
{
  public:
    snditf();
    ~snditf();
    void prt();
    int connect();
    int work(jack_nframes_t nframes, void *arg);
  private:
    jack_port_t *d_in;
    jack_port_t *d_out;
    jack_client_t *d_client;
    jack_status_t d_status;
};

#endif