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
#include "home_scr.h"
#include "../guif/guif_if.h"
#include "../widgets/speed_info.h"
#include "../widgets/rpm_scale.h"
#include "../widgets/gasoline_scale.h"
#include "../widgets/water_scale.h"
#include "../widgets/mileage_roller.h"
#include "../addons/top_info_bar.h"
/******************************************************************************
 *
 * FUNCTIONS
 *
 *****************************************************************************/
static void scr_home_show(void * own)
{
    lv_screen_load_anim((lv_obj_t *)own, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 500, 1000, false);
    load_top_info_bar((lv_obj_t *)own);
}

static void scr_home_load(void * own)
{
    lv_screen_load((lv_obj_t *)own);
    load_top_info_bar((lv_obj_t *)own);
}

static void scr_home_unload(void * own)
{
    unload_top_info_bar();
    lv_obj_delete((lv_obj_t *)own);
}

guif_scr_method_t scr_home_method = {
    home_screen, scr_home_load, scr_home_unload, scr_home_show
};

guif_scr_obj_t scr_home_obj = {
    SCR_HOME, NULL, &scr_home_method
};
/***********************************************/
static void event_handler(lv_event_t * e)
{
    lv_event_code_t evt_code = lv_event_get_code(e);
    lv_key_t key_code = lv_indev_get_key(lv_indev_active());
    switch (key_code)
    {
    case LV_KEY_ENTER:
        guif_scr_change(SCR_MENU);
        break;
    default:
        break;
    }
    // LV_LOG_USER("EVEVT CODE [%d];KEY CODE [%d]\n", evt_code, key_code);
}

void * home_screen(void * parent)
{
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
    lv_obj_t * catch_obj = mileage_roller(obj);
/* 按键捕获 */
    lv_obj_add_event_cb(catch_obj, event_handler, LV_EVENT_ALL, NULL);
    return (void *)obj;
}

/* - End Of File - */
