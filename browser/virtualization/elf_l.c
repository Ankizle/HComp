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

    read_elf_header(l);
    // read_program_header(l);
    read_section_header(l);
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
    readcurinc(lib->elf_header->exectype, 2, 2, lib);

    //read the machine type
    readcurinc(lib->elf_header->machinetype, 2, 2, lib);

    //read the version
    readcurinc(&lib->elf_header->version, 1, 4, lib);

    //read the entry point
    int en_ph_sh_siz = 8; //the size of the next 3 entries in bytes (8 bytes in x64)
    if (lib->elf_header->bitformat == 1)
        //x86, 4 bytes long
        en_ph_sh_siz = 4;

    readcurinc(lib->elf_header->entry, en_ph_sh_siz, en_ph_sh_siz, lib);
    readcurinc(lib->elf_header->phoff, en_ph_sh_siz, en_ph_sh_siz, lib);
    readcurinc(lib->elf_header->shoff, en_ph_sh_siz, en_ph_sh_siz, lib);

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

    int datsiz = lib->elf_header->bitformat == 1 ? 4 /*x86*/ : 8 /*x64*/;

    if (datsiz == 8)
        //on x64 the flags are stored here
        readcurinc(lib->program_header->flags, datsiz, datsiz, lib);
        //on x64 the flags are stored elsewhere

    readcurinc(lib->program_header->offset, datsiz, datsiz, lib);
    readcurinc(lib->program_header->vaddr, datsiz, datsiz, lib);
    readcurinc(lib->program_header->paddr, datsiz, datsiz, lib);
    readcurinc(lib->program_header->filesz, datsiz, datsiz, lib);

    if (datsiz == 4)
        //on x86 the flags are stored here
        readcurinc(lib->program_header->flags, datsiz, datsiz, lib);

    readcurinc(lib->program_header->align, datsiz, datsiz, lib);

    readcurinc(NULL, 0, 0x18, lib); //0x18 bytes of padding

    return lib->program_header;
}

struct SectionHeader* read_section_header(struct ElfLib* lib) {
    lib->section_header = malloc(sizeof(struct SectionHeader));
}

void clean_elf(struct ElfLib* lib) {
    free(lib->elf_header);

    free(lib->program_header);

    free(lib->section_header);

    free(lib);
}