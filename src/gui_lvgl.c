#include "lvgl.h"
#include "gui_lvgl.h"
#include "guif/guif_if.h"
#include "themes/themes.h"
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

static const char * title = "QJMOTOR";
static pthread_t lvgl_tid;
static void * lvgl_task_handler_thread(void *param);

static void * lvgl_task_handler_thread(void *param)
{
    lv_init();
    guif_init();
#if WINDOWS
    /*Initialize the HAL for LVGL*/
    lv_display_t * display = lv_windows_create_display(title, 1024, 600, 100, FALSE, FALSE);
    lv_windows_acquire_pointer_indev(display);
#else
  lv_group_set_default(lv_group_create());

  lv_display_t * disp = lv_sdl_window_create(800, 480);
  lv_display_set_default(disp);

  lv_indev_t * mouse = lv_sdl_mouse_create();
  lv_indev_set_display(mouse, disp);
  lv_indev_set_group(mouse, lv_group_get_default());

  lv_indev_t * kb = lv_sdl_keyboard_create();
  lv_indev_set_display(kb, disp);
  lv_indev_set_group(kb, lv_group_get_default());

#endif
    /*Output prompt information to the console, you can also use printf() to print directly*/
    LV_LOG_USER("LVGL initialization completed!");

    set_theme(BRIGHT);
    set_theme_lang(LANG_EN);
    set_hour_rule(H12);
    guif_scr_change(SCR_HOME);
    while(1) {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5000);       /*Just to let the system breath*/
    }
    return NULL;
}

void gui_lvgl_start(void)
{
    // if(0 != pthread_create(&lvgl_tid, NULL, lvgl_task_handler_thread, NULL)) {
    //     printf("create lvgl thread failed.\n");
    // } else{
    //     pthread_detach(lvgl_tid);
    // }
    lvgl_task_handler_thread(NULL);
}

/* End Of File */
