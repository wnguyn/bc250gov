#include "cmd.hpp"




Smu::Smu(bool queue, std::string buf, uint16_t timeout) : trans(buf) {
  // populate queue
  for (const auto& [id, cmd, rptr, wptr] : DEFAULT_QUEUE_ADDRS) 
    this->queue.emplace(buf, cmd, rptr, wptr, timeout);
};


Smu::~Smu() {
  // delete trans;
};


bool Smu::guard_queue(uint32_t queue) {
  if (queue == 0)
    return false;
  return true;
};



uint32_t Smu::send_msg(
    uint32_t queue_id,
    uint32_t msg_id,
    uint32_t arg,
    uint32_t arg_high,
    uint8_t pack,
    uint8_t decode
) {
  
  bool guard = this->guard_queue(arg);
  if (!guard) {
    const auto& var = this->queue.front().wdone();
    if (var != SmuStatus::Ok) 
      return -1; // complete arbitrary return code lmao i hope no one reads this

  };
  return arg;
};

/*
uint32_t Smu::hi_read(uint32_t read) {
  if (this->guard_queue(read) ) {
    auto& var = this->queue.front(); 
    
  }



};
*/
