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
// https://stackoverflow.com/questions/19808054/convert-c-function-pointer-to-c-function-pointer/19809787
template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args>
    static Ret callback(Args... args) { return func(args...); }
    static std::function<Ret(Params...)> func;
};

// Initialize the static member.
template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

class Snditf
{
  public:
    Snditf(jack_client_t* client);
    ~Snditf();
    void prt();
    int work(jack_nframes_t nframes, void *arg);
  private:
    uint64_t d_nprocessed;
    jack_port_t*   d_in;
    jack_port_t*   d_out;
    jack_client_t* d_client;
};

#endif