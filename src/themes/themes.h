#ifndef THEMES_H
#define THEMES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lv_conf.h"
#include "lvgl.h"
#include "lv_version.h"
#include "color.h"
#include "text.h"

typedef enum {
    BRIGHT,
    DARK,
    WARN,
    UNDEF_THEME
} themes_t;

typedef enum {
    H12,
    H24
} hour_rule_t;

extern lang_t g_lang;
extern hour_rule_t g_hour_rule;

extern void set_theme_lang(lang_t lang);
extern void init_themes(void);
extern void set_theme(themes_t theme);
extern char_t const * get_text_byid(txt_id_t id);
extern void set_hour_rule(hour_rule_t value);
extern int get_color(color_t id);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* THEMES_H */