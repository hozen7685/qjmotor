#include "main_view.h"
#include "../addons/top_info_bar.h"
#include "../addons/speed_info.h"
#include "../addons/rpm_scale.h"
#include "../addons/gasoline_scale.h"
#include "../addons/water_scale.h"
#include "../addons/mileage_roller.h"

static void event_handler(lv_event_t * e)
{
    lv_event_code_t evt_code = lv_event_get_code(e);
    lv_key_t key_code = lv_indev_get_key(lv_indev_active());
    LV_LOG_USER("EVEVT CODE [%d];KEY CODE [%d]\n", evt_code, key_code);
}

void main_view(void)
{
    lv_obj_t * obj = lv_obj_create(lv_screen_active());
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_pad_left(obj, 16, 0);
    lv_obj_center(obj);
/* 顶部信息栏 */
    top_info_bar(obj);
/* 速度 */
    speed_info_zone(obj);
/* 转速条 */
    rpm_scale(obj);
/* 油表*/
    gasoline_scale(obj);
/* 水温 */
    water_scale(obj);
/* 公里数 */
    lv_obj_t * catch_obj = mileage_roller(obj);
/* 按键捕获 */
    lv_obj_add_event_cb(catch_obj, event_handler, LV_EVENT_ALL, NULL);
}
