#include <stdbool.h>
#include "exec_elf.h"
#include "../app.h"
#include "./modrm.h"
#include "./init.h"

long long next(struct App* app, int amt) {
    long long r = 0;
    int oamt = amt;
    for (unsigned char* c = app->mem_start + app->registers.rip + amt; amt > 0; amt--, app->registers.rip++) {
        r<<=8;
        r|=(*c--);
    }
    return r;
}

void exec_elf(struct App* app) {

    initregisters(app);
    app->registers.rip = app->entry; //set the instruction pointer

    int i = 0;

    while (true) {

        if (i++ > 10) break; //FOR TESTING ONLY

        //http://ref.x86asm.net/coder64.html#xB8
        switch (app->mem_start[app->registers.rip]) {
            case 0x00: {
                //add r/m8 r8
                struct ModRM operand = parseModRM((app->mem_start[++app->registers.rip]));
                interpretModRM(&operand, app, -1);
                *operand.offset+=*operand.regval;
                break;
            }
            //...
            case 0xff: {
                break;
            }
        }
        app->registers.rip++;
        break;
    }
}