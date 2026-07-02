#include "policy.hpp"

void smu_init_idle(APU& gpu) {
  Smu& s = gpu.smu;

  uint32_t safe = (1u << 17) | (1u << 19) | (1u << 7)
                | (1u << 8)  | (1u << 9)  | (1u << 14);

  uint32_t before = s.get_enabled_smu();
  s.q3_enable_smu_features(before | safe);

  s.set_min_gfxclk(0);
  s.set_max_deep_sleep(0xFF);
  s.q3_set_perf_profile_index(0);
  s.q3_set_soc_clock(0);
  s.q3_vid_main_limit(800);
  for (uint8_t c = 0; c < 6; c++) {
    s.set_soft_minclck(c, 0);
    s.set_soft_maxclck(c, 1200);
  }
  s.unforce_gfx_freq();
}
