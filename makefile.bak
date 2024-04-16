#makefile文件为shell脚本文件
#主要是做编译指令的编写
#我们拥有了makefile之后
#在编译的时候只需要在终端中敲make就可以直接编译
#如果我想要清除一下当前的系统的生成的过程文件
#你可以敲make clean
#shell---启动程序开发boot-loader、makefile
#如下所示CC、MAINC、EXEC、CFLAGS这些统统是特殊变量
CC = gcc

INC_DIR = ./inc/

# 从源文件目录中获取所有的.c文件
SRC_DIR = ./src
SOURCES := $(wildcard $(SRC_DIR)/*.c)
#MAINC表示的是你要编译的文件名称
EXEC = ./bin/SwinePlant
#exec表示的是你生成的可执行文件名
CFLAGS = -Wall `pkg-config --cflags --libs gtk+-2.0` -lpthread -ldl 
#CFLAGS表示加的属性和连接



main:  
	$(CC) -I $(INC_DIR) -Wall -o $(EXEC) $(SOURCES) $(CFLAGS)
#gcc main.c sqlite3.c  -o demo -lpthread -ldl `pkg-config --cflags --libs gtk+-2.0`
#main表示你在当前文件夹中敲make他会进行什么操作
clean:
	rm $(EXEC) -rf
#clean表示你在当前的文件夹中敲make clean的时候他会做什么