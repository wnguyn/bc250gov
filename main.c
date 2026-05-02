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
    int safepts[2];
    int interval;
    float threshd;
    int voltage;
    int throttling_tmp;
    int recvry_tmp;
} Config;

int main() {
    printf("starting...");
    bc_gpu gpu = bc_gpu_new();
    int current_freq = gpu.freq;
    int load = 0;
    for (;;) {
        /* to be added later */


    }
}
