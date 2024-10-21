#include "water_scale.h"
#include "bracket_rect.h"
#include "../themes/themes.h"

static lv_style_t section_tick_style;

static void set_temp(void * bar, int32_t temp)
{
    lv_bar_set_value(bar, temp, LV_ANIM_ON);
}

static lv_obj_t * create_scale(lv_obj_t *parent)
{
    lv_obj_t * bar_base = lv_obj_create(parent);
    lv_obj_set_size(bar_base, lv_pct(84), lv_pct(100));
    lv_obj_set_style_radius(bar_base, 5, 0);
    lv_obj_align(bar_base, LV_ALIGN_TOP_LEFT, lv_pct(16), 0);
    lv_obj_set_style_bg_color(bar_base, lv_color_hex(get_color(GRAY_C)), 0);
    lv_obj_set_scrollbar_mode(bar_base, LV_SCROLLBAR_MODE_OFF);
    lv_obj_t * bar = lv_bar_create(bar_base);
    lv_obj_set_size(bar, lv_pct(100), lv_pct(100));
    lv_obj_center(bar);
    lv_bar_set_range(bar, 0, 100);
    lv_obj_set_style_radius(bar, 5, LV_PART_MAIN);
    lv_obj_set_style_radius(bar, 5, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(bar, lv_color_hex(get_color(GRAY_C)), LV_PART_MAIN);
    lv_obj_set_style_bg_color(bar, lv_color_hex(get_color(BLACK_C)), LV_PART_INDICATOR);

    lv_obj_t * scale = lv_scale_create(bar_base);
    lv_obj_set_size(scale, lv_pct(100), lv_pct(100));
    lv_scale_set_label_show(scale, false);
    lv_scale_set_total_tick_count(scale, 7);
    lv_scale_set_major_tick_every(scale, 1);
    lv_obj_set_style_length(scale, 10, LV_PART_INDICATOR);
    lv_scale_set_range(scale, 0, 100);
    lv_obj_set_style_line_width(scale, 0, LV_PART_MAIN);
    lv_obj_set_style_line_opa(scale, 0, LV_PART_INDICATOR);
    lv_obj_align(scale, LV_ALIGN_CENTER, 0, 14);
    /* Add a section */
    lv_style_init(&section_tick_style);
    /* Label style properties */
    lv_style_set_line_color(&section_tick_style, lv_color_hex(get_color(BLACK_C)));
    lv_style_set_line_width(&section_tick_style, 2U); // Tick width
    lv_style_set_line_opa(&section_tick_style, 255);
    /* Configure section styles */
    lv_scale_section_t * section = lv_scale_add_section(scale);
    lv_scale_section_set_range(section, 10, 90);
    lv_scale_section_set_style(section, LV_PART_INDICATOR, &section_tick_style);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_temp);
    lv_anim_set_duration(&a, 3000);
    lv_anim_set_playback_duration(&a, 3000);
    lv_anim_set_var(&a, bar);
    lv_anim_set_values(&a, 0, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
    return bar_base;
}

lv_obj_t * water_scale(lv_obj_t *parent)
{
    lv_obj_t * scales_obj = lv_obj_create(parent);
    lv_obj_set_size(scales_obj, 500, 90);
    lv_obj_align(scales_obj, LV_ALIGN_TOP_LEFT, 0, lv_pct(50));
    lv_obj_t * gasoline_base = lv_obj_create(scales_obj);
    lv_obj_t * water_base = lv_obj_create(scales_obj);
    lv_obj_set_size(gasoline_base, 200, 38);
    lv_obj_set_size(water_base, 200, 38);
    lv_obj_align(gasoline_base, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_align(water_base, LV_ALIGN_TOP_LEFT, 0, 43);
    rect_set_t outside = {200, 38, 3};
    rect_set_t inside = {196, 34, 3};
    lv_obj_t * gasoline_work_obj = bracket_rect(gasoline_base, &outside, &inside);
    lv_obj_t * water_work_obj = bracket_rect(water_base, &outside, &inside);
    lv_obj_t * gasoline_icon = lv_label_create(gasoline_work_obj);
    lv_obj_t * water_icon = lv_label_create(water_work_obj);
    lv_obj_set_size(gasoline_icon, lv_pct(16), lv_pct(100));
    lv_obj_set_size(water_icon, lv_pct(16), lv_pct(100));
    lv_obj_align(gasoline_icon, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_align(water_icon, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_obj_t * gasoline_bar = create_scale(gasoline_work_obj);
    lv_obj_t * water_bar = create_scale(water_work_obj);
}
