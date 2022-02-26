#include <dlfcn.h>
#include "app.h"
#include "load.h"
#include "run.h"

int main(int argc, char** argv, char** envp) {
    struct App app = load_elfmem(argv[1]);
    run_prog((void*)app.exec, (void*)app.lib.elf_header.e_entry);
}
