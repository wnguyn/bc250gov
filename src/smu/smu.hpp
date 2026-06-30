// Tradtional clocking without interacting with the SMU library, basically amdgpu

#include <cstdint>
#include <tuple>
#include <vector>
#import <iostream>
#include <filesystem>
#include <amdgpu_drm.h>   
#include <xf86drm.h>
#include <amdgpu.h>
#include <gbm.h>
#import "cmd.hpp"
#include "config.hpp"

using Path = std::filesystem::path;

const uint32_t GRBM_STATUS_REG = 0x2004;
const uint32_t GPU_ACTIVE_BIT = 31;








class DrmDevice;

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
  private: 
    Path get_sysfs_path(drmPciBusInfo *pci, char *buf, size_t len);
 
};


