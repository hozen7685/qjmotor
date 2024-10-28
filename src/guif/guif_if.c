#include "guif_if.h"
#include "guif_pcc.h"
#include "guif_plm.h"

void guif_init(void)
{
    guif_plm_init();
}

void guif_scr_change(guif_scr_id_t dst_scr_id)
{
    guif_pcc_exec_change(dst_scr_id);
}

void guif_scr_close(guif_scr_id_t dst_scr_id)
{
    guif_pcc_exec_delete(dst_scr_id);
}

void guif_scr_back(guif_scr_id_t dst_scr_id)
{
    guif_pcc_exec_back(dst_scr_id);
}
/* End Of File */
