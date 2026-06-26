#include <cstdint>
#include <stdint.h>
// need later


namespace Codec {
  uint32_t dec_uint32(uint32_t var);
  uint32_t pack_uint32(uint32_t var);
  uint32_t pack_uint16(uint16_t var);
  uint32_t pack_float32(float var);
  uint32_t mv_vid(uint32_t var);
  uint32_t vid_mv(uint32_t var);

};
