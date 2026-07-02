#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdint.h>
// need later

namespace Codec {
  uint32_t dec_uint32(uint32_t var) {
    return var;
  }
  uint32_t pack_uint32(uint32_t var) {
    return var;
  }
  uint32_t pack_uint16(uint16_t var) {
    uint32_t typecast = var;
    return typecast;

  }
  uint32_t pack_float32(float var) {
    uint32_t out;
    std::memcpy(&out, &var, 4);
    return out;
  }
  uint32_t mv_vid(uint32_t mv) {
    double volts = (double)mv / 1000.0;
    return (uint32_t)std::round((1.55 - volts) / 0.00625);
  }


  uint32_t vid_to_mv(uint32_t vid) {
      double volts = (static_cast<double>(vid) * -0.00625) + 1.55;
      double mv = volts * 1000.0;
      return static_cast<uint32_t>(std::round(mv));
  }

};
