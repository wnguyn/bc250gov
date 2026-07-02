#include <vector>
#include <tuple>
#include <cstdint>


enum Profile {
  PERF,
  IDLE,
  LOW,
};
struct Core {
  uint32_t total;
  uint32_t idle;
};
struct CpuStatus {
  std::vector<Core> stats;
};



struct Time {
  uint32_t interval;
  uint32_t freq_check; // check the rate we check to lower freq (in seconds)
  uint32_t ramp_rate; // scalar quantity of the ramp rate [1,3]
  uint32_t idle_thresh; // how many cpu events that we qualify as "active"
  uint32_t throt;
};
struct SafePt {
  uint16_t freq;
  float volt;
  Profile prof;
};

class Config {
  public:
    std::vector<SafePt> safe_pt;
    Time timing;
    std::tuple<int, int> load_target;
    uint32_t big_step;

    Config(); // make this edible in a YAML or .jsonc later
    ~Config();

  private:
    std::vector<SafePt> get_safe_pts();
    Time load_default_timing();
    std::tuple<uint32_t, uint32_t> load_default_target();
    

    

};
