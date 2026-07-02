#include "status.hpp"
#include <cstdint>
// #include <tuple>


CyanBox::CyanBox() : addr_cmd(0), rsp_cmd(0), arg_addr(0), timeout(0), trans(nullptr) {}
CyanBox::CyanBox(CyanTransport* t, uint32_t cmd_addr, uint32_t rsp_addr, uint32_t arg_addr, uint32_t timeout)
    : trans(t) {
  this->addr_cmd = cmd_addr;
  this->rsp_cmd  = rsp_addr;
  this->arg_addr = arg_addr;
  this->timeout  = timeout;
}
bool CyanBox::send(uint32_t msg_id, uint32_t arg, uint32_t arg_2) {
  trans->write_smu(rsp_cmd, 0);
  trans->write_smu(arg_addr, arg);
  trans->write_smu(arg_addr + 4, arg_2);
  trans->write_smu(addr_cmd, msg_id);
  return true;
}

SmuStatus CyanBox::wdone() {
  for (uint32_t i = 0; i < timeout; i++) {
    uint32_t raw = trans->read_smu(rsp_cmd);
    if (raw == 0xFF) return SmuStatus::Failed;
    if (raw == 0xFE) return SmuStatus::UnknownCmd;
    if (raw == 0xFD) return SmuStatus::RejectedPrereq;
  }
  return SmuStatus::Failed;
}


uint32_t CyanBox::read() {
  return trans->read_smu(arg_addr);
}

uint32_t CyanBox::read_hi() {
  return trans->read_smu(arg_addr + 4);
}




