#pragma once


#include "../inc/mysqlite.h"
#include "../inc/callback.h"
#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <termios.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void loadImage(GtkWidget *image, const char *file_path, const int w,\
               const int h);

void guiTooltip(GtkWidget *window, const char *const msg);

void musicPause(void);

void musicQuit(void);
