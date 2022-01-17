#include "exec_elf.h"
#include "app.h"

void exec_elf(struct App* app) {
    app->registers.rip = app->entry; //set the instruction pointer
}