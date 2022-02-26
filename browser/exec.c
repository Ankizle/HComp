#include <stdlib.h>
#include <unistd.h>
#include "exec.h"

int exec(char* file) {
    execve(file, NULL, NULL);
}