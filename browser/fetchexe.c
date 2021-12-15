#include <stdio.h>

#include <string.h>
#include <stdlib.h>

void fetchEXE_SCP(char *sshd)
{

    char f = malloc((3 + //"scp"
                     1 + //" "
                     strlen(sshd) +
                     1 +             //" "
                     strlen("~/")) * // download to the home directory of the hcomp usr
                    sizeof(char *));

    sprintf(f, "scp %s %s", sshd, "~/"); // fmt the string so it contains the full command
    system(f);                           // execute the cmd to download from ssh

    free(f);
}