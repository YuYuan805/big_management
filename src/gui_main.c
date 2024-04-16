#include "../inc/gui_main.h"


GtkWidget *window_main = NULL;  // 主窗口
GtkWidget *table_main = NULL;   // 表格布局
GtkWidget *entry_id = NULL;     // 登录账号
GtkWidget *entry_passwd = NULL; // 密码
GtkWidget *image_main = NULL;   // 图片

GtkWidget *button_signin = NULL; // 注册按钮
GtkWidget *button_login = NULL;  // 登录按钮
GtkWidget *button_f5 = NULL;     // 刷新按钮

GtkWidget *entry_Captcha = NULL; // 验证码

char pchar[5]; // 定义具有足够大小的字符数组
void stsrt(char *p);
extern GtkWidget *window_login;
extern sqlite3 *headquarters_db;
//修改背景图
void chang_background(GtkWidget *widget, int w, int h, const gchar *path)
{
    gtk_widget_set_app_paintable(widget, TRUE);     //允许窗口可以绘图
    gtk_widget_realize(widget); 
 
    /* 更改背景图时，图片会重叠
     * 这时要手动调用下面的函数，让窗口绘图区域失效，产生窗口重绘制事件（即 expose 事件）。
     */
    gtk_widget_queue_draw(widget);
 
    GdkPixbuf *src_pixbuf = gdk_pixbuf_new_from_file(path, NULL);   // 创建图片资源对象
    // w, h是指定图片的宽度和高度
    GdkPixbuf *dst_pixbuf = gdk_pixbuf_scale_simple(src_pixbuf, w, h, GDK_INTERP_BILINEAR);
 
    GdkPixmap *pixmap = NULL;
 
    /* 创建pixmap图像; 
     * NULL：不需要蒙版; 
     * 123： 0~255，透明到不透明
     */
    gdk_pixbuf_render_pixmap_and_mask(dst_pixbuf, &pixmap, NULL, 128);
    // 通过pixmap给widget设置一张背景图，最后一个参数必须为: FASLE
    gdk_window_set_back_pixmap(widget->window, pixmap, FALSE);
 
    // 释放资源
    g_object_unref(src_pixbuf);
    g_object_unref(dst_pixbuf);
    g_object_unref(pixmap);
}
/*************************************** gui_main **************************************************/
// 清空账号和密码
void window_main_do_clean(GtkWidget *button_f5, gpointer data) {
    stsrt(pchar);
    
    char yzm[256] = "";
    sprintf(yzm, "<span foreground='black' font_desc='22'>验证码: %s</span>",
            pchar);

    GtkWidget *label = gtk_label_new(""); // 验证码
    gtk_label_set_markup(GTK_LABEL(label), yzm);
    gtk_table_attach_defaults(GTK_TABLE(table_main), label, 6, 9, 7, 8);
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_passwd), "");
}

// 注册
void window_main_do_signin(GtkWidget *button_signin, gpointer data) {
    sqlite3_close(headquarters_db);
    sqlite3_open("./data/管理人员.db", &headquarters_db);
    // 获取id和passwd
    const char *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *passwd = gtk_entry_get_text(GTK_ENTRY(entry_passwd));

    if (strcmp(id, "") == 0 || strcmp(passwd, "") == 0) {
        guiTooltip(window_main, "账号和密码不能为空");
        return;
    }
    char sql_statement[MAX_STATEMENT_SIZE]; // 存储sql语句的数组
    // 组合一个查询的sql语句
    sprintf(sql_statement,
            "select * from 管理员 where 账号 = \'%s\' and 密码 = \'%s\';", id,
            passwd);


    // 执行sql语句
    int row = 0, col = 0;
    char **ret = NULL;
    char *errmsg = NULL;
    sqlite3_get_table(headquarters_db, sql_statement, &ret, &row, &col,
                      &errmsg);

    if (errmsg != NULL) {
        printf("errmsg: %s\n", errmsg);
    }

    // 判断是否已经注册
    if (row != 0) {
        guiTooltip(window_main, "账号已注册，请勿重复注册");
        sqlite3_close(headquarters_db);
        return;
    }
    // 组合一个插入的sql语句
    sprintf(sql_statement, "insert into 管理员 values(\'%s\', \'%s\');", id,
            passwd);
    // SQL_manage_Subclasses_write(sql_statement, "./data/管理人员.db")

    SQL_manage_Subclasses_write(headquarters_db, "管理员", id, passwd);
    guiTooltip(window_main, "账号注册成功！");
}

