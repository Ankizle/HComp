#ifndef APP_H_
#define APP_H_

#include <bits/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "elf_l.h"

struct App {
    struct ElfLib lib;
};

#ifdef __cplusplus
}
#endif

#endif