
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <unistd.h>

#include "themes/themes.h"
#include "main_view/main_view.h"
#include "menu/menu_lv_1.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static const char * title = "QJMOTOR";

/**********************
 *      MACROS
 **********************/
#define WINDOWS 0
/**********************
 *   GLOBAL FUNCTIONS
 **********************/
int main(int argc, char const *argv[])
{
    /*Initialize LVGL*/
    lv_init();

#if WINDOWS
    /*Initialize the HAL for LVGL*/
    lv_display_t * display = lv_windows_create_display(title, 1024, 600, 100, FALSE, FALSE);
    lv_windows_acquire_pointer_indev(display);
#else
    lv_display_t * disp = lv_sdl_window_create(1024, 600);
    lv_sdl_window_set_title(disp, title);
    lv_display_set_default(disp);
    lv_indev_t * mouse = lv_sdl_mouse_create();
    lv_indev_set_display(mouse, disp);
#endif
    /*Output prompt information to the console, you can also use printf() to print directly*/
    LV_LOG_USER("LVGL initialization completed!");

    set_theme(BRIGHT);
    set_theme_lang(LANG_EN);
    set_hour_rule(H12);

    main_view();
    // menu_lv_1_page();

    while(1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5000);       /*Just to let the system breath*/
    }
    return 0;
}

