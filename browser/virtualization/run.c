#include <bits/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "elf_l.h"
#include "util.h"
#include "executor/app.h"
#include "executor/load_elf.h"
#include "executor/exec_elf.h"

const __uint64_t DEFAULT_MEM_SIZ = 0xffffff;

int RunApp(unsigned char* exepath) {
    struct ElfLib* l = read_elf(exepath);

    __uint64_t
        entry_addr = twobytes_conv(l->elf_header.entry),
        mem_siz = DEFAULT_MEM_SIZ;

    unsigned char* ptr = mmap(0, mem_siz, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

    struct App* app = malloc(sizeof(struct App));
    app->lib = l;
    app->mem_start = ptr;
    app->mem_end = ptr + mem_siz;

    load_elf(app);
    exec_elf(app);

    //clean up the memory
    munmap(ptr, mem_siz);
    clean_elf(l);
    free(app);
}

int main(int argc, unsigned char** argv) {
    RunApp("../test/a.out");
}