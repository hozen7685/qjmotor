/******************************************************************************
 *  Copyright 2024
 *
 *  @file    gui_guider.h
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
#ifndef __GUI_GUIDER_H__
#define __GUI_GUIDER_H__

#include "lvgl.h"

typedef enum scr_id{
    SCR_HOME,
    SCR_MENU,
    SCR_UNDEFINE
}scr_id_t;

typedef struct scr_data
{
    lv_obj_t *scr_obj;
	bool scr_del;
    void* (*paint)(void *);
}scr_data_t;


void gui_load_scr_animation(scr_id_t new_scr, scr_data_t * old_scr,
    lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

#endif /* __GUI_GUIDER_H__ */
