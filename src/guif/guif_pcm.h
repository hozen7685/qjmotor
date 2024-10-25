#ifndef __GUIF_PCM_H__
#define __GUIF_PCM_H__
// pcm: scr command management

typedef enum{
    SCR_CMD_CHANGE,
    SCR_CMD_BACK,
    SCR_CMD_DELETE,
    SCR_CMD_MAX
} guif_pcm_cmd_t;

typedef struct {
    guif_pcm_cmd_t cmd;
    guif_scr_id_t scr_id;
} guif_pcm_req_t;

extern void guif_pcm_init(void);
extern ret_t guif_pcm_add(const guif_pcm_req_t *req);
extern void guif_pcm_run(void);

#endif /* __GUIF_PCM_H__ */
