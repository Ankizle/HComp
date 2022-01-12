#ifndef APP_H_
#define APP_H_

#include <bits/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include "elf_l.h"

typedef struct App {

    ElfLib* lib;

    __uint64_t mem_start;
} App;

#ifdef __cplusplus
}
#endif

#endif