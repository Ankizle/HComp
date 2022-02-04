#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <elf.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "elf_l.h"
#include "app.h"
#define DEFAULT_MEM_SIZ 0xffffffff

int main(int argc, char** argv)
{
    struct ElfLib lib = read_elf(argv[1]);
    struct App app;
    app.lib = lib;

    unsigned char* exec = mmap(NULL, DEFAULT_MEM_SIZ, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memset(exec, 0, DEFAULT_MEM_SIZ);

    for (int i = 0; i < lib.elf_header.e_phnum; i++) {
        Elf64_Phdr phdr = lib.program_headers[i];

        fseek(lib.execfile, phdr.p_offset, SEEK_SET);
        switch (phdr.p_type) {
            case PT_LOAD: {
                fread(exec + phdr.p_vaddr, sizeof(unsigned char), phdr.p_memsz, lib.execfile);
                break;
            }
            case PT_DYNAMIC: {
                break;
            }
            case PT_INTERP: {
                char* interp = calloc(sizeof(char), phdr.p_memsz + 1);
                fread(interp, sizeof(char), phdr.p_memsz, lib.execfile);
                break;
            }
            case PT_PHDR: {
                break;
            }
        }

        int flags = PROT_NONE;

        #define HASFLAG(flag) if (phdr.p_flags & flag) flags|=flag

        HASFLAG(PROT_EXEC); //execute flag on
        HASFLAG(PROT_WRITE); //write flag on
        HASFLAG(PROT_READ); //read flag on
        
        mprotect(exec + phdr.p_vaddr, phdr.p_memsz, flags);
    }

    // void (*v)() = (void*)(exec + lib.elf_header.e_entry);
    // v();
}