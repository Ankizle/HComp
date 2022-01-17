#ifndef ELF_L_H_
#define ELF_L_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

struct ElfHeader {
    //see: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_header

    //magic number not needed here
    unsigned char bitformat;
    unsigned char endianness;
    unsigned char eiversion;
    unsigned char osabi;
    unsigned char abiver;
    unsigned char exectype[2];
    unsigned char machinetype[2];
    unsigned char version[4];
    unsigned char entry[8];
    unsigned char phoff[8];
    unsigned char shoff[8];
    unsigned char flags[4];
    unsigned char ehsize[2];
    unsigned char phentsize[2];
    unsigned char phnum[2];
    unsigned char shentsize[2];
    unsigned char shentnum[2];
    unsigned char shstrndx[2];
};

struct ProgramHeader {
    //see: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#Program_header

    unsigned char type[4];
    unsigned char flags[4];
    unsigned char offset[8];
    unsigned char vaddr[8];
    unsigned char paddr[8];
    unsigned char filesz[8];
    unsigned char memsz[8];
    unsigned char align[8];
};

struct SectionHeader {
    //see: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#Section_header

    unsigned char shname[4];
    unsigned char shtype[4];
    unsigned char shflags[8];
    unsigned char shaddr[8];
    unsigned char shoffset[8];
    unsigned char shsize[8];
    unsigned char shlink[4];
    unsigned char shinfo[4];
    unsigned char shaddralign[8];
    unsigned char shentsize[8];
};

struct ElfLib {

    FILE* execfile;
    const unsigned char* execfilename;
    int execfileidx;

    int nprogramheaders, nsectionheaders;

    struct ElfHeader elf_header;
    struct ProgramHeader* program_headers;
    struct SectionHeader* section_headers;
};

unsigned long readcur(void* o, int n, struct ElfLib* lib);
unsigned long readcurinc(void* o, int n, struct ElfLib* lib); 
unsigned long readpadcur(int n, struct ElfLib* lib); 

struct ElfHeader read_elf_header(struct ElfLib* lib);
struct ProgramHeader read_program_headers(struct ElfLib* lib, int offset);
struct SectionHeader read_section_headers(struct ElfLib* lib, int offset);

struct ElfLib* read_elf(const unsigned char* exepath);
void clean_elf(struct ElfLib* lib);

#ifdef __cplusplus
}
#endif

#endif