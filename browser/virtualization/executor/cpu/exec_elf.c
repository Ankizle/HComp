#include <stdbool.h>
#include "exec_elf.h"
#include "../app.h"
#include "modrm.h"

void exec_elf(struct App* app) {

    printf("%u\n", parseModRM(0b11000000).mod);

    app->registers.rip = app->entry; //set the instruction pointer

    // while (true) {
    //     //http://ref.x86asm.net/coder64.html#xB8
    //     switch (app->mem_start[app->registers.rip]) {
    //         case 0x00: {
    //             //add r/m8 r8
    //             break;
    //         }
    //         //...
    //         case 0xff: {
    //             break;
    //         }
    //     }
    //     app->registers.rip++;
    // }
}