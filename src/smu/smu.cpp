#include "smu.hpp"
#include "cmd.hpp"
#include <amdgpu.h>
#include <gbm.h>
#include <fstream>
#include <iostream>
#include <tuple>

Path APU::get_sysfs_path(drmPciBusInfo *pci, char *buf, size_t len) {                             
  int n = std::snprintf(buf, len,                                                                    
     "/sys/bus/pci/devices/%04x:%02x:%02x.%x/",                                                     
     pci->domain, pci->bus, pci->dev, pci->func);                                                   
  return Path(std::string_view{buf, static_cast<size_t>(std::min(n, (int)len - 1))});            
}       

APU::APU(std::vector<SafePt> pts) : smu(true, "0000:00:00.0", 67) {
  std::ofstream file_thing;
  drmPciBusInfo location = {
    .domain = 0,
    .bus = 1,
    .dev = 0,
    .func = 0,
  };
  char buf[128];

  Path sysfs_path = APU::get_sysfs_path(&location, buf, sizeof(buf));
  Path drm_path = Path("/dev/dri/renderD128");

  file_thing.open(drm_path);
  int hi = 0; int lo = 0;
  // probably could iterate functionally instead of imperative
  for (int i = 0; i < pts.size(); i++) {
    int temp = pts[i].freq;
    if (temp > hi) 
      hi = temp;
    if (temp < lo)
      lo = temp;
  }
  std::tuple<int,int> tuple(lo, hi);
  this->smu.set_gpu_max_temp(60); // aggressive asf, need to check peformance on heckin' games!!!
  this->smu.unforce_gfx_freq();
  this->smu.unforce_gfx_vid();
  amdgpu_device_handle dev_skibidi;

  this->dev = std::move(dev_skibidi);
  this->sample = 0;
  this->freq = tuple;
  this->safe_pts = pts;

};

APU::~APU() {
  // delete dev;
};

std::tuple<uint32_t, uint32_t> APU::poll_and_get_load() {

  uint32_t reg = 0;
  auto var = amdgpu_read_mm_registers(this->dev, GRBM_STATUS_REG, 1, 0, 0, &reg);
  bool busyornotidk = (reg & (1 << GPU_ACTIVE_BIT)) > 0;       
  this->sample <<= 1;
  if (busyornotidk) 
    this->sample |= 1;

  uint32_t avgload = __builtin_popcount(this->sample);
  uint32_t len = std::__countr_zero(this->sample);
  std::tuple<uint32_t, uint32_t> turp(avgload, len);
  return turp;

};

uint32_t APU::read_temp() {
  uint32_t temp_millidegrees = 0;
  uint32_t ret = amdgpu_query_sensor_info(                                                                                                                                                                              
       this->dev,                                                                                                                                                                                                   
       AMDGPU_INFO_SENSOR_GPU_TEMP,                                                                                                                                                                                 
       sizeof(temp_millidegrees),                                                                                                                                                                                   
       &temp_millidegrees                                                                                                                                                                                           
   );    
  return temp_millidegrees;
};
bool APU::change_freq(uint32_t arg) {
  auto safe_pt = this->safe_pts[0]; // add logic so that it would pick from closest to thingy functionally latelrkajwkefhasjkdfh
  this->smu.force_gfx_vid((uint32_t)safe_pt.volt);
  this->smu.force_gfx_freq(safe_pt.freq);
  return true;
};

void APU::set_perf_profile(uint32_t prof) {
  this->smu.q3_set_perf_profile_index(prof);
};

void APU::save_profile(uint32_t frq) {
  this->freq = {frq, frq};
  this->smu.force_gfx_freq(frq);
};

