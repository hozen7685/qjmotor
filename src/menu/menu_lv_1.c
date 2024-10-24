#include "menu_lv_1.h"
#include "../themes/themes.h"
#include "../addons/top_info_bar.h"
#include "../themes/color.h"
#include "../addons/bracket_rect.h"

static lv_style_t style_sel;
static lv_obj_t * roller;

static void event_handler(lv_event_t * e)
{
    lv_event_code_t evt_code = lv_event_get_code(e);
    lv_key_t key_code = lv_indev_get_key(lv_indev_active());
    LV_LOG_USER("EVEVT CODE [%d];KEY CODE [%d]\n", evt_code, key_code);
}

void menu_lv_1_page(void)
{
    lv_style_init(&style_sel);
    lv_style_set_bg_color(&style_sel, lv_color_hex(get_color(WHITE_C)));
    lv_style_set_text_color(&style_sel, lv_color_hex(get_color(BLACK_C)));

    lv_obj_t * obj = lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj, 800, 480);
    lv_obj_center(obj);

    top_info_bar(obj);
    lv_obj_t * rect_canvas = lv_obj_create(obj);
    lv_obj_set_size(rect_canvas, lv_pct(90), lv_pct(10));
    lv_obj_center(rect_canvas);
    rect_set_t outside = {720, 48, 6};
    rect_set_t inside = {712, 40, 3};
    bracket_rect(rect_canvas, &outside, &inside);

    roller = lv_roller_create(obj);
    lv_obj_set_style_text_color(roller, lv_color_hex(get_color(GRAY_C)), LV_PART_MAIN);
    lv_obj_add_style(roller, &style_sel, LV_PART_SELECTED);
    lv_obj_set_size(roller, lv_pct(80), lv_pct(30));
    lv_obj_align(roller, LV_ALIGN_CENTER, 0, 0);
    lv_roller_set_options(roller, get_text_byid(T_MENU_LV1), LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(roller, 3);
    lv_obj_add_event_cb(roller, event_handler, LV_EVENT_ALL, NULL);

    lv_obj_t * foot_label = lv_label_create(obj);
    lv_obj_set_size(foot_label, lv_pct(100), lv_pct(8));
    lv_obj_align(foot_label, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_label_set_text(foot_label, get_text_byid(T_MENU_FOOT));
}