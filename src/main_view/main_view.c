#include "main_view.h"
#include "../addons/top_info_bar.h"
#include "../addons/speed_info.h"
#include "../addons/bracket_rect.h"
#include "../themes/themes.h"
#include "../addons/rpm_scale.h"
#include "../addons/water_scale.h"
#include <stdio.h>

static char roller_text[ROLLER_TEXT_LEN] = {0};
static lv_obj_t * mileage_roller = NULL;
static void update_mileage_cb(lv_timer_t *timer) {
    sprintf(roller_text, "TOT :%.1fkm\nTRIPA :%.1fkm\nTRIPB :%.1fkm",
     rand()%100, rand()%100, rand()%100);
    lv_roller_set_options(mileage_roller, roller_text, LV_ROLLER_MODE_INFINITE);
}

void main_view(void)
{
    lv_obj_t * obj = lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_pad_left(obj, 16, 0);

    top_info_bar(obj);
    speed_info_zone(obj);
    rpm_scale(obj);
/* 油表 水温*/
    water_scale(obj);
/* 公里数 */
    lv_obj_t * mileage_canvas = lv_obj_create(obj);
    lv_obj_set_size(mileage_canvas, 255, 38);
    lv_obj_align(mileage_canvas, LV_ALIGN_TOP_LEFT, lv_pct(31), lv_pct(50));
    rect_set_t outside2 = {255, 38, 3};
    rect_set_t inside2 = {251, 34, 3};
    lv_obj_t * mileage_obj = bracket_rect(mileage_canvas, &outside2, &inside2);

    mileage_roller = lv_roller_create(mileage_obj);
    lv_obj_set_style_text_color(mileage_roller, lv_color_hex(get_color(BLACK_C)), LV_PART_MAIN);
    lv_obj_set_size(mileage_roller, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(mileage_roller, lv_color_hex(get_color(WHITE_C)), LV_PART_SELECTED);
    lv_obj_set_style_text_color(mileage_roller, lv_color_hex(get_color(BLACK_C)), LV_PART_SELECTED);
    lv_obj_align(mileage_roller, LV_ALIGN_CENTER, 0, 0);
    // lv_roller_set_options(mileage_roller, roller_text, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(mileage_roller, 1);
    // lv_obj_add_event_cb(mileage_roller, event_handler, LV_EVENT_ALL, NULL);
    // lv_timer_create(update_mileage_cb, 10000, NULL);
}
