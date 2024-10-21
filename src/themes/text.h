#ifndef TEXT_H
#define TEXT_H
#ifdef __cplusplus
extern "C" {
#endif
typedef char char_t;

typedef enum {
    LANG_CH,
    LANG_EN,
    LANG_MAX
} lang_t;

typedef enum {
    T_TOPBAR_MODE,
    T_MENU_LV1,
    T_MENU_FOOT,
    T_IDMAX
} txt_id_t;

extern char_t const * get_text_by_lang_id(txt_id_t id, lang_t lang);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TEXT_H */
