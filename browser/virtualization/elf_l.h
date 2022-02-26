#ifndef ELF_L_H_
#define ELF_L_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <elf.h>

struct ElfLib {

    FILE* execfile;

    Elf64_Ehdr elf_header;
    Elf64_Phdr* program_headers;
    Elf64_Shdr* section_headers;
};

struct ElfLib read_elf_file(FILE* file);
struct ElfLib read_elf(const char* exepath);
void clean_elf(struct ElfLib* lib);

#ifdef __cplusplus
}
#endif

#endif