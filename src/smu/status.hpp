#include "transport.hpp"
#include <cstdint>


enum SmuStatus {
    Ok = 0x01,
    Failed = 0xFF,
    UnknownCmd = 0xFE,
    RejectedPrereq = 0xFD,
    RejectedBusy = 0xFC,
};





class CyanBox {
  public:

    uint32_t addr_cmd;
    uint32_t rsp_cmd;
    uint32_t arg_addr;
    uint32_t timeout;
    CyanTransport* trans;

    CyanBox();
    CyanBox(CyanTransport* t, uint32_t cmd, uint32_t rsp, uint32_t arg, uint32_t to);
    bool send(uint32_t msg_id, uint32_t arg, uint32_t arg_2);
    uint32_t read();
    uint32_t read_hi();
    SmuStatus wdone();
};
