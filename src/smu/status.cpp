#include "status.hpp"
#include <cstdint>
// #include <tuple>


CyanBox::CyanBox(std::string pci_id, uint32_t cmd_addr, uint32_t rsp_addr, uint32_t arg_addr, uint32_t timeout): transprt(pci_id) {
  this->addr_cmd = cmd_addr;
  this->rsp_cmd  = rsp_addr;
  this->arg_addr = arg_addr;
  this->timeout  = timeout;
}
bool CyanBox::send(uint32_t msg_id, uint32_t arg, uint32_t arg_2) {
  this->transprt.write_config32(this->rsp_cmd, 0);
  this->transprt.write_config32(this->arg_addr, arg);
  this->transprt.write_config32(this->arg_addr + 4, this->arg_addr);
  this->transprt.write_config32(this->addr_cmd, msg_id);

  uint32_t tme = timeout;
  auto addr = rsp_cmd;
  /* implement later
  while (tme > 0) {
    tme--;
    auto stat = this->transprt.read_config32(addr);

  }
  */
  
  return true;
}


uint32_t CyanBox::read() {
  uint32_t var = this->transprt.read_config32(this->transprt.read_smu(this->arg_addr));
  return var;
}


uint32_t CyanBox::read_hi() {
  uint32_t var = this->transprt.read_config32(this->transprt.read_smu(this->arg_addr + 4));
  return var;
}




