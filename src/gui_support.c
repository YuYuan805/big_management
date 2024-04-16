#include "../inc/gui_support.h"
#include "../inc/mysqlite.h"

GtkWidget *window_manage_main = NULL;
GtkWidget *table_support = NULL;

extern GtkWidget *window_login;

void window_support_to_window_login(GtkWidget *widget, gpointer data) {
    musicPause();
    gtk_widget_show_all(window_login);
    gtk_widget_hide(window_manage_main);
    return;
}

// 管理界面init
void guiSupport(void) {
    int i = 0;

    // 初始化GUI
    window_manage_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(GTK_WIDGET(window_manage_main), 800, 500);
    gtk_window_set_title(GTK_WINDOW(window_manage_main), "宁氏猪场管理系统");
    gtk_window_set_position(GTK_WINDOW(window_manage_main),
                            GTK_WIN_POS_CENTER); // 窗口居中

    // 表格布局
    table_support = gtk_table_new(10, 10, TRUE);
    gtk_container_add(GTK_CONTAINER(window_manage_main), table_support);

    // 标签添加到表格中
    GtkWidget *label = gtk_label_new(""); // 标签
    gtk_label_set_markup(
        GTK_LABEL(label),
        "<span foreground='blue' font_desc='32'>猪场管理</span>");
    gtk_table_attach_defaults(GTK_TABLE(table_support), label, 3, 6, 0, 2);

    // 创建分栏列表
    char *clist_titles[4] = {"编号", "种类", "喂食", "状态"};
    GtkWidget *clist = gtk_clist_new_with_titles(4, clist_titles);

    // 设置分栏列表的宽度
    gtk_clist_set_column_width(GTK_CLIST(clist), 0, 200);
    gtk_clist_set_column_width(GTK_CLIST(clist), 1, 200);
    gtk_clist_set_column_width(GTK_CLIST(clist), 3, 200);
    gtk_clist_set_column_width(GTK_CLIST(clist), 4, 200);

    // 设置分栏列表内容
    gtk_clist_set_column_justification(GTK_CLIST(clist), 0, GTK_JUSTIFY_CENTER);
    gtk_clist_set_column_justification(GTK_CLIST(clist), 1, GTK_JUSTIFY_CENTER);
    gtk_clist_set_column_justification(GTK_CLIST(clist), 2, GTK_JUSTIFY_CENTER);
    gtk_clist_set_column_justification(GTK_CLIST(clist), 3, GTK_JUSTIFY_CENTER);

    int rows = 0, col = 0;

    char **p = Find_SQL_Subclasses("养殖记录", &rows, &col);

    char *clist_t[4] = {0};
    for (i = 0; i < rows; i++) {
        clist_t[0] = p[8];
        clist_t[1] = p[9];
        clist_t[2] = p[14];
        clist_t[3] = p[13];
        gtk_clist_append(GTK_CLIST(clist), clist_t);
    }
    gtk_table_attach_defaults(GTK_TABLE(table_support), clist, 0, 10, 2, 6);

    // 按钮添加到表格中
    GtkWidget *button_quit = gtk_button_new_with_label("返回");
    gtk_table_attach_defaults(GTK_TABLE(table_support), button_quit, 8, 9, 8, 9);

    GtkWidget *button_search = gtk_button_new_with_label("搜索");
    gtk_table_attach_defaults(GTK_TABLE(table_support), button_search, 4, 7, 8, 9);

    GtkWidget *button_manage = gtk_button_new_with_label("管理");
    gtk_table_attach_defaults(GTK_TABLE(table_support), button_manage, 1, 3, 8, 9);

    // 退出信号连接
    g_signal_connect(button_quit, "pressed",
                     G_CALLBACK(window_support_to_window_login),
                     NULL); // 退出按钮           G_CALLBACK里的回调函数没改

    //------------------------G_CALLBACK------------------------------------

    // 主窗口显示
    // gtk_widget_show_all(window_manage_main);
    g_signal_connect(G_OBJECT(window_manage_main), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
}
