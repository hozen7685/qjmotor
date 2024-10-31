/******************************************************************************
 *  Copyright 2024
 *
 *  @file    menu_scr.c
 *
 *  @brief
 *
 *=============================================================================
 *  Revision History
 *  Version     Date        Author      Content
 *  -------     ----------  ---------   ---------------------------------------
 *  V1.00       2024/10/25  caohz       Create.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * INCLUDES
 *
 *****************************************************************************/
#include "../gui/gui_guider.h"
#include "../themes/themes.h"
#include "../widgets/bracket_rect.h"
#include "../widgets/top_info_bar.h"
/******************************************************************************
 *
 * FUNCTIONS
 *
 *****************************************************************************/
static lv_style_t style_sel;
static lv_obj_t * roller;
static lv_obj_t * scr_menu_paint(lv_obj_t *p);

#if USE_GUIF
static void scr_menu_show(void * own)
{
    LV_LOG_USER("scr_menu_show");
    lv_screen_load_anim((lv_obj_t *)own, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true);
    load_top_info_bar((lv_obj_t *)own);
    // lv_obj_set_state(roller, LV_STATE_DISABLED, false);
}

static void scr_menu_hide(void * own)
{
    LV_LOG_USER("scr_menu_hide");
    unload_top_info_bar();
    // lv_obj_set_state(roller, LV_STATE_DISABLED, true);
}

static void scr_menu_load(void * own)
{
    LV_LOG_USER("scr_menu_load");
    lv_screen_load_anim((lv_obj_t *)own, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, true);
    load_top_info_bar((lv_obj_t *)own);
    // lv_obj_set_state(roller, LV_STATE_DISABLED, false);
}

static void scr_menu_unload(void * own)
{
    LV_LOG_USER("scr_menu_unload");
    lv_obj_clean(lv_screen_active());
}

guif_scr_method_t scr_menu_method = {
    scr_menu_paint, scr_menu_load, scr_menu_unload, scr_menu_show, scr_menu_hide
};

guif_scr_obj_t scr_menu_obj = {
    SCR_MENU, NULL, &scr_menu_method
};
#endif /* USE_GUIF */

scr_data_t scr_menu_data = {NULL, true, scr_menu_paint};
/***************************************************/
static void event_handler(lv_event_t * e)
{
    lv_event_code_t evt_code = lv_event_get_code(e);
    lv_key_t key_code = lv_indev_get_key(lv_indev_active());
    switch (key_code)
    {
    case LV_KEY_ESC:
        if(LV_EVENT_DEFOCUSED == evt_code) {
            LV_LOG_USER("EVEVT CODE [%d];KEY CODE [%d]\n", evt_code, key_code);
        }
        break;
    default:
        break;
    }
}

lv_obj_t * scr_menu_paint(lv_obj_t *p)
{
    LV_LOG_USER("scr_menu_paint");
    lv_style_init(&style_sel);
    lv_style_set_bg_color(&style_sel, lv_color_hex(get_color(WHITE_C)));
    lv_style_set_text_color(&style_sel, lv_color_hex(get_color(BLACK_C)));

    lv_obj_t * obj = lv_obj_create(NULL);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_center(obj);

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
    return obj;
}
/* - End Of File - */
