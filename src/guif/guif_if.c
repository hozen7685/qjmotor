#include "guif_config.h"
#include "guif_if.h"
#include "guif_pcm.h"
#include "guif_plm.h"

void guif_init(void)
{
    guif_plm_init();
    guif_pcm_init();
}
#if USE_MSG
void guif_msgproc(const frm_msg_t * msg)
{
    guif_ep_t result;

    result = guif_evt_pre_process(msg);
    guif_pcm_run();

    if (GEP_GO_ON == result) {
        result = guif_evt_scr_process(msg);
        guif_pcm_run();
    }

    if ((GEP_GO_ON == result) || (GEP_JUMPTO_POST == result)) {
        guif_evt_post_process(msg);
        guif_pcm_run();
    }
}
#endif
ret_t guif_scr_change(guif_scr_id_t dst_scr_id)
{
    guif_pcm_req_t req;
    memset(&req, 0x00, sizeof(req));
    req.cmd = SCR_CMD_CHANGE;
    req.scr_id = dst_scr_id;
    guif_pcm_add(&req);
    guif_pcm_run();
    return RET_SUCCESS;
}

ret_t guif_scr_close(guif_scr_id_t dst_scr_id)
{
    guif_pcm_req_t req;
    memset(&req, 0x00, sizeof(req));
    req.cmd = SCR_CMD_DELETE;
    req.scr_id = dst_scr_id;
    guif_pcm_add(&req);
    guif_pcm_run();
    return RET_SUCCESS;
}

ret_t guif_scr_back(guif_scr_id_t dst_scr_id)
{
    guif_pcm_req_t req;
    memset(&req, 0x00, sizeof(req));
    req.cmd = SCR_CMD_BACK;
    req.scr_id = dst_scr_id;
    guif_pcm_add(&req);
    guif_pcm_run();
    return RET_SUCCESS;
}
#if 0
void guif_msg_key(guif_navi_key_t key, guif_key_state_t state)
{
    frm_msg_t msg;
    msg.msgid = MSG_ID_GUI_KEY;
    msg.param1 = (void *)key;
    msg.param2 = (void *)state;
    frm_msg_send(&msg);
}
#endif
/* End Of File */
