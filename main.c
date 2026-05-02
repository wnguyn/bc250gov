#include <libdrm/amdgpu.h>
#include <libdrm/amdgpu_drm.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

#include "toml.h"
#include "gpu.h"
typedef struct {
    int safepts[8];
    int interval;
    float threshd;
    int throttling_tmp;
    int recvry_tmp;
    int step;
} Config;

typedef enum {
    GOV_IDLE,
    GOV_UP,
    GOV_DOWN
} GovState;

int target_freq(GovState *g, bc_gpu *gpu) {

}

/* Change the cfg DWM Style */
#define CHANGE 500
Config config_new() {
    printf("setting config");
    return (Config) {
        .safepts[8] = {
            {350,  700, 1},
            {1000, 800, 2},
            {1175, 850, 3},
            {1600, 910, 3},
            {1850, 930, 3},
            {2050, 980, 3},
            {2125, 1020, 3},
            {2200, 1050, 3},
        }
        .step = 50;
        .recvry_temp = 70;
        .throttling_tmp = 85;
        .threshd = 50.0;
        .burst = 500; /* burst freq if you need sharp perf */
    };
}

int main() {
    printf("starting...");
    bc_gpu gpu = bc_gpu_new();
    Config cfg = config_new();
    int current_freq = gpu.freq;
    int status = 0;
    GOV_STATE pwr_state = GOV_IDLE;
    while (true) {
        int temp = get_temp();
        switch (temp) {
            case (temp > gpu) && (gpu.max_freq >= gpu.min_freq + step):
                gpu.max_freq -= CHANGE;
                printf("throttling temp becaue of high temp");
            case (cfg.recvy_temp > gpu.temp) && gpu.max_freq != gpu.max_freq:
                gpu.max_freq += scale_temp(*gpu, gpu.step);
                printf("scaling back up b/c it's at a low temp");
        }
        float load = 0.0;
        for (int i = 0; i < 128; i++) {
            int sum += get_pool(*gpu);
        }
        int avg_load = sum / 128;
        if (avg_load > cfg.threshd) {
            pwr_state = GOV_UP;
        } else if (avg_load < cfg.threshd_down && current_freq > gpu.min_freq)  {
            pwr_state = GOV_DOWN;
        } else {
            pwr_state GOV_IDLE;
        }
        int target = target_freq(*pwr_state, *gpu);
        if (gpu.freq != target) {
            printf("clocking up due to idle....");
            bc_gpu_updt(*g);
            gpu.freq = target;
        }
        sleep(cfg.interval);
        bc_gpu_updt(*g );
    }
}
