#ifndef WATER_SCALE_H
#define WATER_SCALE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"

typedef enum {
    WAT_MODE_1,
    WAT_MODE_2,
    // WAT_MODE_3,
    // WAT_MODE_4,
    WAT_MODE_MAX
} water_mode_t;


static void create_mode_1(lv_obj_t *parent);
static void create_mode_2(lv_obj_t *parent);
static void create_mode_3(lv_obj_t *parent);
static void create_mode_4(lv_obj_t *parent);
extern void water_scale(lv_obj_t *parent);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* WATER_SCALE_H */