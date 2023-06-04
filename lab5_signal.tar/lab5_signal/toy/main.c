#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

/* 여기서 sigchld 핸들러 구현 */
static void
sigchldHandler(int sig)
{
    int status, oldErrno;
    pid_t childpid;

    oldErrno = errno;
    printf("handler : Caught SIGCHLD : 17\n");
    printf("handler : returning\n");
    /*
    while((childpid=waitpid(-1, &status, WNOHANG)) > 0){
        printf("handler : reaping child(PID : %d)", childpid);
    }
    */
    errno = oldErrno;
}

int main()
{
    pid_t spid, gpid, ipid, wpid;
    int status, savedErrno;
    int sigCnt;
    sigset_t blockMask, emptyMask;
    struct sigaction sa;

    /* 여기서 SIGCHLD 시그널  등록 */
    sigemptyset(&sa.sa_mask);
    sa.sa_flags=0;
    sa.sa_handler = sigchldHandler;
    if(sigaction(SIGCHLD, &sa, NULL) == -1) // register SIGCHLD handler
        perror("sigaction error");
    
    /*
    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGCHLD);
    if(sigprocmask(SIG_SETMASK, &blockMask, NULL) == -1)
        perror("sigprocmask failed");
    */

    printf("메인 함수입니다.\n");
    printf("시스템 서버를 생성합니다.\n");
    spid = create_system_server();
    printf("웹 서버를 생성합니다.\n");
    wpid = create_web_server();
    printf("입력 프로세스를 생성합니다.\n");
    ipid = create_input();
    printf("GUI를 생성합니다.\n");
    gpid = create_gui();

    waitpid(spid, &status, 0);
    waitpid(gpid, &status, 0);
    waitpid(ipid, &status, 0);
    waitpid(wpid, &status, 0);

    return 0;
}