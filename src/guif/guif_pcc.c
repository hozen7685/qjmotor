// pmc: scr command concret
#include "../frm/frm_msg.h"
#include "guif_config.h"
#include "guif_if.h"
#include "guif_pcm.h"
#include "guif_pcc.h"
#include "guif_plm.h"
#include "guif_preg.h"

static void scr_load(guif_scr_obj_t * scr_obj);
static void scr_unload(guif_scr_obj_t * scr_obj);
static void scr_paint(guif_scr_obj_t * scr_obj);
static void scr_show(guif_scr_obj_t * scr_obj);

ret_t guif_pcc_exec_change(const guif_pcm_req_t *req)
{
    ret_t ret = RET_ERROR;
    guif_scr_id_t scr_id = req->scr_id;
    guif_scr_obj_t * scr_obj;
    guif_scr_method_t *methods;

    if (guif_plm_exist(scr_id)) {
        return RET_ERROR;
    }

    // get scr object by scrid
    scr_obj = guif_preg_get_obj(scr_id);
    if (NULL != scr_obj) {
        methods = scr_obj->scr_methods;
        if (NULL != methods) {
            // lv_obj_create
            scr_paint(scr_obj);
            // lv_screen_load_anim
            scr_load(scr_obj);
            // push scr
            guif_plm_push(scr_id);
            ret = RET_SUCCESS;
        }
        else {
            // log_error("scr(%d) no method", scr_id);
        }
    }
    else {
        // log_error("scr(%d) no exist", scr_id);
    }

    return ret;
}

ret_t guif_pcc_exec_back(const guif_pcm_req_t *req)
{
    ret_t ret = RET_ERROR;
    guif_scr_id_t scr_id = req->scr_id;
    guif_scr_obj_t * scr_obj;
    guif_layer_idx_t layer_idx;
    guif_scr_id_t top_scr_id;
    guif_scr_obj_t *top_scr_obj;

    if (RET_SUCCESS == guif_plm_get_layer_by(scr_id, &layer_idx)) {
        scr_obj = guif_preg_get_obj(scr_id);

        guif_plm_del_layer(layer_idx);

        if (RET_SUCCESS == guif_plm_get_top(&top_scr_id)) {
            top_scr_obj = guif_preg_get_obj(top_scr_id);
            scr_show(top_scr_obj);
        }
        // scr_unload(scr_obj);
        // scr_obj->lv_scr_obj = NULL;
        ret = RET_SUCCESS;
    }

    return ret;
}

ret_t guif_pcc_exec_delete(const guif_pcm_req_t *req)
{
    ret_t ret = RET_ERROR;
    guif_scr_id_t scr_id = req->scr_id;
    guif_scr_obj_t * scr_obj;
    guif_layer_idx_t layer_idx;
    guif_scr_id_t top_scr_id;
    guif_scr_obj_t *top_scr_obj;

    if (RET_SUCCESS == guif_plm_get_layer_by(scr_id, &layer_idx)) {
        scr_obj = guif_preg_get_obj(scr_id);

        guif_plm_del_layer(layer_idx);

        if (RET_SUCCESS == guif_plm_get_top(&top_scr_id)) {
            top_scr_obj = guif_preg_get_obj(top_scr_id);
            scr_show(top_scr_obj);
        }
        scr_unload(scr_obj);
        scr_obj->lv_scr_obj = NULL;
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
        scr_obj->lv_scr_obj = scr_obj->scr_methods->paint(scr_obj->lv_scr_obj);
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

/* End Of File */