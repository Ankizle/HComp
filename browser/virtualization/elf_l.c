#include <stdlib.h>
#include <stdio.h>
#include "elf_l.h"

unsigned long readcur(void* o, int siz, int n, struct ElfLib* lib) {
    fseek(lib->execfile, lib->execfileidx, SEEK_SET);
    return fread(o, siz, n, lib->execfile);
}

unsigned long readcurinc(void* o, int siz, int n, struct ElfLib* lib) {
    fseek(lib->execfile, lib->execfileidx, SEEK_SET);
    lib->execfileidx+=n;
    return fread(o, siz, n, lib->execfile);
}


struct ElfLib* read_elf(const char* exepath) {
    struct ElfLib* l = malloc(sizeof(struct ElfLib));
    l->execfilename = exepath;
    l->execfile = fopen(exepath, "rb");
    l->execfileidx = 0;

    l->elf_header = read_elf_header(l);
    l->program_header = read_program_header(l);
    return l;
}

struct ElfHeader* read_elf_header(struct ElfLib *lib) {
    lib->elf_header = malloc(sizeof(struct ElfHeader));

    //read the magic numbers 0x00 - 0x04
    char magic[] = {0x7F, 'E', 'L', 'F'};
    for (;lib->execfileidx < 4;lib->execfileidx++) {
        char cur;
        readcur(&cur, 1, 1, lib);
        if (cur != magic[lib->execfileidx]); //error: given binary is not an ELF
    }

    //read bit-format (x86 or x86_64)
    readcurinc(&lib->elf_header->bitformat, 1, 1, lib);

    //read endianness
    readcurinc(&lib->elf_header->endianness, 1, 1, lib);

    //read the ei_version (only valid value is 1)
    readcurinc(&lib->elf_header->eiversion, 1, 1, lib);

    //read the ABI
    readcurinc(&lib->elf_header->osabi, 1, 1, lib);

    //read the ABI version
    readcurinc(&lib->elf_header->abiver, 1, 1, lib);

    //read all the padding bits (and do nothing with them)
    readcurinc(NULL, 0, 7, lib);

    //read the executable type
    readcurinc(&lib->elf_header->exectype, 1, 1, lib);

    //read the machine type
    readcurinc(&lib->elf_header->machinetype, 2, 2, lib);

    //read the version
    readcurinc(&lib->elf_header->version, 1, 4, lib);

    //read the entry point
    if (lib->elf_header->bitformat == 1) {
        //x86, 4 bytes long
        lib->elf_header->entry = malloc(4 * sizeof(char));
        lib->elf_header->phoff = malloc(4 * sizeof(char));
        lib->elf_header->shoff = malloc(4 * sizeof(char));

        readcurinc(lib->elf_header->entry, 4, 4, lib);
        readcurinc(lib->elf_header->phoff, 4, 4, lib);
        readcurinc(lib->elf_header->shoff, 4, 4, lib);
    }
    else {
        //x64, 8 bytes long
        lib->elf_header->entry = malloc(8 * sizeof(char));
        lib->elf_header->phoff = malloc(8 * sizeof(char));
        lib->elf_header->shoff = malloc(8 * sizeof(char));

        readcurinc(lib->elf_header->entry, 8, 8, lib);
        readcurinc(lib->elf_header->phoff, 8, 8, lib);
        readcurinc(lib->elf_header->shoff, 8, 8, lib);
    }

    readcurinc(lib->elf_header->flags, 4, 4, lib);
    readcurinc(lib->elf_header->ehsize, 2, 2, lib);
    readcurinc(lib->elf_header->phnum, 2, 2, lib);
    readcurinc(lib->elf_header->phnum, 2, 2, lib);
    readcurinc(lib->elf_header->shentsize, 2, 2, lib);
    readcurinc(lib->elf_header->shentnum, 2, 2, lib);
    readcurinc(lib->elf_header->shstrndx, 2, 2, lib);

    readcurinc(NULL, 0, 10, lib); //last 10 bytes are ending padding
    return lib->elf_header;
}

struct ProgramHeader* read_program_header(struct ElfLib* lib) { 
    lib->program_header = malloc(sizeof(struct ProgramHeader));

    readcurinc(&lib->program_header->type, 4, 4, lib);

    if (lib->elf_header->bitformat == 1) {
        readcurinc(lib->program_header->offset, 4, 4, lib);
        readcurinc(lib->program_header->vaddr, 4, 4, lib);
        readcurinc(lib->program_header->paddr, 4, 4, lib);
        readcurinc(lib->program_header->filesz, 4, 4, lib);

        //on x86 the flags are stored here
        readcurinc(lib->program_header->flags, 4, 4, lib);
        //on x64 the flags are stored elsewhere

        readcurinc(lib->program_header->align, 4, 4, lib);
    } else {

        //on x64 the flags are stored here
        readcurinc(lib->program_header->flags, 4, 4, lib);

        readcurinc(lib->program_header->offset, 8, 8, lib);
        readcurinc(lib->program_header->vaddr, 8, 8, lib);
        readcurinc(lib->program_header->paddr, 8, 8, lib);
        readcurinc(lib->program_header->filesz, 8, 8, lib);
        readcurinc(lib->program_header->align, 8, 8, lib);
    }

    readcurinc(NULL, 0, 0x18, lib); //0x18 bytes of padding

    return lib->program_header;
}

void clean_elf(struct ElfLib* lib) {
    free(lib->elf_header);
    free(lib->elf_header->entry);
    free(lib->elf_header->phoff);
    free(lib->elf_header->shoff);

    free(lib->program_header);
    free(lib->program_header->offset);
    free(lib->program_header->vaddr);
    free(lib->program_header->paddr);
    free(lib->program_header->filesz);
    free(lib->program_header->memsz);
    free(lib->program_header->align);

    free(lib);
}