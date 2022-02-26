#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <elf.h>
#include <stdlib.h>
#include "elf_l.h"
#include "app.h"
#include "run.h"
#include "dynamic.h"
#define DEFAULT_MEM_SIZ 0xffffff

struct App load_elfmem_file(FILE* file) {
    struct ElfLib lib = read_elf_file(file);
    struct App app;
    app.lib = lib;

    app.dynapps = NULL;
    app.dynapps_amt = 0;
    app.dynsyms = NULL;
    app.dynsyms_amt = 0;

    unsigned char* exec = mmap(NULL, DEFAULT_MEM_SIZ, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memset(exec, 0, DEFAULT_MEM_SIZ);
    app.exec = exec;

    for (int i = 0; i < lib.elf_header.e_phnum; i++) {
        Elf64_Phdr phdr = lib.program_headers[i];

        fseek(lib.execfile, phdr.p_offset, SEEK_SET);
        switch (phdr.p_type) {
            case PT_LOAD: {
                mprotect(exec + phdr.p_vaddr, phdr.p_memsz, PROT_WRITE);
                fread(exec + phdr.p_vaddr, sizeof(unsigned char), phdr.p_memsz, lib.execfile);
                break;
            }
            case PT_DYNAMIC: {
                interpret_dynamic_sect(&app, phdr);
                break;
            }
        }

        int flags = PROT_READ; //CHANGE BACK TO PROT_NONE

        #define HASFLAG(flag) if (phdr.p_flags & flag) flags|=flag

        HASFLAG(PROT_EXEC); //execute flag on
        HASFLAG(PROT_WRITE); //write flag on
        HASFLAG(PROT_READ); //read flag on
        
        mprotect(exec + phdr.p_vaddr, phdr.p_memsz, flags);
    }

    return app;
}

struct App load_elfmem(char* bin) {
    return load_elfmem_file(fopen(bin, "rb"));
}