#include "themes.h"
#include "src/themes/lv_theme_private.h"
#include "src/font/lv_font.h"

int *th_color_list = &s_palette;
lang_t g_lang = LANG_CH;
hour_rule_t g_hour_rule = H12;

static lv_style_t cmn_style;
static lv_theme_t cmn_theme;

static void theme_apply_cb(lv_theme_t * th, lv_obj_t * obj)
{
    LV_UNUSED(th);
    lv_obj_add_style(obj, &cmn_style, 0);
}

void init_themes(void)
{
    lv_style_init(&cmn_style);
    lv_style_set_border_width(&cmn_style, 0);
    lv_style_set_outline_width(&cmn_style, 0);
    lv_style_set_pad_all(&cmn_style, 0);
    lv_style_set_radius(&cmn_style, 0);
    lv_style_set_text_align(&cmn_style, LV_TEXT_ALIGN_CENTER);
    lv_style_set_bg_color(&cmn_style, lv_color_hex(get_color(WHITE_C)));
    lv_style_set_border_color(&cmn_style, lv_color_hex(get_color(WHITE_C)));
    lv_style_set_text_color(&cmn_style, lv_color_hex(get_color(BLACK_C)));
    /*Initialize the new theme from the current theme*/
    lv_theme_t * th_act = lv_display_get_theme(NULL);
    cmn_theme = *th_act;
    /*Set the parent theme and the style apply callback for the new theme*/
    lv_theme_set_parent(&cmn_theme, th_act);
    lv_theme_set_apply_cb(&cmn_theme, theme_apply_cb);
    lv_display_set_theme(NULL, &cmn_theme);
}

void set_theme(themes_t theme)
{
    switch (theme)
    {
    case BRIGHT:
        th_color_list = &s_palette;
        break;
    case DARK:
        th_color_list = &s_palette_r;
        break;
    case WARN:
        th_color_list = &s_palette_w;
        break;
    default:
        break;
    }
    init_themes();
}

void set_theme_lang(lang_t lang)
{
    g_lang = lang;
}

char_t const * get_text_byid(txt_id_t id)
{
    return get_text_by_lang_id(id, g_lang);
}

void set_hour_rule(hour_rule_t value)
{
    g_hour_rule = value;
}

int get_color(color_t id)
{
    return th_color_list[id];
}