// 登录
void window_main_to_window_login(GtkWidget *button_login, gpointer data) {
    musicPause(); 

    // 获取id和passwd
    sqlite3_close(headquarters_db);
    sqlite3_open("./data/管理人员.db", &headquarters_db);

    const char *id = gtk_entry_get_text(GTK_ENTRY(entry_id));
    const char *passwd = gtk_entry_get_text(GTK_ENTRY(entry_passwd));

    const char *Captcha = gtk_entry_get_text(GTK_ENTRY(entry_Captcha)); // 验证码

    char sql_statement[MAX_STATEMENT_SIZE]; // 存储sql语句的数组
    // 组合一个查询的sql语句
    sprintf(sql_statement,
            "select * from 管理员 where 账号 = \'%s\' and 密码 = \'%s\';", id,
            passwd);

    // 执行sql语句
    int row = 0, col = 0;
    char **ret = NULL;
    char *errmsg = NULL;

    sqlite3_get_table(headquarters_db, sql_statement, &ret, &row, &col,
                      &errmsg);

    if (errmsg != NULL) {
        printf("errmsg: %s\n", errmsg);
    }
    

    if (strcmp(Captcha, pchar) == 0) {
        if (row != 0) {

            gtk_widget_show_all(window_login);
            gtk_widget_hide(window_main);
            sqlite3_close(headquarters_db);
            return;
        }
        else {
            guiTooltip(window_main, "账号或密码错误，请重新输入");
        }
    }
    else {
        guiTooltip(window_main, "验证码错误，请重新输入");
    }
}
/*************************************** gui_main ***************************************************/
void stsrt(char *p);
// 界面init
void guiMain(void) {
    gtk_entry_set_text(GTK_ENTRY(entry_id), "");
    gtk_entry_set_text(GTK_ENTRY(entry_passwd), "");
    // 初始化GUI
    window_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request(GTK_WIDGET(window_main), 800, 500);
    gtk_window_set_title(GTK_WINDOW(window_main), "宁氏猪场管理系统");
    gtk_window_set_position(GTK_WINDOW(window_main),
                            GTK_WIN_POS_CENTER); // 窗口居中

    // 表格布局
    table_main = gtk_table_new(10, 10, TRUE);
    gtk_container_add(GTK_CONTAINER(window_main), table_main);

    // 标签添加到表格中
    GtkWidget *label = gtk_label_new(""); // 标签
    gtk_label_set_markup(
        GTK_LABEL(label),
        "<span foreground='blue' font_desc='32'>宁氏猪场管理系统</span>");
    gtk_table_attach_defaults(GTK_TABLE(table_main), label, 1, 9, 0, 1);

    // 图片添加到表格中
    image_main = gtk_image_new_from_pixbuf(NULL);
    loadImage(image_main, "./image/zzx.png", 200, 200);
    gtk_table_attach_defaults(GTK_TABLE(table_main), image_main, 3, 7, 1, 4);

    // 标签添加到表格中

    label = gtk_label_new(""); // 标签
    gtk_label_set_markup(
        GTK_LABEL(label),
        "<span foreground='black' font_desc='22'>账号：</span>");
    gtk_table_attach_defaults(GTK_TABLE(table_main), label, 1, 3, ID_ROW_BRGIN,
                              ID_ROW_END);

    label = gtk_label_new(""); // 标签
    gtk_label_set_markup(
        GTK_LABEL(label),
        "<span foreground='black' font_desc='22'>密码：</span>");
    gtk_table_attach_defaults(GTK_TABLE(table_main), label, 1, 3,
                              PASSWD_ROW_BRGIN, PASSWD_ROW_END);

    // 输入框添加到表格中
    entry_id = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table_main), entry_id, 3, 8,
                              ID_ROW_BRGIN, ID_ROW_END);
    entry_passwd = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table_main), entry_passwd, 3, 8,
                              PASSWD_ROW_BRGIN, PASSWD_ROW_END);

    entry_Captcha = gtk_entry_new();
    gtk_table_attach_defaults(GTK_TABLE(table_main), entry_Captcha, 3, 5, 7, 8);

    // 按钮添加到表格中

    button_signin = gtk_button_new_with_label("注册");
    gtk_table_attach_defaults(GTK_TABLE(table_main), button_signin, 1, 3,
                              BUTTON_ROW_BRGIN, BUTTON_ROW_END);
    button_login = gtk_button_new_with_label("登录");
    gtk_table_attach_defaults(GTK_TABLE(table_main), button_login, 4, 6,
                              BUTTON_ROW_BRGIN, BUTTON_ROW_END);
    button_f5 = gtk_button_new_with_label("刷新");
    gtk_table_attach_defaults(GTK_TABLE(table_main), button_f5, 7, 9,
                              BUTTON_ROW_BRGIN, BUTTON_ROW_END);

    stsrt(pchar);

    char yzm[256] = "";
    sprintf(yzm, "<span foreground='black' font_desc='22'>验证码: %s</span>",
            pchar);

    label = gtk_label_new(""); // 验证码
    gtk_label_set_markup(GTK_LABEL(label), yzm);
    gtk_table_attach_defaults(GTK_TABLE(table_main), label, 6, 9, 7, 8);

    chang_background(window_main,800,500,"./image/1.jpg");

    // 按钮信号连接
    g_signal_connect(button_f5, "pressed",
                     G_CALLBACK(window_main_do_clean), NULL); // 刷新按钮

    g_signal_connect(button_signin, "pressed",
                     G_CALLBACK(window_main_do_signin), NULL); // 注册按钮

    g_signal_connect(button_login, "pressed",
                     G_CALLBACK(window_main_to_window_login), NULL); // 登录按钮

    guiTooltip(window_main, "欢迎使用宁氏猪场管理系统");

    // 主窗口显示
    gtk_widget_show_all(window_main);
    g_signal_connect(G_OBJECT(window_main), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
}

void stsrt(char *p) {
    int i = 0;
    srand(time(NULL));
    while (i < 4) {
        if (i % 2 == 0)
            p[i] = rand() % 26 + 'A';
        else if (i % 2 == 1)
            p[i] = rand() % 26 + 'a';
        else
            p[i] = rand() % 9 + '0';

        i++;
    }
    p[4] = '\0';
}
