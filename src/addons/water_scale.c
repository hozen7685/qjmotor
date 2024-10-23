#include "water_scale.h"
#include "bracket_rect.h"
#include "../themes/themes.h"

static lv_obj_t * mode_base;
static lv_style_t section_tick_style_W;
static lv_style_t section_tick_style_B;

// srction range 10 20 40 60 80 90
static int mode = 0;

static void (*f_mode_creat[WAT_MODE_MAX])(lv_obj_t *) = {
    create_mode_1, create_mode_2,
    // create_mode_3, create_mode_4,
};

static void update_water_cb(lv_timer_t *timer) {
    lv_obj_clean(mode_base);
    f_mode_creat[mode++](mode_base);
    if(WAT_MODE_MAX == mode)
        mode = 0;
}

static lv_obj_t * add_scale_base(lv_obj_t *parent)
{
    lv_obj_t * scale = lv_scale_create(parent);
    lv_obj_set_size(scale, lv_pct(100), lv_pct(100));
    lv_scale_set_label_show(scale, false);
    lv_scale_set_total_tick_count(scale, 7);
    lv_scale_set_major_tick_every(scale, 1);
    lv_obj_set_style_length(scale, 10, LV_PART_INDICATOR);
    lv_scale_set_range(scale, 0, 100);
    lv_obj_set_style_line_width(scale, 0, LV_PART_MAIN);
    lv_obj_set_style_line_opa(scale, 0, LV_PART_INDICATOR);
    lv_obj_align(scale, LV_ALIGN_CENTER, 0, 14);
    return scale;
}

void water_scale(lv_obj_t *parent)
{
    /* Add a section */
    lv_style_init(&section_tick_style_B);
    lv_style_init(&section_tick_style_W);
    /* Label style properties */
    lv_style_set_line_color(&section_tick_style_W, lv_color_hex(get_color(WHITE_C)));
    lv_style_set_line_width(&section_tick_style_W, 2U);
    lv_style_set_line_opa(&section_tick_style_W, 255);
    lv_style_set_line_color(&section_tick_style_B, lv_color_hex(get_color(BLACK_C)));
    lv_style_set_line_width(&section_tick_style_B, 2U);
    lv_style_set_line_opa(&section_tick_style_B, 255);

    lv_obj_t * water_base = lv_obj_create(parent);
    lv_obj_set_size(water_base, 200, 38);
    lv_obj_align(water_base, LV_ALIGN_TOP_LEFT, 0, 283);
    rect_set_t outside = {200, 38, 3};
    rect_set_t inside = {196, 34, 3};
    lv_obj_t * water_work_obj = bracket_rect(water_base, &outside, &inside);
    lv_obj_t * water_icon = lv_label_create(water_work_obj);
    lv_obj_set_size(water_icon, lv_pct(16), lv_pct(100));
    lv_obj_align(water_icon, LV_ALIGN_TOP_LEFT, 0, 0);
    mode_base = lv_obj_create(water_work_obj);
    lv_obj_set_size(mode_base, lv_pct(84), lv_pct(100));
    lv_obj_set_style_radius(mode_base, 5, 0);
    lv_obj_align(mode_base, LV_ALIGN_TOP_LEFT, lv_pct(16), 0);
    lv_obj_set_style_bg_color(mode_base, lv_color_hex(get_color(GRAY_C)), 0);
    lv_obj_set_scrollbar_mode(mode_base, LV_SCROLLBAR_MODE_OFF);

    lv_timer_create(update_water_cb, 800, NULL);
}

