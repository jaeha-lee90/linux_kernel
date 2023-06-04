#include <stdio.h>

#include <system_server.h>
#include <gui.h>
#include <input.h>
#include <web_server.h>

int create_web_server()
{
    pid_t systemPid;

    printf("여기서 Web Server 프로세스를 생성합니다.\n");

    /* fork + exec 를 이용하세요 */
    /* exec으로 filebrowser을 실행 하세요. */
    /* execl("/usr/local/bin/filebrowser", "filebrowser", "-p", "8282", (char *) NULL)) */
    /* fork + exec 를 이용하세요 */
    systemPid = fork();
    switch(systemPid)
    {
      case -1:
        printf("Failed!!!\n");
        break;
      case 0:
          printf(" current Process id = %d :: parent pid = %d \n",systemPid, getppid());
          execl("/usr/local/bin/filebrowser","filebrowser","-p","8282",(char*)NULL);
          break;
      default:
            printf("parent id = %d \n", systemPid);
            break;
    }
    return 0;
}
