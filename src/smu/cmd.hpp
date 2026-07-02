/*  handle actual interaction with the Bc250Smu */


#import "config.hpp"

#include <queue>
#import <cstdint>
#include <array>
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
    std::queue<CyanBox> queue;

    Smu(bool queue, std::string buf, uint16_t timeout);
    ~Smu();
    bool guard_queue(uint32_t in);

    uint32_t send_msg(
        uint32_t queue_id,
        uint32_t msg_id,
        uint32_t arg,
        uint32_t arg_high,
        uint8_t pack,
        uint8_t decode
    );
    // tons of smu functions to actually do stuff
    uint32_t get_smu_version();
    uint32_t get_driver_version();
    uint32_t set_dram_high(uint32_t var);
    uint32_t set_dram_low(uint32_t var);
    uint32_t smu_dram();
    uint32_t dram_smu();
    uint32_t req_pstate();
    uint32_t find_pstate();
    uint32_t vddcr_soc(uint8_t var);
    uint32_t find_dfste();
    uint32_t hi_s3_pwroff(uint32_t var);
    uint32_t lo_s3_pwroff(uint32_t var);
    void req_wgp();
    void set_min_gfxclk();
    void set_max_deep_sleep();
    void start_telem();
    void clear_telem();
    uint32_t find_active_wgp();
    uint32_t get_gfx_fq();
    uint32_t get_gfx_vid();
    uint32_t force_gfx_frq();
    uint32_t unforce_gfx_freq();
    uint32_t force_gfx_vid();
    uint32_t unforce_gfx_vid();
    uint32_t get_enabled_smu();
    uint32_t set_core_enable();
    uint32_t gfx_cac();
    uint32_t l3_cac();
    uint32_t pac_core();
    void driver_taple();
    uint32_t set_soft_minclck();
    uint32_t set_hard_minclock();

    uint32_t q1_msg_0x08();
    uint32_t q1_msg_0x10();
    uint32_t q2_gt_constant();
    // std::string get_devname(uint32_t idx);
    /*
     * Fuck around with 0x07,
     * 0x08,
     * 0x09,
     * 0x0A,
     * 0x0B
     * 0x0b
     * 0x0c
     * 0x0F
     * 0x10
     * 0x13
     * 0x14
     * 0x15
     * 0x16
     * 0x1a 
     * 0x20
     * 0x21
     * 0x29
     * 0x2f
     * 0x30
     * later.....
     * also implement more later but 
     */


  private:
    uint32_t hi_read(uint32_t queue);
    /*
    uint32_t read(uint32_t queue);
    */

};
