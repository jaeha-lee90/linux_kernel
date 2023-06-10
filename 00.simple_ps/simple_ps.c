#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <fcntl.h>

int main() {
    while(1) {
        DIR *dirp = opendir("/proc");
        struct dirent *dp;

        if (!dirp) {
            perror("opendir");
            return 1;
        }

        printf("PID\tTTY\tCMD\n");

        while ((dp = readdir(dirp)) != NULL) {
            int pid = atoi(dp->d_name); // Convert string to integer

            if (pid > 0) { // It is a process directory
                char cmd_path[256];
                char cmd[256];

                // Read cmdline
                snprintf(cmd_path, sizeof(cmd_path), "/proc/%d/cmdline", pid);
                int fd = open(cmd_path, O_RDONLY);
                if (fd >= 0) {
                    ssize_t length = read(fd, cmd, sizeof(cmd) - 1);
                    if (length > 0) {
                        cmd[length] = '\0';

                        // Replace null characters with spaces
                        for (int i = 0; i < length; i++) {
                            if (cmd[i] == '\0') {
                                cmd[i] = ' ';
                            }
                        }

                        // Assume TTY is pts/0 for example. (You can further refine to fetch actual TTY).
                        printf("%d\tpts/0\t%s\n", pid, cmd);
                    }
                    close(fd);
                }
            }
        }

        closedir(dirp);

        sleep(1); // Sleep for 1 second
        printf("\n");
    }

    return 0;
}