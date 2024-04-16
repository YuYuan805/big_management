#include "../inc/mysqlite.h"

char scanf_sqlname[20];
sqlite3 *Buy_Sell_db;      // 管理购买信息的数据库
sqlite3 *Keepers_db;       // 管理饲养信息的数据库
sqlite3 *headquarters_db;  // 数据库的总表.DB
char SQL_headquarters[20]; // 数据库的总表
char SQL_Subclasses[20];   // 数据库的子表

// 创建管理员账户子表
// sqlite3 * dbj      总表
// 如果同名子表已经存在则不创建且不提示错误信息
void create_SQL_manage_Subclasses(sqlite3 *dbj,
                                  const char *SQL_Subclasses_name) {
    char *error_message = NULL;
    char table_structureout[1000];
    char table_structure[300] = "账号 text ,密码 text";
    sprintf(table_structureout, "CREATE TABLE IF NOT EXISTS %s (%s);",
            SQL_Subclasses_name, table_structure);
    sqlite3_exec(dbj, table_structureout, NULL, NULL, &error_message);

    if (error_message != NULL)
        printf("error_message:  %s\n", error_message);
}

// 创建子表
// sqlite3 * dbj      总表
// 如果同名子表已经存在则不创建且不提示错误信息
void create_SQL_Sale_Subclasses(sqlite3 *dbj, const char *SQL_Subclasses_name) {
    char *error_message = NULL;
    char table_structureout[1000];
    char table_structure[300] =
        "订单编号 long int ,下单时间 long int, 品种 text, 姓别 text, 数量  "
        "int, 重量 int, 猪年龄 int, 买家信息 text, 买家电话 long int , 价格 "
        "long int";
    sprintf(table_structureout, "CREATE TABLE IF NOT EXISTS %s (%s);",
            SQL_Subclasses_name, table_structure);
    sqlite3_exec(dbj, table_structureout, NULL, NULL, &error_message);
    if (error_message != NULL)
        printf("error_message:  %s\n", error_message);
}
// 创建饲养信息子表
// sqlite3 * dbj      总表指针
// 如果同名子表已经存在则不创建且不提示错误信息
void create_SQL_Keepers_Subclasses(sqlite3 *dbj,
                                   const char *SQL_Subclasses_name) {
    char *error_message = NULL;
    char table_structureout[500];
    char table_structure[330] = {
        "编号 int , 品种 text, 姓别 text, 年份 int, 重量  int, 状态 text, "
        "饲料信息 text, 疫苗信息 text"};
    sprintf(table_structureout, "CREATE TABLE IF NOT EXISTS %s (%s);",
            SQL_Subclasses_name, table_structure);
    sqlite3_exec(dbj, table_structureout, NULL, NULL, &error_message);
    if (error_message != NULL)
        printf("error_message:  %s\n", error_message);
}
// 管理员账户信息写入
void SQL_manage_Subclasses_write(sqlite3 *dbj,                // 总表指针
                                 const char *Subclasses_name, // 子表名称
                                 const char *account,         // 管理员账户
                                 const char *password // 管理员账户密码
) {
    char *error_message = NULL;
    char Order_Information_cmdout[550];
    sprintf(Order_Information_cmdout, "insert into %s values(\'%s\',\'%s\');",
            Subclasses_name, // 子表名称
            account,         // 管理员账户
            password         // 管理员账户密码
    );
    sqlite3_exec(dbj, Order_Information_cmdout, NULL, NULL, &error_message);
    if (error_message != NULL)
        printf("error_message:  %s\n", error_message);
}
// 出售订单子表信息写入
void SQL_Sale_Subclasses_write(sqlite3 *dbj,                  // 总表指针
                               const char *Subclasses_name,   // 子表名称
                               long int Order_number,         // 订单编号
                               long int Order_time,           // 下单时间
                               const char *variety,           // 品种
                               const char *sex,               // 姓别
                               int num,                       // 数量
                               int weight,                    // 重量
                               int age,                       // 猪年龄
                               const char *Buyer_Information, // 买家信息
                               long int Buyer_phone,          // 买家电话
                               long int price                 // 价格
) {
    char *error_message = NULL;
    char Order_Information_cmdout[550];
    sprintf(Order_Information_cmdout,
            "insert into %s "
            "values(\'%ld\',\'%ld\',\'%s\',\'%s\',\'%d\',\'%d\',\'%d\',\'%s\',"
            "\'%ld\',\'%ld\');",
            Subclasses_name,   // 子表名称
            Order_number,      // 订单编号
            Order_time,        // 下单时间
            variety,           // 品种
            sex,               // 姓别
            num,               // 数量
            weight,            // 重量
            age,               // 猪年龄
            Buyer_Information, // 买家信息
            Buyer_phone,       // 买家电话
            price              // 价格
    );
    sqlite3_exec(dbj, Order_Information_cmdout, NULL, NULL, &error_message);
    if (error_message != NULL)
        printf("error_message:  %s\n", error_message);
}

