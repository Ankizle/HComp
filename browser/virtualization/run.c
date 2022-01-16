#include <bits/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "elf_l.h"
#include "util.h"

const __uint64_t DEFAULT_MEM_SIZ = 0xffffffff;

int RunApp(char* exepath) {
    struct ElfLib* l = read_elf(exepath);

    __uint64_t
        entry_addr = twobytes_conv(l->elf_header.entry),
        mem_siz = DEFAULT_MEM_SIZ;

    printf("%lx\n", bytes_conv(l->section_headers[1].shsize, 8));

    void* alc = mmap((void*)entry_addr, mem_siz, PROT_READ, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    munmap(alc, mem_siz);
}

int main(int argc, char** argv) {
    RunApp("../test/a.out");
}