#include <stdlib.h>
#include "../app.h"

void initregisters(struct App* app) {
    app->registers.rax = malloc(sizeof(long long));
    *app->registers.rax = 0;
    
    app->registers.rbx = malloc(sizeof(long long));
    *app->registers.rbx = 0;
    
    app->registers.rcx = malloc(sizeof(long long));
    *app->registers.rcx = 0;

    app->registers.rdx = malloc(sizeof(long long));
    *app->registers.rdx = 0;

    app->registers.rsi = malloc(sizeof(long long));
    *app->registers.rsi = 0;

    app->registers.rdi = malloc(sizeof(long long));
    *app->registers.rdi = 0;

    app->registers.rsp = malloc(sizeof(long long));
    *app->registers.rsp = 0;

    app->registers.rbp = malloc(sizeof(long long));
    *app->registers.rbp = 0;

    app->registers.r8 = malloc(sizeof(long long));
    *app->registers.r8 = 0;

    app->registers.r9 = malloc(sizeof(long long));
    *app->registers.r9 = 0;

    app->registers.r10 = malloc(sizeof(long long));
    *app->registers.r10 = 0;

    app->registers.r11 = malloc(sizeof(long long));
    *app->registers.r11 = 0;

    app->registers.r12 = malloc(sizeof(long long));
    *app->registers.r12 = 0;

    app->registers.r13 = malloc(sizeof(long long));
    *app->registers.r13 = 0;

    app->registers.r14 = malloc(sizeof(long long));
    *app->registers.r14 = 0;

    app->registers.r15 = malloc(sizeof(long long));
    *app->registers.r15 = 0;
}