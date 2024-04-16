#include "../inc/gui_login.h"
#include "../inc/gui_main.h"
#include "../inc/gui_store.h"
#include "../inc/gui_support.h"
#include "../inc/mysqlite.h"

int main(int argc, char *argv[]) {
    sqlInit();
    gtk_init(&argc, &argv);
    guiMain();
    guiLogin();
    guiStore();
    guiSupport();

    mkfifo("cmd_fifo", 0777);
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork\n");
    }
    else if (pid == 0) {
        execlp("mplayer", "mplayer", "-slave", "-quiet", "-idle", "-input",
               "file=./cmd_fifo", "./music/zzx.mp3", NULL);
        _exit(0);
    }
    else {
        int fd = open("cmd_fifo", O_WRONLY);
        write(fd, "pause\n", strlen("pause\n"));
        close(fd);
        gtk_main();
    }
    sqlUninit();
    musicQuit();
    return 0;
}
