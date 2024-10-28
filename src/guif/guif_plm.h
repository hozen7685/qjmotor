#ifndef __GUIF_PLM_H__
#define __GUIF_PLM_H__

#include "typedef.h"
#include "guif_if.h"
//plm: Page layer Manager
#define GUIF_LAYER_STACK_SIZE    (10)
typedef int32_t guif_layer_idx_t;

extern void guif_plm_init(void);
extern void guif_plm_clear(void);
extern ret_t guif_plm_push(guif_scr_id_t scr_id);
extern ret_t guif_plm_get_top(guif_scr_id_t *scr_id);
extern ret_t guif_plm_get_by(guif_layer_idx_t layer, guif_scr_id_t *scr_id);
extern ret_t guif_plm_get_layer_by(guif_scr_id_t scr_id, guif_layer_idx_t *layer);
extern guif_layer_idx_t guif_plm_get_layer_top(void);
extern ret_t guif_plm_del_layer(guif_layer_idx_t layer_idx);
extern int32_t guif_plm_foreach(guif_layer_idx_t start_layer, void (*cb)(guif_scr_id_t scr_id));
extern void guif_plm_foreach2(guif_layer_idx_t start_layer, void (*cb)(guif_scr_id_t scr_id));
extern bool_t guif_plm_exist(guif_scr_id_t scr_id);
extern guif_scr_id_t guif_plm_get_active(void);
extern void guif_plm_set_active(guif_scr_id_t scr_id);

#endif /* __GUIF_PLM_H__ */
