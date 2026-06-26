#include <vector>
#include <tuple>



enum Profile {
  PERF,
  IDLE,
  LOW,
};



struct Time {
  int interval;
  int freq_check; // check the rate we check to lower freq (in seconds)
  int ramp_rate; // scalar quantity of the ramp rate [1,3]
  int idle_thresh; // how many cpu events that we qualify as "active"
};
struct SafePt {
  int freq;
  int volt;
  Profile prof;
};

class Config {
  public:
    std::vector<SafePt> safe_pt;
    Time timing;
    std::tuple<int, int> load_target;

    Config(); // make this edible in a YAML or .jsonc later
    ~Config();

  private:
    std::vector<SafePt> get_safe_pts();
    Time load_default_timing();
    std::tuple<int, int> load_default_target();
    

    

};
