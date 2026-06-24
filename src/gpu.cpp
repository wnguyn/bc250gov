#include "gpu.h"
struct drm_amdgpu_info_device info;



bc_pci bc_pci_new() {
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

bc_gpu bc_gpu_new() {
    GPU gpu = {0};
    char vendor_path[512];
    char device_path[512];
    gpu.location = (BUS_INFO) {
        .domain = 0,
        .bus = 1,
        .dev = 0,
        .func = 0,
    };
    snprintf(
        gpu.sysfs_path,
        sizeof(gpu.sysfs_path),
        "/sys/bus/pci/devices/%04x:%02x:%02x.%1u",
        gpu.location.domain,
        gpu.location.bus,
        gpu.location.dev,
        gpu.location.func
    );

    snprintf(vendor_path, sizeof(vendor_path), "%s/vendor", gpu.sysfs_path);
    snprintf(device_path, sizeof(device_path), "%s/device", gpu.sysfs_path);
    read_text_file(vendor_path, gpu.vendor, sizeof(gpu.vendor));
    read_text_file(device_path, gpu.device, sizeof(gpu.device));
    gpu.min_freq = safe_points[0].freq;
    gpu.max_freq = safe_points[safe_point_count - 1].freq;
    return gpu;
}
int get_temp(bc_gpu *p) {
    uint32_t temp;
    int ret = amdgpu_query_sensor_info
        (p->def_handle, AMDGPU_INFO_SENSOR_GPU_TEMP, sizeof(temp), &temp);
    return (temp / 10000);
}
