#include "../inc/gui_store.h"
#include <stdio.h>

#include "../inc/mysqlite.h"
GtkWidget *window_shopping_centre = NULL;
GtkWidget *shopping_centre = NULL;
GtkWidget *button_Place_order, *button_revise, *button_Shelves, *button_back;
GtkWidget *image_main;
GtkWidget *label, *clist;

char **p;
char **pp;
char selected_songout[256];
char selected_song[256];
GtkWidget *bj_image;

int price = 0;

extern sqlite3 *headquarters_db;
extern GtkWidget *window_login;

void load_image(GtkWidget *image, const char *file_path, const int w,
                const int h) {
    gtk_image_clear(GTK_IMAGE(image)); // 清除图像
    GdkPixbuf *src_pixbuf =
        gdk_pixbuf_new_from_file(file_path, NULL); // 创建图片资源
    GdkPixbuf *dest_pixbuf = gdk_pixbuf_scale_simple(
        src_pixbuf, w, h, GDK_INTERP_BILINEAR);    // 指定大小
    gtk_image_set_from_pixbuf(GTK_IMAGE(image),
                              dest_pixbuf);  // 图片控件重新设置一张图片(pixbuf)
    g_object_unref(src_pixbuf);              // 释放资源
    g_object_unref(dest_pixbuf);             // 释放资源
}

//-------------------------------回调函数区-----------------------------//
// clist回调函数
void on_row_selected(GtkWidget *clist, gint row, gint column, GdkEvent *event,
                     gpointer data) {}
// 下单
void button_Place_order_Callback(GtkWidget *clist, gpointer data) {}
// 删除
void button_revise_Callback(GtkWidget *clist, gpointer data) {}
// 上架
void button_Shelves_Callback(GtkWidget *clist, gpointer data) {}
// 返回
void button_back_Callback(GtkWidget *clist, gpointer data) {
    gtk_widget_show_all(window_login);
    gtk_widget_hide(window_shopping_centre);
    return;
}

//-------------------------------回调函数区-----------------------------//

void guiStore(void) {
    window_shopping_centre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(GTK_WIDGET(window_shopping_centre), 1600, 800);
    gtk_window_set_title(GTK_WINDOW(window_shopping_centre), "商城");
    gtk_window_set_position(GTK_WINDOW(window_shopping_centre),
                            GTK_WIN_POS_CENTER); // 窗口居中

    // 表格布局
    shopping_centre = gtk_table_new(10, 19, TRUE);
    gtk_container_add(GTK_CONTAINER(window_shopping_centre), shopping_centre);

    // 标签添加到表格中
    label = gtk_label_new(""); // 标签
    gtk_label_set_markup(
        GTK_LABEL(label),
        "<span foreground='red' font_desc='32'>长期合作伙伴——国璇大饭店</span>");
    gtk_table_attach_defaults(GTK_TABLE(shopping_centre), label, 0, 18, 0, 1);

    
    
    // 图片添加到表格中
    image_main = gtk_image_new_from_pixbuf(NULL);
    loadImage(image_main, "./image/zzx.png", 200, 200);
    gtk_table_attach_defaults(GTK_TABLE(shopping_centre), image_main, 14, 18, 2,
                              4);

    // 创建分栏列表
    char *clist_shopping_centre[7] = {"编号", "种类", "公母", "疫苗接种",
                                      "重量", "价格"}; // 定义一个数组存储标题
    clist = gtk_clist_new_with_titles(6, clist_shopping_centre); // 看

    // 设置分栏列表的宽度
    gtk_clist_set_column_width(GTK_CLIST(clist), 0, 150);
    gtk_clist_set_column_width(GTK_CLIST(clist), 1, 150);
    gtk_clist_set_column_width(GTK_CLIST(clist), 2, 150);
    gtk_clist_set_column_width(GTK_CLIST(clist), 3, 150);
    gtk_clist_set_column_width(GTK_CLIST(clist), 4, 150);
    gtk_clist_set_column_width(GTK_CLIST(clist), 5, 150);

    // 设置分栏列表内容
    gtk_clist_set_column_justification(GTK_CLIST(clist), 0, GTK_JUSTIFY_CENTER);
    gtk_clist_set_column_justification(GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
    gtk_clist_set_column_justification(GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);
    gtk_clist_set_column_justification(GTK_CLIST(clist), 3, GTK_JUSTIFY_CENTER);
    gtk_clist_set_column_justification(GTK_CLIST(clist), 4, GTK_JUSTIFY_CENTER);
    gtk_clist_set_column_justification(GTK_CLIST(clist), 5, GTK_JUSTIFY_CENTER);

    gtk_table_attach_defaults(GTK_TABLE(shopping_centre), clist, 1, 12, 2, 9);

    // 按钮添加到表格中

    button_Place_order = gtk_button_new_with_label("下单");
    gtk_table_attach_defaults(GTK_TABLE(shopping_centre), button_Place_order,
                              13, 15, 6, 7);
    button_revise = gtk_button_new_with_label("下架");
    gtk_table_attach_defaults(GTK_TABLE(shopping_centre), button_revise, 16, 18,
                              6, 7);
    button_Shelves = gtk_button_new_with_label("上新");
    gtk_table_attach_defaults(GTK_TABLE(shopping_centre), button_Shelves, 13,
                              15, 8, 9);
    button_back = gtk_button_new_with_label("返回");
    gtk_table_attach_defaults(GTK_TABLE(shopping_centre), button_back, 16, 18,
                              8, 9);

    // 按钮信号连接
    g_signal_connect(button_Place_order, "pressed",
                     G_CALLBACK(button_Place_order_Callback), NULL); // 下单按钮

    g_signal_connect(button_revise, "pressed",
                     G_CALLBACK(button_revise_Callback), NULL); // 下架按钮

    g_signal_connect(button_Shelves, "pressed",
                     G_CALLBACK(button_Shelves_Callback), NULL); // 上新按钮

    g_signal_connect(button_back, "pressed", G_CALLBACK(button_back_Callback),
                     NULL); // 返回按钮

    // 主窗口显示
    g_signal_connect(G_OBJECT(window_shopping_centre), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
}
