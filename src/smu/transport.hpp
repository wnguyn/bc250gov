#include <cstdint>
#include <fstream>
#include <filesystem>
/* Send binary offsets to doohickey */

class CyanTransport {
  public: 
    CyanTransport(std::string std);
    ~CyanTransport();
    uint32_t read_config32(uint32_t offset);
    void write_config32(uint64_t offset, uint32_t val);
    uint32_t read_smu(uint32_t reg);
    uint32_t write_smu(uint32_t offset, uint32_t val);



  private:
    std::filesystem::path bus_path;
    std::fstream file;
    bool flock;
};
