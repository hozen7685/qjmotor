// pcm: scr command management
#include "guif_config.h"
#include "guif_if.h"
#include "guif_pcm.h"
#include "guif_pcc.h"

typedef struct {
    int32_t tail;
    guif_pcm_req_t cmd_queue[GUIF_SCR_CMD_QUE_SIZE];
} guif_pcm_cmd_que_t;

static guif_pcm_cmd_que_t pcm_cmd_queue;

static bool_t guif_pcm_exist(const guif_pcm_req_t *req);

static ret_t (*guif_pcm_cmds[SCR_CMD_MAX])(const guif_pcm_req_t *req) = {
    guif_pcc_exec_change,   /* SCR_CMD_CHANGE */
    guif_pcc_exec_back,     /* SCR_CMD_BACK */
    guif_pcc_exec_delete,   /* SCR_CMD_DELETE */
};

void guif_pcm_init(void)
{
    pcm_cmd_queue.tail = 0;
}

ret_t guif_pcm_add(const guif_pcm_req_t *req)
{
    ret_t ret = RET_ERROR;
    bool_t result = FALSE;

    if (pcm_cmd_queue.tail < GUIF_SCR_CMD_QUE_SIZE) {
        result = guif_pcm_exist(req);
        if (!result) {
            pcm_cmd_queue.cmd_queue[pcm_cmd_queue.tail] = *req;
            pcm_cmd_queue.tail++;
            ret = RET_SUCCESS;
        }
    }

    return ret;
}

void guif_pcm_run(void)
{
    int32_t i;
    guif_pcm_req_t *req;

    for (i = 0; i < pcm_cmd_queue.tail; ++i) {
        req = &(pcm_cmd_queue.cmd_queue[i]);
        (*guif_pcm_cmds[req->cmd])(req);
    }

    pcm_cmd_queue.tail = 0;
}

static bool_t guif_pcm_exist(const guif_pcm_req_t *req)
{
    bool_t ret = FALSE;
    int32_t i;

    for (i = 0; i < pcm_cmd_queue.tail; ++i) {
        if ((req->cmd == pcm_cmd_queue.cmd_queue[i].cmd)
            && (req->scr_id == pcm_cmd_queue.cmd_queue[i].scr_id)) {
            ret = TRUE;
            break;
        }
    }

    return ret;
}

/* End Of File */
