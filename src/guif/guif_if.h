#ifndef __GUIF_IF_H__
#define __GUIF_IF_H__

#include "../frm/frm_msg.h"
#include "typedef.h"
#include "lvgl.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
typedef enum {
    SCR_HOME = 0,
    SCR_MENU,
    PGID_MAX
} guif_scr_id_t;

#define PGID_INVALID    PGID_MAX

typedef struct {
    void * (*paint)(void *);
    void (*load)(void *);
    void (*unload)(void *);
    void (*show)(void *);
    void (*hide)(void *);
} guif_scr_method_t;

typedef struct {
    guif_scr_id_t scr_id;
    void * lv_scr_obj;
    guif_scr_method_t *scr_methods;
} guif_scr_obj_t;

extern void guif_init(void);

extern void guif_scr_close(guif_scr_id_t dst_scr_id);
extern void guif_scr_change(guif_scr_id_t dst_scr_id);
extern void guif_scr_back(guif_scr_id_t dst_scr_id);

extern guif_scr_obj_t *guif_preg_get_obj(guif_scr_id_t scr_id);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GUIF_IF_H__ */
