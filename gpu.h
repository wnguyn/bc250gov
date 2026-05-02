#include <amdgpu.h>
#include <stdbool.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>




typedef struct {
    int samples;
    int max_freq;
    int min_freq;
    int freq;
    amdgpu_device_handle dev_handle;
} bc_gpu;



typedef struct {
    char path[256];
    FILE *p;
} bc_pci;

bc_gpu bc_gpu_new();
void get_poll(bc_gpu *g);
void get_temp(bc_gpu *g);
void scale_temp(bc_gpu *g, int scl);
int get_max_freq(bc_gpu *g);
void bc_gpu_updt(bc_gpu *g);


bc_pci pci_new_open();
int pci_readcfg(bc_pci *p, int oft, int cfg);
void pci_readsmu(bc_pci *p, int n );
void pci_writesmu(bc_pci *p, int value);

bc_smu bc_smu_new();
