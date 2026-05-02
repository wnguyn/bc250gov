#include "gpu.h"
struct drm_amdgpu_info_device info;



bc_pci new() {
    bc_pci pci;
    snprintf(pci.path, sizeof(str), "/sys/bus/pci/devices/%s/config");
    pci.p = fopen(pci.path, "r+");
    return pci;
}

int pci_readcfg(bc_pci *pci, int pad) {
    uint8_t buf[4] = {0};
    int new = dup(pci->p);
    flock(new, LOCK_UN);
    pread(new, buf, 4, pad);
    close(new);
    int32_t val;
    memcpy(&val, buf, 4);

    return (int32_t)le32toh(val);
} // return offset;
void pc_writecfg(bc_pci *pci, int oft, int cfg) {
    uint8_t buf[4] = {0};
    pwrite(buf, cfg, 4, oft);
}

void pc_readsmu(bc_pci *pci, int n ) {
    pc_writecfg(pci, 0xB8);
    return pc_readcfg(0xBC);

}
void pc_writesmu(bc_pci *pci, int reg, int val) {
    pc_writecfg(pci, 0xB8, reg);
    pc_writecfg(pci, 0xBC, val);
}



bc_gpu new() {
    drmPciBusInfo location = {
        .domain = 0,
        .bus    = 1,
        .dev    = 0,
        .func   = 0,
    }a;
}
