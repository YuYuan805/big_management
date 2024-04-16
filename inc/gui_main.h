#pragma once

#ifndef GUI_MAIN_H
#define GUI_MAIN_H

#include "../inc/gui.h"

#define MAX_STATEMENT_SIZE 1024

enum button_main {
    ID_ROW_BRGIN = 4,
    ID_ROW_END,
    PASSWD_ROW_BRGIN,
    PASSWD_ROW_END,

    BUTTON_ROW_BRGIN,
    BUTTON_ROW_END
};


//修改背景图
void chang_background(GtkWidget *widget, int w, int h, const gchar *path);
void guiMain(void);

#endif
