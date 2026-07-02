#import "policy.hpp"


uint32_t Idle::get_enabled_smu(APU * gpu) {



};


void Idle::smu_init_idle(APU* gpu) {
  // enable safe-ish (wow) idles 
  uint32_t safe = (1u << 17) | (1u << 19) | (1u << 7) | (1u << 8) | (1u << 9) | (1u << 14); // fancy version of 0x000A4380 
  uint32_t before = Idle::get_enabled_smu(gpu);
  gpu->smu.q3_enable_smu_features();
  std::cout << "told smu value: " << safe << "and enabled?? \n";
  gpu->smu.set_min_gfxclk(0);
  gpu->smu.set_max_deep_sleep(0xFF);
  gpu->smu.q3_set_perf_profile_index(0);
  gpu->smu.q3_set_soc_clock(0);
  gpu->smu.q3_vid_main_limit(800);
  gpu->smu.unforce_gfx_freq();
  gpu->smu.unforce_gfx_vid();

  for(int i = 0; i < 7; i++) 
    gpu->smu.set_soft_minclck();
  std::cout << "done...";



}


