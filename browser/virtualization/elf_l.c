#include "elf_l.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

struct ElfLib read_elf(const char *exepath) {
  struct ElfLib l;
  l.execfile = fopen(exepath, "rb");

  Elf64_Ehdr ehdr;
  fread(&ehdr, sizeof(Elf64_Ehdr), 1, l.execfile);
  l.elf_header = ehdr;

  l.program_headers = malloc(sizeof(Elf64_Phdr) * ehdr.e_phnum);
  fseek(l.execfile, ehdr.e_phoff, SEEK_SET);
  fread(l.program_headers, sizeof(Elf64_Phdr), ehdr.e_phnum, l.execfile);

  l.section_headers = malloc(sizeof(Elf64_Shdr) * ehdr.e_shnum);
  fseek(l.execfile, ehdr.e_shoff, SEEK_SET);
  fread(l.section_headers, sizeof(Elf64_Phdr), ehdr.e_shnum, l.execfile);

  return l;
}