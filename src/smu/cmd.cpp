#include "cmd.hpp"
#include "codec.hpp"

Smu::Smu(bool queue, std::string buf, uint16_t timeout) : trans(buf) {
  int i = 0;
  for (const auto& [id, cmd, rptr, wptr] : DEFAULT_QUEUE_ADDRS)
    queues[i++] = CyanBox(&trans, cmd, rptr, wptr, timeout);
}

Smu::~Smu() {}

bool Smu::guard_queue(uint32_t queue) {
  return queue != 0;
}

uint32_t Smu::send_msg(
    uint32_t queue_id,
    uint32_t msg_id,
    uint32_t arg,
    uint32_t arg_high,
    uint8_t pack,
    uint8_t decode
) {
  if (queue_id == 0 || queue_id >= 5) return -1;
  uint32_t packed = pack ? Codec::pack_uint32(arg) : arg;
  queues[queue_id].send(msg_id, packed, arg_high);
  if (decode) return queues[queue_id].read();
  return 0;
}

void   Smu::set_min_gfxclk(uint32_t mhz)         { send_msg(0, 0x19, mhz, 0, 1, 0); }
void   Smu::set_max_deep_sleep(uint32_t div)      { send_msg(0, 0x1A, div, 0, 1, 0); }
uint32_t Smu::force_gfx_freq(uint32_t mhz)        { return send_msg(0, 0x39, mhz, 0, 1, 0); }
uint32_t Smu::unforce_gfx_freq()                  { return send_msg(0, 0x3A, 0, 0, 0, 0); }
uint32_t Smu::force_gfx_vid(uint32_t mv)          { return send_msg(0, 0x3B, Codec::mv_vid(mv), 0, 1, 0); }
uint32_t Smu::unforce_gfx_vid()                   { return send_msg(0, 0x3C, 0, 0, 0, 0); }
uint32_t Smu::get_enabled_smu()                   { return send_msg(0, 0x3D, 0, 0, 1, 1); }
uint32_t Smu::set_soft_minclck(uint8_t c, uint16_t m) { return send_msg(0, 0x35, ((uint32_t)c << 20) | m, 0, 1, 0); }
uint32_t Smu::set_soft_maxclck(uint8_t c, uint16_t m) { return send_msg(0, 0x36, ((uint32_t)c << 20) | m, 0, 1, 1); }

uint32_t Smu::q3_set_perf_profile_index(uint32_t idx) { return send_msg(3, 0x1E, idx, 0, 1, 0); }
uint32_t Smu::q3_enable_smu_features(uint32_t mask)   { return send_msg(3, 0x3C, mask, 0, 1, 0); }
uint32_t Smu::q3_set_soc_clock(uint32_t level)        { return send_msg(3, 0x1D, level, 0, 1, 0); }
uint32_t Smu::q3_disable_smu_features(uint32_t mask)  { return send_msg(3, 0x3D, mask, 0, 1, 0); }
uint32_t Smu::q3_vid_main_limit(uint32_t mv)          { return send_msg(3, 0x8E, mv, 0, 1, 0); }
uint32_t Smu::set_gpu_max_temp(uint32_t c)            { return send_msg(3, 0x8C, c, 0, 1, 0); }
uint32_t Smu::find_dfste()                             { return send_msg(0, 0x13, 0, 0, 0, 1); }
