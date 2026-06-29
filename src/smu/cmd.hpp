#import "config.hpp"

#include <iostream>
#include <queue>
#import <cstdint>
#include <array>
#import <vector>
#import <unordered_map>
#import "transport.hpp"
#import "status.hpp"

struct QueueAddr {
  uint8_t id;
  uint32_t cmd;
  uint32_t rptr;
  uint32_t wptr;
};

constexpr std::array<QueueAddr, 5> DEFAULT_QUEUE_ADDRS = {{                                            
   {0, 0x03B10A08, 0x03B10A68, 0x03B10A48},                                                           
   {1, 0x03B10A00, 0x03B10A60, 0x03B10A40},                                                           
   {2, 0x03B10528, 0x03B10564, 0x03B10998},                                                           
   {3, 0x03B10A20, 0x03B10A80, 0x03B10A88},                                                           
   {4, 0x03B10A24, 0x03B10A84, 0x03B10A8C},                                                           
}};

class Smu {
  public:
    CyanTransport trans;
    std::queue<CyanTransport> queue;

    Smu(bool queue, std::string_view buf, uint16_t timeout);
    ~Smu();
    bool guard_queue(uint16_t in);
    uint32_t send_msg(
        uint32_t queue_id,
        uint32_t msg_id,
        uint32_t arg,
        uint32_t arg_high,
        uint8_t pack,
        uint8_t decode
    );

  private:
    uint32_t hi_read();
    uint32_t read();

};
