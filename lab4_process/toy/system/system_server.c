#include <stdio.h>
#include <sys/prctl.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int system_server()
{
    printf("나 system_server 프로세스!\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

int create_system_server()
{
    pid_t systemPid;
    const char *name = "system_server";

    printf("여기서 시스템 프로세스를 생성합니다.\n");
    /* fork 를 이용하세요 */
    systemPid = fork();
    switch(systemPid)
    {
      case -1:
        printf("Form Failed system server----\n");
        break;
      case 0:
        printf("Parent Pid = %d :: Child Pid = %d \n", systemPid, getppid());
        system_server();
        break;
      default:

        printf("Parent Pid = %d \n", systemPid);
    }
    /* fork 를 이용하세요 */

    return 0;
}
