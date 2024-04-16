#include "../inc/gui.h"

// 给创建好的image重新设计一张图片
void loadImage(GtkWidget *image, const char *file_path, const int w,
               const int h) {
    gtk_image_clear(GTK_IMAGE(image)); // 清除图像
    GdkPixbuf *src_pixbuf =
        gdk_pixbuf_new_from_file(file_path, NULL); // 创建图片资源
    GdkPixbuf *dest_pixbuf = gdk_pixbuf_scale_simple(
        src_pixbuf, w, h, GDK_INTERP_BILINEAR); // 指定大小
    gtk_image_set_from_pixbuf(GTK_IMAGE(image),
                              dest_pixbuf); // 图片控件重新设置一张图片(pixbuf)
    g_object_unref(src_pixbuf);             // 释放资源
    g_object_unref(dest_pixbuf);            // 释放资源
}

// 创建提示框
void guiTooltip(GtkWidget *window, const char *const msg) {
    GtkWidget *dialog_tuifang_queding =
        gtk_message_dialog_new((gpointer)window, GTK_DIALOG_DESTROY_WITH_PARENT,
                               GTK_MESSAGE_OTHER, GTK_BUTTONS_OK, msg);

    gtk_window_set_title(GTK_WINDOW(dialog_tuifang_queding), "提示");
    gtk_widget_set_size_request(dialog_tuifang_queding, 450, 100);
    gtk_dialog_run(GTK_DIALOG(dialog_tuifang_queding));
    gtk_widget_destroy(dialog_tuifang_queding);
}

void musicPause(void) {
    int fd = open("cmd_fifo", O_WRONLY);
    write(fd, "pause\n", strlen("pause\n"));
    close(fd);
}

void musicQuit(void) {
    int fd = open("cmd_fifo", O_WRONLY);
    write(fd, "quit\n", strlen("quit\n"));
    close(fd);
}
