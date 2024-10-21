#include "rpm_scale.h"
#include "../themes/themes.h"

static int rpm_value = 0;
static lv_style_t bar_style;
static lv_style_t arc_style;
static lv_obj_t * bar_hor;
static lv_obj_t * arc;
static lv_style_t bar_scale_style;
static lv_style_t arc_scale_style;
static const char * bar_labels[] = {"0", "1", "2", "3", "4", "5", "6", "7", NULL};
static const char * arc_labels[] = {"12", "11", "10", "9", "8", NULL};
static lv_style_t section_label_style;
static lv_style_t section_main_line_style;

int arr[14] = {0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000, 13000};
int i = 0;

static void update_rpm_cb(lv_timer_t *timer) {
    if(14 == i) i = 0;
    rpm_value = arr[i++];
    if(rpm_value < 0) {
        lv_bar_set_value(bar_hor, 0, LV_ANIM_ON);
        lv_arc_set_value(arc, 0);
    } else if(rpm_value <= BAR_MAX) {
        lv_bar_set_value(bar_hor, rpm_value, LV_ANIM_ON);
        lv_arc_set_value(arc, 0);
    } else if(rpm_value <= ARC_MAX) {
        lv_bar_set_value(bar_hor, BAR_MAX, LV_ANIM_ON);
        int angle = (rpm_value - BAR_MAX) * 100 / (ARC_MAX - BAR_MAX);
        lv_arc_set_value(arc, (rpm_value - BAR_MAX) * 100 / 5000);
    } else {
        lv_bar_set_value(bar_hor, BAR_MAX, LV_ANIM_ON);
        lv_arc_set_value(arc, 100);
    }
    if(rpm_value >= RPM_WARN) {
        lv_obj_set_style_bg_color(bar_hor, lv_color_hex(get_color(YELLOW_C)), LV_PART_INDICATOR);
        lv_style_set_arc_color(&arc_style, lv_color_hex(get_color(YELLOW_C)));
        // set_theme(WARN);
    } else {
        lv_obj_set_style_bg_color(bar_hor, lv_color_hex(get_color(BLACK_C)), LV_PART_INDICATOR);
        lv_style_set_arc_color(&arc_style, lv_color_hex(get_color(BLACK_C)));
        // set_theme(BRIGHT);
    }
}

