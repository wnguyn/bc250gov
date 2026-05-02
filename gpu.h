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
    int fd;
    bool use_flock;
    char PATH_MAX;
} bc_pci;

bc_gpu bc_gpu_new();
void get_poll(bc_gpu *g);
void get_temp(bc_gpu *g);
void scale_temp(bc_gpu *g, int scl)
int get_max_freq(bc_gpu *g);
void bc_gpu_updt(bc_gpu *g);


bc_pci pci_new();
int pci_open(pci *g);
void pci_write();
void pci_read();
