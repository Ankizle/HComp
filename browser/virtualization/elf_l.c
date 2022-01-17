#include "elf_l.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

unsigned long readcur(void *o, int n, struct ElfLib *lib) {
  fseek(lib->execfile, lib->execfileidx, SEEK_SET);
  return fread(o, sizeof(unsigned char), n, lib->execfile);
}

unsigned long readcurinc(void *o, int n, struct ElfLib *lib) {
  unsigned long r = readcur(o, n, lib);
  lib->execfileidx+=n;
  return r;
}

unsigned long readpadcur(int n, struct ElfLib* lib) {
  lib->execfileidx+=n;
  return 0;
}

struct ElfLib *read_elf(const unsigned char *exepath) {
  struct ElfLib *l = malloc(sizeof(struct ElfLib));
  l->execfilename = exepath;
  l->execfile = fopen(exepath, "rb");
  l->execfileidx = 0;

  l->elf_header = read_elf_header(l);

  l->nprogramheaders = bytes_conv(l->elf_header.phnum, 2);
  l->nsectionheaders = bytes_conv(l->elf_header.shentnum, 2);

  l->program_headers = malloc(l->nprogramheaders * sizeof(struct ProgramHeader));
  for (int i = 0, cur = bytes_conv(l->elf_header.phoff, 8); i < l->nprogramheaders; i++, cur+=bytes_conv(l->elf_header.phentsize, 2))
    l->program_headers[i] = read_program_headers(l, cur);
    
  l->section_headers = malloc(l->nsectionheaders * sizeof(struct SectionHeader));
  for (int i = 0, cur = bytes_conv(l->elf_header.shoff, 8); i < l->nsectionheaders; i++, cur+=bytes_conv(l->elf_header.shentsize, 2))
    l->section_headers[i] = read_section_headers(l, cur);

  return l;
}

struct ElfHeader read_elf_header(struct ElfLib *lib) {
  struct ElfHeader header;

  // read the magic numbers 0x00 - 0x04
  unsigned char magic[] = {0x7F, 'E', 'L', 'F'};
  while (lib->execfileidx < 4) {
    unsigned char cur;
    readcurinc(&cur, 1, lib);
    if (cur != magic[lib->execfileidx])
      ; // error: given binary is not an ELF
  }

  // read bit-format (x86 or x86_64)
  readcurinc(&header.bitformat, 1, lib);

  // read endianness
  readcurinc(&header.endianness, 1, lib);

  // read the ei_version (only valid value is 1)
  readcurinc(&header.eiversion, 1, lib);

  // read the ABI
  readcurinc(&header.osabi, 1, lib);

  // read the ABI version
  readcurinc(&header.abiver, 1, lib);

  // read all the padding bits (and do nothing with them)
  readpadcur(7, lib);

  // read the executable type
  readcurinc(header.exectype, 2, lib);

  // read the machine type
  readcurinc(header.machinetype, 2, lib);

  // read the version
  readcurinc(header.version, 4, lib);

    // read the entry point
    int en_ph_sh_siz = 8; // the size of the next 3 entries in bytes (8 bytes in x64)
    if (lib->elf_header.bitformat == 1)
        // x86, 4 bytes long
        en_ph_sh_siz = 4;

  readcurinc(header.entry, en_ph_sh_siz, lib);
  readcurinc(header.phoff, en_ph_sh_siz, lib);
  readcurinc(header.shoff, en_ph_sh_siz, lib);

  readcurinc(header.flags, 4, lib);
  readcurinc(header.ehsize, 2, lib);
  readcurinc(header.phentsize, 2, lib);
  readcurinc(header.phnum, 2, lib);
  readcurinc(header.shentsize, 2, lib);
  readcurinc(header.shentnum, 2, lib);
  readcurinc(header.shstrndx, 2, lib);

  readpadcur(0xa, lib); // last 10 bytes are ending padding

  return header;
}

struct ProgramHeader read_program_headers(struct ElfLib *lib, int offset) {
  lib->execfileidx = offset; //go to the offset position
  struct ProgramHeader header;

  readcurinc(header.type, 4, lib);

  int datsiz = lib->elf_header.bitformat == 1 ? 4 /*x86*/ : 8 /*x64*/;

  if (datsiz == 8)
    // on x64 the flags are stored here
    readcurinc(header.flags, 4, lib);
  // on x86 the flags are stored elsewhere

  readcurinc(header.offset, datsiz, lib);
  readcurinc(header.vaddr, datsiz, lib);
  readcurinc(header.paddr, datsiz, lib);
  readcurinc(header.filesz, datsiz, lib);
  readcurinc(header.memsz, datsiz, lib);

  if (datsiz == 4)
    // on x86 the flags are stored here
    readcurinc(header.flags, 4, lib);

  readcurinc(header.align, datsiz, lib);

  readpadcur(0x18, lib); // 0x18 bytes of padding

  return header;
}

struct SectionHeader read_section_headers(struct ElfLib *lib, int offset) {
  lib->execfileidx = offset;
  struct SectionHeader header;

  readcurinc(header.shname, 4, lib);
  readcurinc(header.shtype, 4, lib);

  int datsiz = lib->elf_header.bitformat == 1 ? 4 /*x86*/ : 8 /*x64*/;

  readcurinc(header.shflags, datsiz, lib);
  readcurinc(header.shaddr, datsiz, lib);
  readcurinc(header.shoffset, datsiz, lib);
  readcurinc(header.shsize, datsiz, lib);
  readcurinc(header.shlink, 4, lib);
  readcurinc(header.shinfo, 4, lib);
  readcurinc(header.shaddralign, datsiz, lib);
  readcurinc(header.shentsize, datsiz, lib);

  //read the padding at the end
  readpadcur(0x18, lib);

  return header;
}

void clean_elf(struct ElfLib *lib) {

    free(lib->program_headers);
    free(lib->section_headers);

    free(lib);
}