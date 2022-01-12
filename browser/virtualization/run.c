#include <stdio.h>
#include "elf_l.h"

int RunApp(char* exepath) {
    struct ElfLib* l = read_elf(exepath);
}

int main() {
    RunApp("../test/a.out");
}