// 饲养信息子表写入
void SQL_Keepers_Subclasses_write(sqlite3 *dbj,                 // 总表指针
                                  const char *Subclasses_name,  // 子表名称
                                  int numbering,                // 编号
                                  const char *variety,          // 品种
                                  const char *sex,              // 姓别
                                  int year,                     // 年份、
                                  int weight,                   // 重量
                                  const char *state,            // 状态
                                  const char *Feed_information, // 饲料信息
                                  const char *Vaccine_information // 疫苗信息
) {
    char *error_message = NULL;
    char Order_Information_cmdout[550];
    sprintf(Order_Information_cmdout,
            "insert into %s "
            "values(\'%d\',\'%s\',\'%s\',\'%d\',\'%d\',\'%s\',\'%s\',\'%s\');",
            Subclasses_name,    // 子表名称
            numbering,          // 编号
            variety,            // 品种
            sex,                // 姓别
            year,               // 年份、
            weight,             // 重量
            state,              // 状态
            Feed_information,   // 饲料信息
            Vaccine_information // 疫苗信息
    );
    sqlite3_exec(dbj, Order_Information_cmdout, NULL, NULL, &error_message);
    if (error_message != NULL)
        printf("error_message:  %s\n", error_message);
}

// 打印总表下所有子表的信息
void sqlite_printf_all_tables(sqlite3 *dbj) {
    char *err_msg = 0;
    char **result, **result2;
    int rows, columns;
    int hhj;
    int srows, ii = 0;
    // 查询所有表的名称
    hhj = sqlite3_get_table(dbj,
                            "SELECT name FROM sqlite_master WHERE type='table'",
                            &result, &rows, &columns, &err_msg);
    printf("共查到有...-----------------%d个子表:\n\n", rows);
    if (hhj != SQLITE_OK) {
        fprintf(stderr, "Failed to execute query: %s\n", err_msg);
        sqlite3_free(err_msg);
        return; // 返回函数如果查询失败
    }
    printf("%d  %d\n", rows, columns);
    int i = 0, kk = 0;
    printf("-------------------------------------------------\n");
    for (i = 0; i < rows + 1; ++i) {
        for (kk = 0; kk < columns; ++kk) {
            printf("{%s}", result[i * columns + kk]);
        }
        printf("\n");
    }
    printf("-------------------------------------------------\n");

    if (result[1] == NULL)
        printf("没有子表\n\n");
    else {
        for (ii = 0; ii < rows; ++ii) {
            // printf("999999\n");
            if (ii == 0)
                printf("\t  %s\n", result[ii]);
            else
                printf("result[%d]: %s\n", ii, result[ii]);
        }
        srows = rows;
        printf("srows: %d\n", srows);
        printf("1111\n");
        // 对每个表执行查询并打印结果
        printf("开始打印子表:\n");
        for (int i = 1; i <= srows; i++) {
            printf("当前第%d个子表: %s\n", i, result[i]);
            char *table_name = result[i];

            // 构造查询语句
            char sqlite3_name[100];
            sprintf(sqlite3_name, "SELECT * FROM %s", table_name);

            // 执行查询
            hhj = sqlite3_get_table(dbj, sqlite3_name, &result2, &rows,
                                    &columns, &err_msg);
            // printf("result2[%d]: %s\n",ii, result2[ii]);
            printf("222222\n");
            if (result2[1] == NULL)
                continue;
            if (hhj != SQLITE_OK) {
                fprintf(stderr, "Failed to execute query for table %s: %s\n",
                        table_name, err_msg);
                sqlite3_free(err_msg);
                continue; // 继续下一个表的查询
            }

            // 打印查询结果
            for (int j = 0; j <= rows; j++) {
                for (int k = 0; k < columns; k++) {
                    printf("%s\t", result2[j * columns + k]);
                }
                printf("\n");
            }
            if (result[i + 1] != NULL)
                printf("\n继续下一个子表的查询是: %s\n", result[i + 1]);
            else
                printf("\n已打印完子表\n\n");
            printf("\n\n");
        }
        sqlite3_free_table(result);
    }
}

