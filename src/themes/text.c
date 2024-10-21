#include "text.h"

static const char_t * const s_txt_ch[T_IDMAX] = {
    "普通模式",
    "动力模式\n蓝牙\n胎压\n仪表主题\n亮度\n信息\n时钟\n单位\n语言\nTCS",
    "菜单"
};

static const char_t * const s_txt_en[T_IDMAX] = {
    "NORMAL",
    "DRIVE MODE\nBLUETOOTH\nTIRES\nAPPEARANCE\nBRIGHTNESS\nINFO\nCLOCK\nUNIT\nLANGUAGE\nTCS",
    "MENU"
};

static char_t const * const * const s_book[LANG_MAX] = {
    s_txt_ch,
    s_txt_en
};

char_t const * get_text_by_lang_id(txt_id_t id, lang_t lang)
{
    char_t const * text = s_book[lang][id];
    return text;
}