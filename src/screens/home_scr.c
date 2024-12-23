/******************************************************************************
 *  Copyright 2024
 *
 *  @file    home_scr.c
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
#include "../widgets/speed_info.h"
#include "../widgets/rpm_scale.h"
#include "../widgets/gasoline_scale.h"
#include "../widgets/water_scale.h"
#include "../widgets/mileage_roller.h"
#include "../widgets/top_info_bar.h"
/******************************************************************************
 *
 * FUNCTIONS
 *
 *****************************************************************************/
lv_obj_t * roller_obj = NULL;

static lv_obj_t * scr_home_paint(lv_obj_t * parent);

scr_data_t scr_home_data = {NULL, true, scr_home_paint};
/***********************************************/
static void event_handler(lv_event_t * e)
{
    lv_event_code_t evt_code = lv_event_get_code(e);
    lv_key_t key_code = lv_indev_get_key(lv_indev_active());
    switch (key_code)
    {
    case LV_KEY_ENTER:
        if(LV_EVENT_SHORT_CLICKED == evt_code) {
            unload_top_info_bar();
            gui_load_scr_animation(SCR_MENU, &scr_home_data,
             LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 200, true, true);
            LV_LOG_USER("EVEVT CODE [%d];KEY CODE [%d]\n", evt_code, key_code);
        }
        break;
    default:
        break;
    }
}

lv_obj_t * scr_home_paint(lv_obj_t * parent)
{
    LV_LOG_USER("paint");
    lv_obj_t * obj = lv_obj_create(NULL);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_pad_left(obj, 16, 0);
    lv_obj_center(obj);
/* 速度 */
    speed_info_zone(obj);
/* 转速条 */
    rpm_scale(obj);
/* 油表*/
    gasoline_scale(obj);
/* 水温 */
    water_scale(obj);
/* 公里数 */
    roller_obj = mileage_roller(obj);
/* 按键捕获 */
    lv_obj_add_event_cb(roller_obj, event_handler, LV_EVENT_ALL, NULL);
    load_top_info_bar(obj);
    return obj;
}

/* - End Of File - */
