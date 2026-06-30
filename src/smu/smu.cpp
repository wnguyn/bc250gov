#include "smu.hpp"
#include "cmd.hpp"
#include <gbm.h>
#include <fstream>
#include <iostream>

Path APU::get_sysfs_path(drmPciBusInfo *pci, char *buf, size_t len) {                             
  int n = std::snprintf(buf, len,                                                                    
     "/sys/bus/pci/devices/%04x:%02x:%02x.%x/",                                                     
     pci->domain, pci->bus, pci->dev, pci->func);                                                   
  return Path(std::string_view{buf, static_cast<size_t>(std::min(n, (int)len - 1))});            
}       


APU::APU(std::vector<SafePt> pts) {
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
  auto smu = Smu(true, std::move(buf), 30);  // allocate buf[128]
  std::cout << "connection started????\n";

    
  
};

APU::~APU() {
  // delete dev;
};

