#ifndef GASOLINE_SCALE_H
#define GASOLINE_SCALE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "lvgl.h"

typedef enum {
    GAS_MODE_1,
    GAS_MODE_2,
    // GAS_MODE_3,
    // GAS_MODE_4,
    GAS_MODE_MAX
} gaso_mode_t;


static void create_mode_1(lv_obj_t *parent);
static void create_mode_2(lv_obj_t *parent);
static void create_mode_3(lv_obj_t *parent);
static void create_mode_4(lv_obj_t *parent);
extern void gasoline_scale(lv_obj_t *parent);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* GASOLINE_SCALE_H */