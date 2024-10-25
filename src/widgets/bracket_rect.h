#ifndef BRACKET_RECT_H
#define BRACKET_RECT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "setting.h"

extern lv_obj_t* bracket_rect(lv_obj_t *parent, rect_set_t *outside, rect_set_t *inside);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* BRACKET_RECT_H */