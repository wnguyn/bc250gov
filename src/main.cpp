#include <iostream> 
#include <thread> 
#include <chrono>
#include <fstream>
#include <cpuid.h>
#include <memory>
#include <string>
#include <cstdint>

// configuration file
#include "config.hpp"
#include "smu/smu.hpp"
#include "idle/policy.hpp"




std::string get_cpu_sku() {
  std::string line;
  std::ifstream sku("/proc/cpuinfo");
  while (std::getline(sku, line)) {
    if (line.rfind("model name", 0) == 0) {
      size_t pos = line.find(':');
      if (pos != std::string::npos) {
        return line.substr(pos + 2); 
      }
    }
  }
  return line;
};




int main(void) {
  std::cout << "starting governor... \n";
  std::string cpu_sku = get_cpu_sku();
  if (cpu_sku != "AMD BC-250") {
    std::cout << "you aren't running this on a bc-250";
    return 6767;
  }

  auto cfg = std::make_unique<Config>();
  auto gpu = std::make_unique<APU>(cfg->safe_pt);
  smu_init_idle(*gpu);
  
  bool forced = false;
  size_t idx = gpu->safe_pts.size() - 1;

  while (1) {
    auto [load, idlestk] = gpu->poll_and_get_load();
    uint32_t temp = gpu->read_temp();
    auto [lo, hi] = cfg->load_target;

    if (!forced && load > hi) {
      auto& pt = gpu->safe_pts[idx];
      gpu->smu.force_gfx_vid((uint32_t)pt.volt);
      gpu->smu.force_gfx_freq(pt.freq);
      forced = true;
    }

    if (forced && idlestk > cfg->timing.idle_thresh) {
      gpu->smu.unforce_gfx_freq();
      gpu->smu.unforce_gfx_vid();
      forced = false;
    }

    if (temp > 85000) { // we already set smu to max 60 but I don't want to fry my board lol
      auto& lo_pt = gpu->safe_pts[0];
      gpu->smu.force_gfx_vid((uint32_t)lo_pt.volt);
      gpu->smu.force_gfx_freq(lo_pt.freq);
      forced = true;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return 0;
}