lv_obj_t* rpm_scale(lv_obj_t *parent)
{
    lv_style_init(&arc_style);
    lv_style_set_arc_width(&arc_style, 76);
    lv_style_set_arc_rounded(&arc_style, 0);
    lv_style_set_arc_color(&arc_style, lv_color_hex(get_color(BLACK_C)));

    bar_hor = lv_bar_create(parent);
    lv_obj_set_size(bar_hor, 508, 76);
    lv_obj_align_to(bar_hor, parent, LV_ALIGN_TOP_LEFT, 0, 358);
    lv_bar_set_range(bar_hor, 0, BAR_MAX);
    lv_obj_set_style_radius(bar_hor, 0, LV_PART_MAIN);
    lv_obj_set_style_radius(bar_hor, 0, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(bar_hor, lv_color_hex(get_color(GRAY_C)), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(bar_hor, 255, LV_PART_MAIN);

    lv_obj_t * bar_remark = lv_label_create(parent);
    lv_obj_set_size(bar_remark, 100, 20);
    lv_obj_align_to(bar_remark, bar_hor, LV_ALIGN_TOP_LEFT, 0, -20);
    lv_label_set_text(bar_remark, "RPM x1000");

    lv_obj_t * bar_scale = lv_scale_create(parent);
    lv_obj_set_size(bar_scale, 508, 30);
    lv_scale_set_label_show(bar_scale, true);
    lv_scale_set_mode(bar_scale, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_obj_align_to(bar_scale, bar_hor, LV_ALIGN_TOP_LEFT, 0, 80);
    lv_scale_set_total_tick_count(bar_scale, 8);
    lv_scale_set_major_tick_every(bar_scale, 1);
    lv_obj_set_style_length(bar_scale, 5, LV_PART_INDICATOR);
    lv_scale_set_range(bar_scale, 0, 7);
    lv_scale_set_text_src(bar_scale, bar_labels);
    lv_style_init(&bar_scale_style);
    lv_style_set_text_font(&bar_scale_style, LV_FONT_DEFAULT);
    lv_style_set_text_color(&bar_scale_style, lv_color_hex(get_color(BLACK_C)));
    lv_style_set_line_color(&bar_scale_style, lv_color_hex(get_color(BLACK_C)));
    lv_style_set_width(&bar_scale_style, 10U);      /*Tick length*/
    lv_style_set_line_width(&bar_scale_style, 2U);  /*Tick width*/
    lv_obj_add_style(bar_scale, &bar_scale_style, LV_PART_INDICATOR);
    lv_obj_set_style_line_width(bar_scale, 0, LV_PART_MAIN);

    arc = lv_arc_create(parent);
    lv_obj_set_size(arc, 372, 372);
    lv_obj_align_to(arc, bar_hor, LV_ALIGN_BOTTOM_RIGHT, 186, 0);
    lv_arc_set_rotation(arc, 0);
    lv_arc_set_bg_angles(arc, 0, 90);
    lv_arc_set_angles(arc, 0, 90);
    lv_arc_set_mode(arc, LV_ARC_MODE_REVERSE);
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB);   /*Be sure the knob is not displayed*/
    lv_obj_remove_flag(arc, LV_OBJ_FLAG_CLICKABLE);  /*To not allow adjusting by click*/
    lv_obj_set_style_arc_rounded(arc, 0, LV_PART_MAIN);
    lv_obj_set_style_arc_width(arc, 76, LV_PART_MAIN);
    lv_obj_set_style_arc_color(arc, lv_color_hex(get_color(GRAY_C)), LV_PART_MAIN);
    lv_obj_add_style(arc, &arc_style, LV_PART_INDICATOR);

    lv_obj_t * arc_scale = lv_scale_create(parent);
    lv_obj_set_size(arc_scale, 390, 390);
    lv_scale_set_label_show(arc_scale, true);
    lv_scale_set_mode(arc_scale, LV_SCALE_MODE_ROUND_OUTER);
    lv_obj_set_style_radius(arc_scale, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(arc_scale, true, 0);
    lv_obj_align_to(arc_scale, arc, LV_ALIGN_CENTER, 0, 0);
    lv_scale_set_range(arc_scale, 7, 11);
    lv_scale_set_angle_range(arc_scale, 72);
    lv_scale_set_rotation(arc_scale, 0);
    lv_scale_set_text_src(arc_scale, arc_labels);
    lv_scale_set_total_tick_count(arc_scale, 5);
    lv_scale_set_major_tick_every(arc_scale, 1);
    lv_obj_set_style_length(arc_scale, 5, LV_PART_INDICATOR);
    lv_style_init(&arc_scale_style);
    /* Label style properties */
    lv_style_set_text_font(&arc_scale_style, LV_FONT_DEFAULT);
    lv_style_set_text_color(&arc_scale_style, lv_color_hex(get_color(BLACK_C)));
    /* Major tick properties */
    lv_style_set_line_color(&arc_scale_style, lv_color_hex(get_color(BLACK_C)));
    lv_style_set_width(&arc_scale_style, 10U);      /*Tick length*/
    lv_style_set_line_width(&arc_scale_style, 2U);  /*Tick width*/
    lv_obj_add_style(arc_scale, &arc_scale_style, LV_PART_INDICATOR);
    lv_obj_set_style_arc_width(arc_scale, 0, LV_PART_MAIN);
    /* Add a section */
    lv_style_init(&section_label_style);
    lv_style_init(&section_main_line_style);

    /* Label style properties */
    lv_style_set_text_font(&section_label_style, LV_FONT_DEFAULT);
    lv_style_set_text_color(&section_label_style, lv_color_hex(get_color(RED_C)));
    lv_style_set_line_color(&section_label_style, lv_color_hex(get_color(RED_C)));
    lv_style_set_line_width(&section_label_style, 2U); /*Tick width*/
    /* Main line properties */
    lv_style_set_arc_width(&section_main_line_style, 0);
    /* Configure section styles */
    lv_scale_section_t * section = lv_scale_add_section(arc_scale);
    lv_scale_section_set_range(section, 7, 10);
    lv_scale_section_set_style(section, LV_PART_INDICATOR, &section_label_style);
    lv_scale_section_set_style(section, LV_PART_MAIN, &section_main_line_style);

    lv_timer_create(update_rpm_cb, 1000, NULL);
    return NULL;
}