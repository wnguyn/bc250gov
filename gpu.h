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


bc_pci bc_pci_new();
int bc_pci_open();
void bc_pci_write();
void bc_pci_read();
