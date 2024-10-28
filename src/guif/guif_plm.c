//plm: Page layer Manager
#include "guif_if.h"
#include "guif_plm.h"

typedef struct {
    guif_layer_idx_t tp;                                /* top pointer */
    guif_scr_id_t stack[GUIF_LAYER_STACK_SIZE];
} guif_layer_stack_t;

static guif_layer_stack_t scr_stack;

void guif_plm_init(void)
{
    scr_stack.tp = 0;
}

void guif_plm_clear(void)
{
    scr_stack.tp = 0;
}

ret_t guif_plm_push(guif_scr_id_t scr_id)
{
    ret_t ret = RET_ERROR;

    if (scr_stack.tp < GUIF_LAYER_STACK_SIZE) {
        scr_stack.stack[scr_stack.tp] = scr_id;
        scr_stack.tp++;
        ret = RET_SUCCESS;
    }

    return ret;
}

ret_t guif_plm_get_top(guif_scr_id_t *scr_id)
{
    ret_t ret = RET_ERROR;

    if (scr_stack.tp > 0) {
        *scr_id = scr_stack.stack[scr_stack.tp - 1];
        ret = RET_SUCCESS;
    }

    return ret;
}

ret_t guif_plm_get_by(guif_layer_idx_t layer, guif_scr_id_t *scr_id)
{
    ret_t ret = RET_ERROR;

    if (layer < scr_stack.tp) {
        *scr_id = scr_stack.stack[layer];
        ret = RET_SUCCESS;
    }

    return ret;
}

// 根据scrid获取所在layer
ret_t guif_plm_get_layer_by(guif_scr_id_t scr_id, guif_layer_idx_t *layer)
{
    ret_t ret = RET_ERROR;
    guif_layer_idx_t i;

    for (i = scr_stack.tp; i > 0; --i) {
        if (scr_stack.stack[i - 1] == scr_id) {
            *layer = i - 1;
            ret = RET_SUCCESS;
            break;
        }
    }

    return ret;
}

guif_layer_idx_t guif_plm_get_layer_top(void)
{
    return scr_stack.tp;
}

// 删除指定layer的scr
ret_t guif_plm_del_layer(guif_layer_idx_t layer_idx)
{
    ret_t ret = RET_ERROR;
    guif_layer_idx_t i;

    if ((scr_stack.tp > 0) && (layer_idx < scr_stack.tp)) {
        for (i = layer_idx; i < scr_stack.tp; ++i) {
            scr_stack.stack[i] = scr_stack.stack[i + 1];
        }
        scr_stack.tp--;
        ret = RET_SUCCESS;
    }

    return ret;
}

int32_t guif_plm_foreach(guif_layer_idx_t start_layer, void (*cb)(guif_scr_id_t scr_id))
{
    int32_t cnt = 0;
    guif_layer_idx_t i;

    if (NULL != cb) {
        for (i = start_layer; i < scr_stack.tp; ++i) {
            (*cb)(scr_stack.stack[i]);
            ++cnt;
        }
    }

    return cnt;
}

void guif_plm_foreach2(guif_layer_idx_t start_layer, void (*cb)(guif_scr_id_t scr_id))
{
    if ((NULL != cb) && (scr_stack.tp > 0)) {
        (*cb)(scr_stack.stack[scr_stack.tp - 1]);
    }
}

// scr在栈中返回TRUE，否则返回FALSE
bool_t guif_plm_exist(guif_scr_id_t scr_id)
{
    bool_t ret = FALSE;
    guif_layer_idx_t i;

    for (i = 0; i < scr_stack.tp; ++i) {
        if (scr_stack.stack[i] == scr_id) {
            ret = TRUE;
            break;
        }
    }

    return ret;
}

static guif_scr_id_t active_scr_id = PGID_INVALID;

guif_scr_id_t guif_plm_get_active(void)
{
    return active_scr_id;
}

void guif_plm_set_active(guif_scr_id_t scr_id)
{
    active_scr_id = scr_id;
}

/* End Of File */
