// pmc: scr command concret
#include "../frm/frm_msg.h"
#include "guif_if.h"
#include "guif_pcc.h"
#include "guif_plm.h"

static void scr_load(guif_scr_obj_t * scr_obj);
static void scr_unload(guif_scr_obj_t * scr_obj);
static void scr_paint(guif_scr_obj_t * scr_obj);
static void scr_show(guif_scr_obj_t * scr_obj);
static void scr_hide(guif_scr_obj_t * scr_obj);

ret_t guif_pcc_exec_change(guif_scr_id_t scr_id)
{
    ret_t ret = RET_ERROR;
    guif_scr_obj_t * scr_obj;
    guif_scr_method_t *methods;
    guif_scr_id_t top_scr_id;
    guif_scr_obj_t *top_scr_obj;

    if (guif_plm_exist(scr_id)) {
        return RET_ERROR;
    }

    if (RET_SUCCESS == guif_plm_get_top(&top_scr_id)) {
        top_scr_obj = guif_preg_get_obj(top_scr_id);
        scr_hide(top_scr_obj);
    }

    // get scr object by scrid
    scr_obj = guif_preg_get_obj(scr_id);
    // lv_obj_create
    scr_paint(scr_obj);
    // lv_screen_load_anim
    scr_load(scr_obj);
    // push scr
    guif_plm_push(scr_id);
    ret = RET_SUCCESS;
    return ret;
}

ret_t guif_pcc_exec_back(guif_scr_id_t scr_id)
{
    ret_t ret = RET_ERROR;
    guif_scr_obj_t * scr_obj;
    guif_layer_idx_t layer_idx;
    guif_scr_id_t top_scr_id;
    guif_scr_obj_t *top_scr_obj;

    if (RET_SUCCESS == guif_plm_get_layer_by(scr_id, &layer_idx)) {
        scr_obj = guif_preg_get_obj(scr_id);
        scr_hide(scr_obj);
        guif_plm_del_layer(layer_idx);

        if (RET_SUCCESS == guif_plm_get_top(&top_scr_id)) {
            top_scr_obj = guif_preg_get_obj(top_scr_id);
            scr_show(top_scr_obj);
        }
        ret = RET_SUCCESS;
    }

    return ret;
}

ret_t guif_pcc_exec_delete(guif_scr_id_t scr_id)
{
    ret_t ret = RET_ERROR;
    guif_scr_obj_t * scr_obj;
    guif_layer_idx_t layer_idx;
    guif_scr_id_t top_scr_id;
    guif_scr_obj_t *top_scr_obj;

    if (RET_SUCCESS == guif_plm_get_layer_by(scr_id, &layer_idx)) {
        scr_obj = guif_preg_get_obj(scr_id);
        scr_hide(scr_obj);
        scr_unload(scr_obj);
        scr_obj->lv_scr_obj = NULL;
        guif_plm_del_layer(layer_idx);

        if (RET_SUCCESS == guif_plm_get_top(&top_scr_id)) {
            top_scr_obj = guif_preg_get_obj(top_scr_id);
            scr_show(top_scr_obj);
        }
        ret = RET_SUCCESS;
    }

    return ret;
}

static void scr_load(guif_scr_obj_t * scr_obj)
{
    if (scr_obj && scr_obj->scr_methods && scr_obj->scr_methods->load) {
        if (scr_obj->lv_scr_obj) {
            scr_obj->scr_methods->load(scr_obj->lv_scr_obj);
        }
    }
}

static void scr_unload(guif_scr_obj_t * scr_obj)
{
    if (scr_obj && scr_obj->scr_methods && scr_obj->scr_methods->unload) {
        if (scr_obj->lv_scr_obj) {
            scr_obj->scr_methods->unload(scr_obj->lv_scr_obj);
        }
    }
}

static void scr_paint(guif_scr_obj_t * scr_obj)
{
    if (scr_obj && scr_obj->scr_methods && scr_obj->scr_methods->paint) {
        if (!scr_obj->lv_scr_obj) {
        scr_obj->lv_scr_obj = scr_obj->scr_methods->paint(NULL);
        }
    }
}

static void scr_show(guif_scr_obj_t * scr_obj)
{
    if (scr_obj && scr_obj->scr_methods && scr_obj->scr_methods->show) {
        if (scr_obj->lv_scr_obj) {
            scr_obj->scr_methods->show(scr_obj->lv_scr_obj);
        }
    }
}

static void scr_hide(guif_scr_obj_t * scr_obj)
{
    if (scr_obj && scr_obj->scr_methods && scr_obj->scr_methods->hide) {
        if (scr_obj->lv_scr_obj) {
            scr_obj->scr_methods->hide(scr_obj->lv_scr_obj);
        }
    }
}

/* End Of File */
