#ifndef ELF_L_H_
#define ELF_L_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

struct ElfHeader {
    //see: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_header

    //magic number not needed here
    char bitformat;
    char endianness;
    char eiversion;
    char osabi;
    char abiver;
    char exectype;
    char machinetype[2];
    char version;
    char* entry;
    char* phoff;
    char* shoff;
    char flags[4];
    char ehsize[2];
    char phentsize[2];
    char phnum[2];
    char shentsize[2];
    char shentnum[2];
    char shstrndx[2];
};

struct ProgramHeader {
    //see: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#Program_header

    char type[4];
    char flags[4];
    char* offset;
    char* vaddr;
    char* paddr;
    char* filesz;
    char* memsz;
    char* align;
};

struct ElfLib {

    FILE* execfile;
    const char* execfilename;
    int execfileidx;

    struct ElfHeader* elf_header;
    struct ProgramHeader* program_header;
};

struct ElfHeader* read_elf_header(struct ElfLib* lib);
struct ProgramHeader* read_program_header(struct ElfLib* lib);

struct ElfLib* read_elf(const char* exepath);
void    clean_elf(struct ElfLib* lib);

#ifdef __cplusplus
}
#endif

#endif