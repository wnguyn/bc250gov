#include <libdrm/amdgpu.h>
#include <libdrm/amdgpu_drm.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <amdgpu.h>

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
    };

}





int main() {
    printf("starting...");
    bc_gpu gpu = bc_gpu_new();
    Config cfg = config_new();
    int current_freq = gpu.freq;

    for (;;) {
        int temp = get_temp();
        switch (temp) {
            case (temp > gpu) && (gpu.max_freq >= gpu.min_freq + step):
                gpu.max_freq -= CHANGE;
                printf("throttling temp becaue of high temp");
            case (cfg.recvy_temp > gpu.temp) && gpu.max_freq != gpu.max_freq:
                gpu.max_freq += scale_temp(*gpu, gpu.step);
        }




        float load = 0.0;
        for (int i = 0; i < 128; i++) {
            load += get_pool(*gpu);
        }





        sleep(cfg.interval);
    }
}
