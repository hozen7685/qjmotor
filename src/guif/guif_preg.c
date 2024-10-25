#include "guif_if.h"
extern guif_scr_obj_t scr_home_obj;
extern guif_scr_obj_t scr_menu_obj;

static guif_scr_obj_t *scr_objs[PGID_MAX] = {
    &scr_home_obj,
    &scr_menu_obj,
};

guif_scr_obj_t *guif_preg_get_obj(guif_scr_id_t scr_id)
{
    guif_scr_obj_t *ret = NULL;

    if (scr_id < PGID_MAX) {
        ret = scr_objs[scr_id];
    }

    return ret;
}

/* End Of File */
