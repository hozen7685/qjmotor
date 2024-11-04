#include "top_info_bar.h"
#include "../themes/themes.h"
#include <time.h>
#include <stdio.h>

static lv_obj_t *icon_bluetooth = NULL;
static lv_obj_t *icon_4G = NULL;
static lv_obj_t *icon_battery = NULL;
static lv_obj_t *icon_wifi = NULL;
static lv_obj_t *time_lable_hour = NULL;
static lv_obj_t *time_lable_min = NULL;
static lv_obj_t *time_lable_mid = NULL;
static lv_obj_t *time_lable_rear = NULL;
static char time_mid_blink = 1;
lv_obj_t * s_top_info_bar = NULL;

static void update_time_cb(lv_timer_t *timer);

static void top_info_bar(lv_obj_t *parent)
{
/* 位置、大小与布局 */
    lv_obj_t *bar = lv_obj_create(parent);
    lv_obj_set_size(bar, lv_pct(100), lv_pct(8));
    lv_obj_align(bar, LV_ALIGN_TOP_LEFT, 0, 0);
/* 内容 */
    //左侧图标盒子
    lv_obj_t * icon_box = lv_obj_create(bar);
    lv_obj_set_size(icon_box, 128, lv_pct(100));
    lv_obj_align(icon_box, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_flex_flow(icon_box, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(icon_box, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END);
    //插入图标
    icon_bluetooth = lv_label_create(icon_box);
    lv_obj_set_size(icon_bluetooth, 32, 32);
    lv_label_set_text(icon_bluetooth, LV_SYMBOL_BLUETOOTH);
    icon_battery = lv_label_create(icon_box);
    lv_obj_set_size(icon_battery, 32, 32);
    lv_label_set_text(icon_battery, LV_SYMBOL_BATTERY_EMPTY);
    icon_wifi = lv_label_create(icon_box);
    lv_obj_set_size(icon_wifi, 32, 32);
    lv_label_set_text(icon_wifi, LV_SYMBOL_WIFI);
    //时间弹性盒子
    lv_obj_t * time_box = lv_obj_create(bar);
    lv_obj_set_size(time_box, 128, lv_pct(100));
    lv_obj_align(time_box, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_flex_flow(time_box, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(time_box, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END);
    //模式标签
    lv_obj_t * mode_label = lv_label_create(bar);
    lv_obj_set_size(mode_label, 64, lv_pct(100));
    lv_obj_align_to(mode_label, icon_box, LV_ALIGN_TOP_LEFT, 128, 0);
    lv_label_set_text(mode_label, get_text_byid(T_TOPBAR_MODE));
    //时间label
    time_lable_hour = lv_label_create(time_box);
    lv_obj_set_size(time_lable_hour, 20, lv_pct(100));
    time_lable_mid = lv_label_create(time_box);
    lv_obj_set_size(time_lable_mid, 8, lv_pct(100));
    time_lable_min = lv_label_create(time_box);
    lv_obj_set_size(time_lable_min, 20, lv_pct(100));
    time_lable_rear = lv_label_create(time_box);
    lv_obj_set_size(time_lable_rear, 32, lv_pct(100));
    if(H12 == g_hour_rule) {
        lv_obj_remove_flag(time_lable_rear, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(time_lable_rear, LV_OBJ_FLAG_HIDDEN);
    }
    update_time_cb(NULL);
    //创建一个定时器，每秒更新一次
    lv_timer_create(update_time_cb, 1000, NULL);
    s_top_info_bar = bar;
}

void update_time_cb(lv_timer_t *timer) {
    time_t now;
    struct tm *tm;
    // 获取当前本地时间
    now = time(NULL);
    tm = localtime(&now);

    char time_str[4]; // 存放格式化后的时间字符串，HH:MM
    if(H12 == g_hour_rule) {
        if(tm->tm_hour > 12) {
            snprintf(time_str, sizeof(time_str) - 1, "%02d", tm->tm_hour - 12);
            lv_label_set_text(time_lable_rear, " PM");
        } else {
            snprintf(time_str, sizeof(time_str) - 1, "%02d", tm->tm_hour);
            lv_label_set_text(time_lable_rear, " AM");
        }
    } else {
        snprintf(time_str, sizeof(time_str) - 1, "%02d", tm->tm_hour);
    }
    // 更新时间标签的文本
    lv_label_set_text(time_lable_hour, time_str);
    snprintf(time_str, sizeof(time_str) - 1, "%02d", tm->tm_min);
    lv_label_set_text(time_lable_min, time_str);
    if(time_mid_blink) {
        lv_label_set_text(time_lable_mid, ":");
    } else {
        lv_label_set_text(time_lable_mid, "");
    }
    time_mid_blink = 1 - time_mid_blink;
}

void load_top_info_bar(lv_obj_t * p)
{
    if(s_top_info_bar) {
        lv_obj_set_parent(s_top_info_bar, p);
    } else{
        top_info_bar(p);
    }
}

void unload_top_info_bar(void)
{
    if(s_top_info_bar) {
        lv_obj_clean(s_top_info_bar);
        lv_obj_delete(s_top_info_bar);
        s_top_info_bar = NULL;
    }
}