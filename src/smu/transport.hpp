#include <cstdint>
#include <iostream>
#include <filesystem>


/* Send binary offsets to doohickey */

class CyanTransport {
  public: 
    CyanTransport();
    ~CyanTransport();
    bool open();
    void close();
    bool read_config32(uint32_t offset);
    bool write_config32(uint64_t offset, uint32_t val);
    uint32_t read_smu(uint32_t reg);
    uint32_t write_smu(uint32_t reg);



  private:
    std::filesystem::path bus_path;
    int file;
};
