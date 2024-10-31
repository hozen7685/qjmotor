/******************************************************************************
 *  Copyright 2024
 *
 *  @file    gui_guider.c
 *
 *  @brief
 *
 *=============================================================================
 *  Revision History
 *  Version     Date        Author      Content
 *  -------     ----------  ---------   ---------------------------------------
 *  V1.00       2024/10/30  caohz       Create.
 *
 *****************************************************************************/

/******************************************************************************
 *
 * INCLUDES
 *
 *****************************************************************************/
#include "gui_guider.h"

/******************************************************************************
 *
 * FUNCTIONS
 *
 *****************************************************************************/
extern scr_data_t scr_home_data;
extern scr_data_t scr_menu_data;

static scr_data_t *scr_data_list[] = {
    &scr_home_data,
    &scr_menu_data
};

static scr_data_t * get_scr_data_by_id(scr_id_t id)
{
    return scr_data_list[id];
}

void gui_load_scr_animation(scr_id_t new_scr, scr_data_t * old_scr,
    lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del)
{
    lv_obj_t * act_scr = lv_screen_active();
    scr_data_t * new_scr_data = get_scr_data_by_id(new_scr);
    if (auto_del && is_clean) {
        lv_obj_clean(act_scr);
    }
    if (new_scr_data->scr_del) {
        new_scr_data->scr_obj = new_scr_data->paint(NULL);
    }
    lv_screen_load_anim(new_scr_data->scr_obj, anim_type, time, delay, auto_del);
    old_scr->scr_del = auto_del;
}

void gui_setup(void)
{
    scr_home_data.scr_obj = scr_home_data.paint(NULL);
    lv_screen_load(scr_home_data.scr_obj);
}
/* - End Of File - */
