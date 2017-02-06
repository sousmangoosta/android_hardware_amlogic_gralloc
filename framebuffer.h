#ifndef FRAMEBUFFER_API_H_
#define FRAMEBUFFER_API_H_

#include <hardware/hardware.h>

struct private_handle_t;
struct private_module_t;

enum {
    GLES_COMPOSE_MODE = 0,
    DIRECT_COMPOSE_MODE = 1,
    GE2D_COMPOSE_MODE = 2,
};

typedef struct framebuffer_info_t{
    // gralloc module.
    private_module_t *grallocModule;

    buffer_handle_t currentBuffer;

    //set by device.
    int   displayType;
    int   fbIdx;

    //information get from osd
    struct fb_var_screeninfo info;//need to fbpost
    struct fb_fix_screeninfo finfo;

    int   fd;//for fbpost use
    int   fbSize;

    float xdpi;
    float ydpi;
    float fps;
    int   flipFlags;

    // Composer mode.
    int   renderMode;

    // GE2D composer mode used only.
    int   yOffset;

    // osd blank option.
    unsigned int op;
}framebuffer_info_t;

#define ION_IOC_MESON_PHYS_ADDR 8

struct meson_phys_data{
    int handle;
    unsigned int phys_addr;
    unsigned int size;
};

// get ion physical address.
uint32_t getIonPhyAddr(struct framebuffer_info_t* fbinfo, buffer_handle_t hnd);

// Initialize the framebuffer (must keep module lock before calling
int init_frame_buffer_locked(struct framebuffer_info_t* info);

#ifndef SINGLE_EXTERNAL_DISPLAY_USE_FB1
int init_cursor_buffer_locked(struct framebuffer_info_t* info);
int update_cursor_buffer_locked(struct framebuffer_info_t* cbinfo, int xres, int yres);
#endif

int fb_post_locked(struct framebuffer_info_t* fbinfo,buffer_handle_t buffer);
int fb_post_with_fence_locked(struct framebuffer_info_t* fbinfo,buffer_handle_t hnd,int in_fence);
int hwc_fb_post_with_fence_locked(struct framebuffer_info_t* fbinfo,buffer_handle_t hnd,int in_fence);
int getOsdIdx(int display_type);
int bits_per_pixel();

//for egl to get framebuffer count
extern unsigned int get_num_fb_buffers();
extern bool osd_afbcd_enable();

#endif
