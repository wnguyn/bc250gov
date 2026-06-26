#include <iostream> 
#include <fstream>
#include <cpuid.h>
#include <string>

// configuration file
#include "config.hpp"


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
  std::cout << "Starting governor..." << std::endl;
  std::string cpu_sku = get_cpu_sku();
  if (cpu_sku != "AMD BC-250") {
    std::cout << "you aren't running this on a bc-250";
    return 1;
  }
  Config config = Config::defaults();






  return 0;
}
