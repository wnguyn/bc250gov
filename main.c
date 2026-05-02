#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "toml.h"
#include "gpu.h"

typedef struct {
    int safepts[8];
    int interval;
    float threshd;
    float threshd_down;
    int throttling_temp;
    int recovery_temp;
    int step;
    int burst;
} Config;

typedef enum {
    GOV_IDLE,
    GOV_UP,
    GOV_DOWN
} GovState;

#define CHANGE 500

static int target_freq(GovState state, const bc_gpu *gpu, const Config *cfg)
{
    if (gpu == NULL || cfg == NULL) {
        return 0;
    }

    switch (state) {
    case GOV_UP:
        if (gpu->freq + cfg->step > gpu->max_freq) {
            return gpu->max_freq;
        }
        return gpu->freq + cfg->step;
    case GOV_DOWN:
        if (gpu->freq - CHANGE < gpu->min_freq) {
            return gpu->min_freq;
        }
        return gpu->freq - CHANGE;
    case GOV_IDLE:
    default:
        return gpu->freq;
    }
}

static Config config_new(void)
{
    Config cfg = {
        .safepts = {350, 1000, 1175, 1600, 1850, 2050, 2125, 2200},
        .interval = 1,
        .threshd = 50.0f,
        .threshd_down = 25.0f,
        .throttling_temp = 85,
        .recovery_temp = 70,
        .step = 50,
        .burst = 500,
    };

    return cfg;
}

int main(void)
{
    bc_gpu gpu = bc_gpu_new();
    Config cfg = config_new();
    GovState pwr_state = GOV_IDLE;

    printf("starting...\n");

    while (true) {
        int temp = get_temp(&gpu);
        int sum = 0;
        int avg_load;
        int target;

        if (temp > cfg.throttling_temp &&
            gpu.max_freq >= gpu.min_freq + cfg.step) {
            gpu.max_freq -= CHANGE;
            printf("throttling temp because of high temp\n");
        } else if (cfg.recovery_temp > gpu.temp &&
                   gpu.max_freq != get_max_freq(&gpu)) {
            gpu.max_freq += scale_temp(&gpu, gpu.step);
            printf("scaling back up because it's at a low temp\n");
        }

        for (int i = 0; i < gpu.samples; i++) {
            sum += get_poll(&gpu);
        }

        avg_load = sum / gpu.samples;

        if (avg_load > cfg.threshd) {
            pwr_state = GOV_UP;
        } else if (avg_load < cfg.threshd_down &&
                   gpu.freq > gpu.min_freq) {
            pwr_state = GOV_DOWN;
        } else {
            pwr_state = GOV_IDLE;
        }

        target = target_freq(pwr_state, &gpu, &cfg);
        if (gpu.freq != target) {
            printf("updating frequency\n");
            bc_gpu_updt(&gpu);
            gpu.freq = target;
        }

        sleep((unsigned)cfg.interval);
        bc_gpu_updt(&gpu);
    }
}