// 返回子表信息
char **Find_SQL_Subclasses(const char *SQL_headquarters, int *row_num,
                           int *columns_num) {
    char *err_msg = 0;
    char **result, **result2;
    int rows, columns = 0, hhj = 0, i = 0;
    // 查询所有表的名称
    hhj = sqlite3_get_table(headquarters_db,
                            "SELECT name FROM sqlite_master WHERE type='table'",
                            &result, &rows, &columns, &err_msg);
    printf("共查到有------2---%d个子表:\n\n", rows);
    if (hhj != SQLITE_OK) {
        fprintf(stderr, "Failed to execute query: %s\n", err_msg);
        sqlite3_free(err_msg);
        return NULL; // 返回函数如果查询失败
    }

    // 查询表的位置
    char *table_name;
    while (1) {
        printf("SQL_headquarters   %s\n\n", SQL_headquarters);
        printf("result[i] %s\n\n", result[i]);

        if (strcmp(SQL_headquarters, result[i]) == 0) {
            break;
        }
        else
            i++;
    }
    table_name = result[i]; // 记录表的位置
    printf("这个子表为空: %s\n", table_name);
    // 构造查询语句
    char sqlite3_name[300];
    sprintf(sqlite3_name, "SELECT * FROM %s", table_name);

    // 执行查询
    hhj = sqlite3_get_table(headquarters_db, sqlite3_name, &result2, &rows,
                            &columns, &err_msg);
    *row_num = rows;
    *columns_num = columns;
    printf("共查到有------2---%d个子表:\n\n", rows);
    if (result2[1] == NULL) // 防止表中没数据
    {
        printf("这个子表为空: %s\n", table_name);
        return NULL; // 返回函数如果查询失败
    }
    if (hhj != SQLITE_OK) // 查询报错
    {
        fprintf(stderr, "Failed to execute query for table %s: %s\n",
                table_name, err_msg);
        sqlite3_free(err_msg);
        return NULL; // 返回函数如果查询失败
    }
    return result2; // 返回表信息
}

// 返回总表信息
char **Find_headquarters(const char *SQL_headquarters) {
    char *err_msg = NULL, **result = NULL;
    int rows = 0, columns = 0, hhj = 0;
    // 查询所有表的名称
    hhj = sqlite3_get_table(headquarters_db,
                            "SELECT name FROM sqlite_master WHERE type='table'",
                            &result, &rows, &columns, &err_msg);
    printf("共查到有------3--%d个子表:\n\n", rows);
    if (hhj != SQLITE_OK) {
        fprintf(stderr, "Failed to execute query: %s\n", err_msg);
        sqlite3_free(err_msg);
        return NULL; // 返回函数如果查询失败
    }
    return result;
}
// 删除行
void SQL_delete_row(sqlite3 *dbj, const char *SQL_name, int delete_row) {
    // sqlite3 *dbj;
    char *err_msg = 0;
    // 执行删除操作的 SQL 语句
    // char cmd[100] = "your_table_name WHERE condition;";
    char delete_cmd[100];
    sprintf(delete_cmd, "DELETE FROM %s WHERE id = %d ;", SQL_name, delete_row);

    // 执行 SQL 语句
    sqlite3_exec(dbj, delete_cmd, NULL, NULL, &err_msg);
    if (err_msg != NULL)
        printf("行删除失败: %s\n", err_msg);
    else
        printf("行删除成功\n");
}

// 修改编号信息
void SQL_columns_revise(sqlite3 *dbj,                   // 总表指针
                        const char *Subclasses_name,    // 子表名称
                        int numbering,                  // 编号
                        const char *variety,            // 品种
                        const char *sex,                // 姓别
                        int year,                       // 年份
                        int weight,                     // 重量
                        const char *state,              // 状态
                        const char *Feed_information,   // 饲料信息
                        const char *Vaccine_information // 疫苗信息
) {
    // sqlite3 *db;
    char *err_msg = 0;
    // 执行删除操作的 SQL 语句
    // char cmd[100] = " your_table_name WHERE condition;";
    char delete_cmd[500];
    sprintf(
        delete_cmd,
        "UPDATE \'%s\' SET 品种=\'%s\' ,姓别=\'%s\' ,年份=\'%d\' ,重量=\'%d\' "
        ",状态=\'%s\' ,饲料信息=\'%s\' ,疫苗信息=\'%s\' WHERE 编号=%d ;",
        Subclasses_name, variety, sex, year, weight, state, Feed_information,
        Vaccine_information, numbering);
    printf("delete_cmd: %s\n", delete_cmd);
    // 执行 SQL 语句
    sqlite3_exec(dbj, delete_cmd, NULL, NULL, &err_msg);
    if (err_msg != NULL)
        printf("行删除失败: %s\n", err_msg);
    else
        printf("行删除成功\n");
}

// 数据库初始化
int SQL_manage_init(const char *SQL_headquarters) {
    int st;
    st = sqlite3_open(SQL_headquarters, &headquarters_db);
    if (st != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(headquarters_db));
        sqlite3_close(headquarters_db);
        return 1;
    }
    printf("%s打开成功\n", SQL_headquarters);
    return 0;
}

void sqlInit(void) {
    SQL_manage_init("./data/管理人员.db");

    create_SQL_manage_Subclasses(headquarters_db, "管理员");
    create_SQL_Sale_Subclasses(headquarters_db, "出售记录");
    create_SQL_Keepers_Subclasses(headquarters_db, "养殖记录");

    SQL_manage_Subclasses_write(headquarters_db, "管理员", "admin", "123");
}

void sqlUninit(void) { sqlite3_close(headquarters_db); }
