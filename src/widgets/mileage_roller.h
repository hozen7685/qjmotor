#ifndef MILEAGE_ROLLER_H
#define MILEAGE_ROLLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#define ROLLER_TEXT_LEN 128
#define ROLLER_ROW      3
extern lv_obj_t * mileage_roller(lv_obj_t *parent);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* MILEAGE_ROLLER_H */