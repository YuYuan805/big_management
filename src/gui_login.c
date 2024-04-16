#include "../inc/gui_login.h"


GtkWidget *window_login = NULL;
GtkWidget *table_login = NULL; // 表格布局

GtkWidget *button_support = NULL;    // 养殖管理按钮
GtkWidget *button_store = NULL;      // 商城管理按钮
GtkWidget *button_back_login = NULL; // 登录返回按钮

extern GtkWidget *window_main;
extern GtkWidget *window_manage_main;
extern GtkWidget *window_shopping_centre;
extern GtkWidget *entry_id;
extern GtkWidget *entry_passwd;
extern GtkWidget *entry_Captcha;

/*************************************** gui_login * **************************************************/

// 返回主界面
void window_login_back_window_main(GtkWidget *button_back_login,
                                   gpointer data) {
    musicPause();

    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_passwd), "");
    gtk_entry_set_text(GTK_ENTRY(entry_Captcha), "");
    gtk_widget_show_all(window_main);
    gtk_widget_hide(window_login);
    return;
}

// 养殖管理
void window_main_to_window_support(GtkWidget *button_support, gpointer data) {
    musicPause();

    gtk_widget_show_all(window_manage_main);
    gtk_widget_hide(window_login);
    return;
}

// 商城
void window_main_to_window_store(GtkWidget *button_store, gpointer data) {
    musicPause();

    gtk_widget_show_all(window_shopping_centre);
    gtk_widget_hide(window_login);
    return;
}

/*************************************** gui_login * **************************************************/

void guiLogin(void) {
    // 初始化GUI
    window_login = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(GTK_WIDGET(window_login), 800, 500);
    gtk_window_set_title(GTK_WINDOW(window_login), "选择");
    gtk_window_set_position(GTK_WINDOW(window_login),
                            GTK_WIN_POS_CENTER); // 窗口居中

    // 表格布局
    table_login = gtk_table_new(10, 10, TRUE);
    gtk_container_add(GTK_CONTAINER(window_login), table_login);

    // 标签添加到表格中
    GtkWidget *label = gtk_label_new(""); // 标签
    gtk_label_set_markup(
        GTK_LABEL(label),
        "<span foreground='blue' font_desc='32'>宁氏猪场管理系统</span>");
    gtk_table_attach_defaults(GTK_TABLE(table_login), label, 1, 9, 0, 3);

    // 按钮添加到表格中
    button_support = gtk_button_new_with_label("养殖管理");
    gtk_table_attach_defaults(GTK_TABLE(table_login), button_support, 1, 4,
                              BUTTON_ROW_BRGIN_LOGIN, BUTTON_ROW_END_LOGIN);
    button_store = gtk_button_new_with_label("商城管理");
    gtk_table_attach_defaults(GTK_TABLE(table_login), button_store, 6, 9,
                              BUTTON_ROW_BRGIN_LOGIN, BUTTON_ROW_END_LOGIN);
    button_back_login = gtk_button_new_with_label("返回");
    gtk_table_attach_defaults(GTK_TABLE(table_login), button_back_login, 8, 9,
                              8, 9);

    // 按钮信号连接
    g_signal_connect(button_support, "pressed",
                     G_CALLBACK(window_main_to_window_support),
                     NULL); // 养殖管理按钮

    g_signal_connect(button_store, "pressed",
                     G_CALLBACK(window_main_to_window_store),
                     NULL); // 商城管理按钮

    g_signal_connect(button_back_login, "pressed",
                     G_CALLBACK(window_login_back_window_main),
                     NULL); // 返回按钮

    // 主窗口显示
    g_signal_connect(G_OBJECT(window_login), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
}
