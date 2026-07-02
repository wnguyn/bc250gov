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
  
  while(1) {
    // check temps before doing anything and get freq domain
    auto temps = gpu->read_temp();
    std::tuple<uint32_t, uint32_t> domain_freq = gpu->freq;
    uint32_t max = std::get<1>(domain_freq);
    if (temps >= cfg->timing.throt) {
      std::cout << "your thing is thorttling man.. temp is: " << temps << std::endl;
      gpu->change_freq(max - cfg->big_step); 
    }
    /*
    std::ifstream file("/proc/stat");
    std::stringstream buf;
    buf << file.rdbuf();
    std::string stat_stuff = buf.str();
    */




    std::this_thread::sleep_for(std::chrono::milliseconds(1767)); 
  }
  return 0;
}
