#ifndef APP_H_
#define APP_H_

#include <bits/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <elf.h>
#include "elf_l.h"

struct App {
    struct ElfLib lib;
    unsigned char* exec;
    Elf64_Dyn* dyn;

    struct App* dynapps;
    size_t dynapps_amt; //how many shared libraries we have

    Elf64_Sym* dynsyms;
    size_t dynsyms_amt; //how many dynamic symbols (symbol table) we have
    char* dynstrtab; //dynamic string table
};

#ifdef __cplusplus
}
#endif

#endif