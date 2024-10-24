#include "mileage_roller.h"
#include "setting.h"
#include "bracket_rect.h"
#include "../themes/themes.h"
#include <stdio.h>
#include <stdlib.h>

static char roller_text[ROLLER_TEXT_LEN] = {0};
const char *default_text = "TOT :0.0km\nTRIPA :0.0km\nTRIPB :0.0km";
static lv_obj_t * roller = NULL;

static void update_mileage_cb(lv_timer_t *timer) {
    uint32_t sel_index = lv_roller_get_selected(roller);
    snprintf(roller_text, ROLLER_TEXT_LEN - 1, "TOT :%.1fkm\nTRIPA :%.1fkm\nTRIPB :%.1fkm",
     (float)(rand()%100), (float)(rand()%100), (float)(rand()%100));
    lv_roller_set_options(roller, roller_text, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_selected(roller, sel_index, LV_ANIM_ON);
}

lv_obj_t * mileage_roller(lv_obj_t *parent)
{
    lv_obj_t * mileage_canvas = lv_obj_create(parent);
    lv_obj_set_size(mileage_canvas, 255, 38);
    lv_obj_align(mileage_canvas, LV_ALIGN_TOP_LEFT, lv_pct(31), lv_pct(50));
    rect_set_t outside2 = {255, 38, 3};
    rect_set_t inside2 = {251, 34, 3};
    lv_obj_t * mileage_obj = bracket_rect(mileage_canvas, &outside2, &inside2);

    roller = lv_roller_create(mileage_obj);
    lv_obj_set_style_text_color(roller, lv_color_hex(get_color(BLACK_C)), LV_PART_MAIN);
    lv_obj_set_size(roller, lv_pct(100), lv_pct(100));
    lv_obj_set_style_bg_color(roller, lv_color_hex(get_color(WHITE_C)), LV_PART_SELECTED);
    lv_obj_set_style_text_color(roller, lv_color_hex(get_color(BLACK_C)), LV_PART_SELECTED);
    lv_obj_align(roller, LV_ALIGN_CENTER, 0, 0);
    lv_roller_set_options(roller, default_text, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(roller, 1);
    lv_timer_create(update_mileage_cb, 5000, NULL);
    return roller;
}
