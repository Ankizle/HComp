#include <stdbool.h>
#include "exec_elf.h"
#include "../app.h"
#include "./modrm.h"
#include "./init.h"

//get the next x bytes in data, and convert it to an integer (little endian)
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
    unsigned char prefix = 0;

    while (true) {

        //http://ref.x86asm.net/coder64.html#xB8
        switch (app->mem_start[app->registers.rip]) {
            case 0x10:
            case 0x00: {
                //add r/m8 r8
                struct ModRM operand = parseModRM((app->mem_start[++app->registers.rip]));
                interpretModRM(&operand, app, prefix);
                *(char*)(operand.offset)+=*(char*)(operand.regval);
                break;
            }
            case 0x11:
            case 0x01: {
                //add r/m16/32/64 r16/32/64
                struct ModRM operand = parseModRM((app->mem_start[++app->registers.rip]));
                interpretModRM(&operand, app, prefix);
                switch (prefix) {
                    case 0x66: {
                        //16 bit
                        *(short*)(operand.offset)+=*(short*)(operand.regval);
                        break;
                    }
                    case 0x48: {
                        //64 bit
                        *(long long*)(operand.offset)+=*(long long*)(operand.regval);
                        break;
                    }
                    default: {
                        //32 bit
                        *(int*)(operand.offset)+=*(int*)(operand.regval);
                        break;
                    }
                }
            }
            case 0x12:
            case 0x02: {
                //add r8 r/m8
                struct ModRM operand = parseModRM((app->mem_start[++app->registers.rip]));
                interpretModRM(&operand, app, prefix);
                *(char*)(operand.regval)+=*(char*)(operand.offset);
                break;
            }
            case 0x13:
            case 0x03: {
                //add r16/32/64 r/m16/32/64
                struct ModRM operand = parseModRM((app->mem_start[++app->registers.rip]));
                interpretModRM(&operand, app, prefix);
                switch (prefix) {
                    case 0x66: {
                        //16 bit
                        *(short*)(operand.regval)+=*(short*)(operand.offset);
                        break;
                    }
                    case 0x48: {
                        //64 bit
                        *(long long*)(operand.regval)+=*(long long*)(operand.offset);
                        break;
                    }
                    default: {
                        //32 bit
                        *(int*)(operand.regval)+=*(int*)(operand.offset);
                        break;
                    }
                }
            }
            case 0x14:
            case 0x04: {
                //add al, imm8
                *(char*)(app->registers.rax)+=next(app, 1);
                break;
            }
            case 0x15:
            case 0x05: {
                //add rax, imm32
                *(long long*)(app->registers.rax)+=next(app, 4);
            }
            case 0x08: {
                //or r/m8 r8
                struct ModRM operand = parseModRM((app->mem_start[++app->registers.rip]));
                interpretModRM(&operand, app, prefix);
                *(char*)(operand.offset)|=*(char*)(operand.regval);
                break;
            }
            case 0x09: {
                //or r/m16/32/64 r16/32/64
                struct ModRM operand = parseModRM((app->mem_start[++app->registers.rip]));
                interpretModRM(&operand, app, prefix);
                switch (prefix) {
                    case 0x66: {
                        //16 bit
                        *(short*)(operand.offset)|=*(short*)(operand.regval);
                        break;
                    }
                    case 0x48: {
                        //64 bit
                        *(long long*)(operand.offset)|=*(long long*)(operand.regval);
                        break;
                    }
                    default: {
                        //32 bit
                        *(int*)(operand.offset)|=*(int*)(operand.regval);
                        break;
                    }
                }
            }
            case 0x0a: {
                //or r8 r/m8
                struct ModRM operand = parseModRM((app->mem_start[++app->registers.rip]));
                interpretModRM(&operand, app, prefix);
                *(char*)(operand.regval)|=*(char*)(operand.offset);
                break;
            }
            case 0x0b: {
                //or r16/32/64 r/m16/32/64
                struct ModRM operand = parseModRM((app->mem_start[++app->registers.rip]));
                interpretModRM(&operand, app, prefix);
                switch (prefix) {
                    case 0x66: {
                        //16 bit
                        *(short*)(operand.regval)|=*(short*)(operand.offset);
                        break;
                    }
                    case 0x48: {
                        //64 bit
                        *(long long*)(operand.regval)|=*(long long*)(operand.offset);
                        break;
                    }
                    default: {
                        //32 bit
                        *(int*)(operand.regval)|=*(int*)(operand.offset);
                        break;
                    }
                }
            }
            case 0x0c: {
                //or al, imm8
                *(char*)(app->registers.rax)|=next(app, 1);
                break;
            }
            case 0x0d: {
                //or rax, imm32
                *(long long*)(app->registers.rax)|=next(app, 4);
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