#include "bracket_rect.h"
#include "../themes/themes.h"

lv_obj_t* bracket_rect(lv_obj_t *parent, rect_set_t *outside, rect_set_t *inside)
{
    //外层反转色圆角矩形
    lv_obj_t *out_rect = lv_obj_create(parent);
    lv_obj_set_size(out_rect, outside->width, outside->height);
    lv_obj_set_style_radius(out_rect, outside->radius, 0);
    lv_obj_set_style_bg_color(out_rect, lv_color_hex(get_color(BLACK_C)), 0);
    lv_obj_center(out_rect);
    //主题色矩形遮挡
    lv_obj_t *cover_rect = lv_obj_create(out_rect);
    lv_obj_set_size(cover_rect, (outside->width - outside->radius * 4), outside->height);
    lv_obj_center(cover_rect);
    //括号内操作区矩形
    lv_obj_t *work_rect = lv_obj_create(out_rect);
    lv_obj_set_size(work_rect, inside->width, inside->height);
    lv_obj_set_style_radius(work_rect, inside->radius, 0);
    lv_obj_center(work_rect);
    return work_rect;
}