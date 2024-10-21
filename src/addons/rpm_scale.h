#ifndef RPM_SCALE_H
#define RPM_SCALE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#define BAR_MAX     7000
#define RPM_WARN    9000
#define ARC_MAX     12000

extern lv_obj_t* rpm_scale(lv_obj_t *parent);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* RPM_SCALE_H */