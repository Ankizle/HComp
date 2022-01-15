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
    char exectype[2];
    char machinetype[2];
    char version;
    char entry[8];
    char phoff[8];
    char shoff[4];
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
    char flags[8];
    char offset[8];
    char vaddr[8];
    char paddr[8];
    char filesz[8];
    char memsz[8];
    char align[8];
};

struct SectionHeader {
    //see: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#Section_header

    char shname[4];
    char shtype[4];
    char shflags[8];
    char shaddr[8];
    char shoffset[8];
    char shsize[8];
    char shlink[4];
    char shinfo[4];
    char shaddralign[8];
    char shentsize[8];
};

struct ElfLib {

    FILE* execfile;
    const char* execfilename;
    int execfileidx;

    struct ElfHeader* elf_header;
    struct ProgramHeader* program_header;
    struct SectionHeader* section_header;
};

unsigned long readcur(void* o, int siz, int n, struct ElfLib* lib);
unsigned long readcurinc(void* o, int siz, int n, struct ElfLib* lib); 

struct ElfHeader* read_elf_header(struct ElfLib* lib);
struct ProgramHeader* read_program_header(struct ElfLib* lib, int offset);
struct SectionHeader* read_section_header(struct ElfLib* lib, int offset);

struct ElfLib* read_elf(const char* exepath);
void clean_elf(struct ElfLib* lib);

#ifdef __cplusplus
}
#endif

#endif