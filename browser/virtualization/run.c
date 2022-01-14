#include <bits/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "elf_l.h"

const __uint64_t DEFAULT_MEM_SIZ = 0xffffffff;

//some values are pairs of bytes
//this function converts it to a single uint64
__uint64_t twobytes_conv(char v[2]) {
    return v[0] + v[1] * 0xff; //idx 0 is the lsb
}

int RunApp(char* exepath) {
    struct ElfLib* l = read_elf(exepath);

    __uint64_t
        entry_addr = twobytes_conv(l->elf_header->entry),
        start_addr = entry_addr - twobytes_conv(l->elf_header->ehsize) - twobytes_conv(l->elf_header->phentsize),
        mem_siz = DEFAULT_MEM_SIZ;

    void* alc = mmap((void*)start_addr, mem_siz, PROT_READ, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    memcpy(alc, l->execfile, l->elf_header->)
    munmap(alc, mem_siz);
}

int main() {
    RunApp("../test/a.out");
}