static void create_mode_2(lv_obj_t *parent)
{
    lv_obj_t * rect_L = lv_obj_create(parent);
    lv_obj_set_size(rect_L, lv_pct(48), lv_pct(100));
    lv_obj_align(rect_L, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_bg_color(rect_L, lv_color_hex(get_color(BLACK_C)), 0);
    lv_obj_set_style_radius(rect_L, 5, 0);
    lv_obj_t * scale = add_scale_base(parent);
    lv_scale_section_t * section1 = lv_scale_add_section(scale);
    lv_scale_section_set_range(section1, 10, 60);
    lv_scale_section_set_style(section1, LV_PART_INDICATOR, &section_tick_style_W);
    lv_scale_section_t * section2 = lv_scale_add_section(scale);
    lv_scale_section_set_range(section2, 60, 90);
    lv_scale_section_set_style(section2, LV_PART_INDICATOR, &section_tick_style_B);
    lv_obj_t * label_l = lv_label_create(parent);
    lv_obj_set_size(label_l, lv_pct(16), lv_pct(100));
    lv_obj_align(label_l, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_color(label_l, lv_color_hex(get_color(WHITE_C)), 0);
    lv_obj_set_style_pad_top(label_l, 10, 0);
    lv_label_set_text(label_l, "C");
    lv_obj_t * label_R = lv_label_create(parent);
    lv_obj_set_size(label_R, lv_pct(16), lv_pct(100));
    lv_obj_align(label_R, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_text_color(label_R, lv_color_hex(get_color(RED_C)), 0);
    lv_obj_set_style_pad_top(label_R, 10, 0);
    lv_label_set_text(label_R, "H");
}

static void create_mode_1(lv_obj_t *parent)
{
    lv_obj_t * rect_R = lv_obj_create(parent);
    lv_obj_set_size(rect_R, lv_pct(48), lv_pct(100));
    lv_obj_align(rect_R, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_bg_color(rect_R, lv_color_hex(get_color(BLACK_C)), 0);
    lv_obj_set_style_radius(rect_R, 5, 0);
    lv_obj_t * scale = add_scale_base(parent);
    lv_scale_section_t * section1 = lv_scale_add_section(scale);
    lv_scale_section_set_range(section1, 10, 60);
    lv_scale_section_set_style(section1, LV_PART_INDICATOR, &section_tick_style_B);
    lv_scale_section_t * section2 = lv_scale_add_section(scale);
    lv_scale_section_set_range(section2, 60, 90);
    lv_scale_section_set_style(section2, LV_PART_INDICATOR, &section_tick_style_W);
    lv_obj_t * label_l = lv_label_create(parent);
    lv_obj_set_size(label_l, lv_pct(16), lv_pct(100));
    lv_obj_align(label_l, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_color(label_l, lv_color_hex(get_color(BLACK_C)), 0);
    lv_obj_set_style_pad_top(label_l, 10, 0);
    lv_label_set_text(label_l, "C");
    lv_obj_t * label_R = lv_label_create(parent);
    lv_obj_set_size(label_R, lv_pct(16), lv_pct(100));
    lv_obj_align(label_R, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_text_color(label_R, lv_color_hex(get_color(RED_C)), 0);
    lv_obj_set_style_pad_top(label_R, 10, 0);
    lv_label_set_text(label_R, "H");
}

static void create_mode_3(lv_obj_t *parent)
{
    /* Add a scale */
    lv_obj_t * scale = add_scale_base(parent);
    /* Configure section styles */
    lv_scale_section_t * section = lv_scale_add_section(scale);
    lv_scale_section_set_range(section, 10, 90);
    lv_scale_section_set_style(section, LV_PART_INDICATOR, &section_tick_style_B);
    lv_obj_t * label_l = lv_label_create(parent);
    lv_obj_set_size(label_l, lv_pct(16), lv_pct(100));
    lv_obj_align(label_l, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_color(label_l, lv_color_hex(get_color(RED_C)), 0);
    lv_obj_set_style_pad_top(label_l, 10, 0);
    lv_label_set_text(label_l, "C");
    lv_obj_t * label_R = lv_label_create(parent);
    lv_obj_set_size(label_R, lv_pct(16), lv_pct(100));
    lv_obj_align(label_R, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_text_color(label_R, lv_color_hex(get_color(BLACK_C)), 0);
    lv_obj_set_style_pad_top(label_R, 10, 0);
    lv_label_set_text(label_R, "H");
}

static void create_mode_4(lv_obj_t *parent)
{
    lv_obj_t * scale = add_scale_base(parent);
    lv_scale_section_t * section = lv_scale_add_section(scale);
    lv_scale_section_set_range(section, 20, 80);
    lv_scale_section_set_style(section, LV_PART_INDICATOR, &section_tick_style_B);
    lv_obj_t * rect_L = lv_obj_create(parent);
    lv_obj_set_size(rect_L, lv_pct(16), lv_pct(100));
    lv_obj_align(rect_L, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_bg_color(rect_L, lv_color_hex(get_color(ORANGE_C)), 0);
    lv_obj_set_style_radius(rect_L, 5, 0);
    lv_obj_t * rect_R = lv_obj_create(parent);
    lv_obj_set_size(rect_R, lv_pct(16), lv_pct(100));
    lv_obj_align(rect_R, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_bg_color(rect_R, lv_color_hex(get_color(BLACK_C)), 0);
    lv_obj_set_style_radius(rect_R, 5, 0);
    lv_obj_t * label_l = lv_label_create(parent);
    lv_obj_set_size(label_l, lv_pct(16), lv_pct(100));
    lv_obj_align(label_l, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_style_text_color(label_l, lv_color_hex(get_color(BLACK_C)), 0);
    lv_obj_set_style_pad_top(label_l, 10, 0);
    lv_label_set_text(label_l, "C");
    lv_obj_t * label_R = lv_label_create(parent);
    lv_obj_set_size(label_R, lv_pct(16), lv_pct(100));
    lv_obj_align(label_R, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_obj_set_style_text_color(label_R, lv_color_hex(get_color(WHITE_C)), 0);
    lv_obj_set_style_pad_top(label_R, 10, 0);
    lv_label_set_text(label_R, "H");
}

