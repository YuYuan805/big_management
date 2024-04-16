#ifndef __SQL_manage_H
#define __SQL_manage_H

#include <sqlite3.h>
#include <stdio.h>
#include <string.h>


void create_SQL_manage_Subclasses(
    sqlite3 *dbj, const char *SQL_Subclasses_name); // 创建管理员账户子表
void create_SQL_Sale_Subclasses(sqlite3 *dbj,
                                const char *SQL_Subclasses_name); // 创建子表
void create_SQL_Keepers_Subclasses(
    sqlite3 *dbj, const char *SQL_Subclasses_name); // 创建饲养信息子表

// 管理员账户信息写入
void SQL_manage_Subclasses_write(sqlite3 *dbj,                // 总表指针
                                 const char *Subclasses_name, // 子表名称
                                 const char *account,         // 管理员账户
                                 const char *password // 管理员账户密码
);

// 子表信息写入
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
);
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
);

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

);

void sqlite_printf_all_tables(sqlite3 *dbj); // 打印总表下所有子表的信息
void SQL_delete_row(sqlite3 *dbj, const char *SQL_name, int delete_row);

// 返回子表信息
char **Find_SQL_Subclasses(const char *SQL_headquarters, int *row_num,
                           int *columns_num);

char **Find_headquarters(const char *SQL_headquarters); // 返回总表信息

int main(int argc, char *argv[]);
int SQL_manage_init(const char *SQL_headquarters); // 数据库初始化
void sqlInit(void);
void sqlUninit(void);

#endif