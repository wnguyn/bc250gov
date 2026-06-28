#include "config.hpp"
#include <vector>
#include <cstdint>
/* 
 * TODO don't hard code later on and let user configure it on their own (step 19028313)
*/

std::vector<SafePt> Config::get_safe_pts() { 
  std::vector<SafePt> safe_pt;

  SafePt pt_1 = SafePt {
    .freq = 1000,
    .volt = 800,
    .prof = LOW,
  };
  safe_pt.push_back(std::move(pt_1));

  SafePt pt_2 = SafePt {
    .freq = 1175,
    .volt = 850,
    .prof = IDLE,
  };
  safe_pt.push_back(std::move(pt_2));

  SafePt pt_3 = SafePt {
    .freq = 1200,
    .volt = 750,
    .prof = PERF,
  };
  safe_pt.push_back(std::move(pt_3));


  return safe_pt;
};


Time Config::load_default_timing() {
  Time tme = Time {
    .interval = 10,
    .freq_check = 60,
    .ramp_rate = 2,
    .idle_thresh = 10, // change later
  };
  return tme;


};


std::tuple<int, int> Config::load_default_target() {
  std::tuple<int, int> turp(32, 64); // placeholder value
  return turp;

};


Config::Config() {
  this->safe_pt = get_safe_pts();
  this->load_target = load_default_target();
  this->timing = load_default_timing();

};
Config::~Config() {
  // implement later when user can choose their own values
};

