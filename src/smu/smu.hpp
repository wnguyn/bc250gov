// Tradtional clocking without interacting with the SMU library

#include <iostream>
#include <cstdint>
#include <tuple>
#include <vector>

#include <amdgpu_drm.h>   
#include <amdgpu.h>
#include "config.hpp"


class APU {
  public:
    amdgpu_device* dev;
    uint32_t sample;
    std::tuple<uint32_t, uint32_t> freq; // domain of range [a,b] of freq
    std::vector<SafePt> safe_pts;
    APU(std::vector<SafePt> pts);
    ~APU();

    uint32_t get_load();
    bool read_temp();
    bool change_freq(uint32_t prof);
    void set_perf_profile(uint32_t prof);
    void save_profile(uint32_t frq);
    // void get_freq() i don't care about encapsulation or whatever


};
