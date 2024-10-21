#include "speed_info.h"
#include <stdlib.h>
#include <stdio.h>

static lv_obj_t *speed_lable = NULL;


static void update_speed_cb(lv_timer_t *timer);

lv_obj_t * speed_info_zone(lv_obj_t *parent)
{
/* 位置、大小与布局 */
    lv_obj_t *div = lv_obj_create(parent);
    lv_obj_set_size(div, lv_pct(100), lv_pct(32));
    lv_obj_align(div, LV_ALIGN_TOP_LEFT, 0, lv_pct(8));
/* 样式 */
    //速度弹性盒子
    lv_obj_t * speed_box = lv_obj_create(div);
    lv_obj_set_size(speed_box, lv_pct(100), lv_pct(100));
    lv_obj_align(speed_box, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_flex_flow(speed_box, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(speed_box, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END);
    //速度label
    speed_lable = lv_label_create(speed_box);
    lv_obj_set_size(speed_lable, lv_pct(40), lv_pct(80));    
    lv_obj_set_style_pad_top(speed_lable, 75, 0);
    lv_obj_set_style_text_font(speed_lable, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_align(speed_lable, LV_TEXT_ALIGN_RIGHT, 0);
    lv_obj_t *unit_lable = lv_label_create(speed_box);
    lv_obj_set_size(unit_lable, 40, 16);
    lv_label_set_text(unit_lable, "km/h");
    update_speed_cb(NULL);
    //创建一个定时器，每100ms更新一次
    lv_timer_create(update_speed_cb, 500, NULL);
    return div;
}

void update_speed_cb(lv_timer_t *timer)
{
    char speed[4];
    sprintf(speed, "%d", rand()%360);
    lv_label_set_text(speed_lable, speed);
}
