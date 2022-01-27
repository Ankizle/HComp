#ifndef REGISTERS_H_
#define REGISTERS_H_

#ifdef __cplusplus
extern "C" {
#endif

//store the registers a program uses
struct CPU_Registers {
    long long rax;
    long long rbx;
    long long rcx;
    long long rdx;
    long long rsi;
    long long rdi;
    long long rsp;
    long long rbp;
    long long r8;
    long long r9;
    long long r10;
    long long r11;
    long long r12;
    long long r13;
    long long r14;
    long long r15;

    unsigned long long rip;
};

#ifdef __cplusplus
}
#endif

#endif