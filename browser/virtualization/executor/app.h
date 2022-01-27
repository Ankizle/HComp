#ifndef APP_H_
#define APP_H_

#include <bits/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "./cpu/registers.h"
#include "./cpu/segment.h"
#include "../elf_l.h"

struct App {

    struct ElfLib* lib;

    unsigned long long entry; //entry point address

   //lower memory addresses
    unsigned char* mem_start;
    unsigned char* mem_end;
   //higher memory addresses

   struct CPU_Registers registers;
   struct CPU_Segment* segments;
};

#ifdef __cplusplus
}
#endif

#endif