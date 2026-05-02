#include "gpu.h"
struct drm_amdgpu_info_device info;



bc_pci new() {
    char str[256];
    snprintf(str, sizeof(str), "/sys/bus/pci/devices/{}/config");
    File *file = fopen(self->config_path, "r+");
    if (file == NULL) { break; }
    return (bc_pci) {
        .path[256] = str[256];
        .use_flock = false;
        .file = file;
    }
}
bc_pci open(bc_pci *p) {
    p->file =
}
