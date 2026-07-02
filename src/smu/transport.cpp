#include "transport.hpp"

#include <unistd.h>
#include <string>
#include <fstream>
#include <cstdint>
#include <iostream>
#include <filesystem>
#include <bit>


CyanTransport::CyanTransport(std::string std) {
  std::filesystem::path config_path = std::filesystem::path("/sys/bus/pci/devices/") / std / "config";
  this->bus_path = config_path;
  this->flock = true;
  this->file = std::fstream(this->bus_path);
}

CyanTransport::~CyanTransport() {
  this->file.close();
}

uint32_t CyanTransport::read_config32(uint32_t ofst) {
  uint8_t buf[4] = {0};
  this->file.seekg(ofst, std::ios::beg);
  this->file.read(reinterpret_cast<char*>(buf), 4);
  // turn into little endian manually
  uint32_t value = (static_cast<uint32_t>(buf[0]) << 0)  |
                 (static_cast<uint32_t>(buf[1]) << 8)  |
                 (static_cast<uint32_t>(buf[2]) << 16) |
                 (static_cast<uint32_t>(buf[3]) << 24);
  return value;
}

void CyanTransport::write_config32(uint64_t offset, uint32_t val) {
    uint8_t buf[4] = {
        (uint8_t)(val),
        (uint8_t)(val >> 8),
        (uint8_t)(val >> 16),
        (uint8_t)(val >> 24)
    };
    this->file.seekp(offset, std::ios::beg);
    this->file.write(reinterpret_cast<char*>(buf), 4);
}
uint32_t CyanTransport::read_smu(uint32_t reg) {
  CyanTransport::write_config32(0xB8, reg);
  auto var = CyanTransport::read_config32(0xBC);
  return var;
}

void CyanTransport::write_smu(uint32_t reg, uint32_t val) {
  CyanTransport::write_config32(0xB8, reg);
  CyanTransport::write_config32(0xBC, val);
}
