#include <elf.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h> 
#include <string.h>
#include "app.h"
#include "elf_l.h"
#include "load.h"

Elf64_Dyn get_typ(struct App* app, Elf64_Addr typ) {
    for (int i = 0;; i++)
        if (app->dyn[i].d_tag == typ)
            return app->dyn[i];
}

unsigned char* reloc_lookup(struct App* app, char* symnam) {
    for (int i = 0; i < app->dynapps_amt; i++) {
        for (int j = 0; j < app->dynapps[i].dynsyms_amt; j++) {
            Elf64_Sym sym = app->dynapps[i].dynsyms[j];
            if (strcmp(symnam, app->dynapps[i].dynstrtab + sym.st_name) == 0) {
                return app->dynapps[i].exec + sym.st_value;
            }
        }
    }
    return NULL;
}

//  https://docs.oracle.com/cd/E19683-01/816-1386/6m7qcoblk/index.html#chapter6-42444
void interpret_dynamic_sect(struct App* app, Elf64_Phdr phdr) {
    unsigned char* exec = app->exec;

    Elf64_Dyn* dyn = malloc(phdr.p_memsz * sizeof(unsigned char));
    fread(dyn, sizeof(unsigned char), phdr.p_memsz, app->lib.execfile);
    app->dyn = dyn;

    //strtab is mandatory for all binaries so we interpret it here
    Elf64_Addr strtab_addr = get_typ(app, DT_STRTAB).d_un.d_ptr;
    Elf64_Xword strsz = get_typ(app, DT_STRSZ).d_un.d_val;

    char* strtab = malloc(sizeof(char) * strsz);
    fseek(app->lib.execfile, strtab_addr, SEEK_SET);
    fread(strtab, sizeof(unsigned char), strsz, app->lib.execfile);
    app->dynstrtab = strtab;

    Elf64_Sym** shared_syms = NULL;
    size_t* shared_syms_sizes = NULL;

    //loop until we reach a null entry
    for (;dyn->d_tag != DT_NULL; ++dyn) {
        switch (dyn->d_tag) {
            case DT_NEEDED:
                char* symnam = strtab + dyn->d_un.d_val; //get the symbol name
                FILE* symfile = fopen(symnam, "rb"); //open the symbol's file

                const char* paths[] = {"/usr/lib"};

                for (int i = 0; symfile == NULL && i < (sizeof(paths) / sizeof(char*)); i++) {
                    chdir(paths[i]);
                    symfile = fopen(symnam, "rb"); //open the symbol's file
                }

                if (symfile == NULL) {
                    //our system simply cannot load the shared library being requested
                }

                struct App sharedapp = load_elfmem_file(symfile);
                printf("%llx\n", sharedapp.exec);
                app->dynapps = realloc(app->dynapps, ++app->dynapps_amt * sizeof(struct App));
                shared_syms = realloc(shared_syms, app->dynapps_amt * sizeof(Elf64_Sym*));
                shared_syms_sizes = realloc(shared_syms_sizes, app->dynapps_amt * sizeof(size_t));

                app->dynapps[app->dynapps_amt - 1] = sharedapp;
                shared_syms[app->dynapps_amt - 1] = sharedapp.dynsyms;
                shared_syms_sizes[app->dynapps_amt - 1] = sharedapp.dynsyms_amt;

                break;
            case DT_SYMTAB:

                Elf64_Xword syment = get_typ(app, DT_SYMENT).d_un.d_val;

                //might be a bit hacky, but we're using the section header to tell the size of the symbol table
                Elf64_Xword dynsym_siz;

                for (int i = 0; i < app->lib.elf_header.e_shnum; i++) {
                    Elf64_Shdr shdr = app->lib.section_headers[i];
                    if (shdr.sh_type == SHT_DYNSYM) dynsym_siz = shdr.sh_size;
                }

                fseek(app->lib.execfile, dyn->d_un.d_ptr, SEEK_SET);
                Elf64_Sym* dynsyms = malloc(sizeof(unsigned char) * dynsym_siz);
                fread(dynsyms, sizeof(unsigned char), dynsym_siz, app->lib.execfile);

                size_t dynsyms_amt = dynsym_siz / syment;

                app->dynsyms = dynsyms;
                app->dynsyms_amt = dynsyms_amt;

                app->dynapps = realloc(app->dynapps, ++app->dynapps_amt * sizeof(struct App));
                shared_syms = realloc(shared_syms, app->dynapps_amt * sizeof(Elf64_Sym*));
                shared_syms_sizes = realloc(shared_syms_sizes, app->dynapps_amt * sizeof(size_t));


                app->dynapps[app->dynapps_amt - 1] = *app;
                shared_syms[app->dynapps_amt - 1] = dynsyms;
                shared_syms_sizes[app->dynapps_amt - 1] = dynsyms_amt;

                break;
            case DT_RELA:
                Elf64_Dyn rela_siz = get_typ(app, DT_RELASZ);
                Elf64_Dyn rela_ent = get_typ(app, DT_RELAENT);

                int nument = rela_siz.d_un.d_val / rela_ent.d_un.d_val;
                Elf64_Rela* entries = malloc(sizeof(Elf64_Rela) * nument);

                for (int i = 0; i < nument; i++) {
                    fseek(app->lib.execfile, dyn->d_un.d_ptr + i * rela_ent.d_un.d_val, SEEK_SET);
                    fread(&entries[i], sizeof(unsigned char), rela_ent.d_un.d_val, app->lib.execfile);

                    Elf64_Xword dynsym_idx = ELF64_R_SYM(entries[i].r_info); //index in the dynsym table of the reloc entry
                    char* symnam = strtab + app->dynsyms[dynsym_idx].st_name;
                    if (strlen(symnam) == 0) continue;
                    Elf64_Addr symaddr = (Elf64_Addr) reloc_lookup(app, symnam);

                    restart_worked:
                    for (int m = 0; m < 8; m++, symaddr>>=8)
                        exec[entries[i].r_offset + m] = symaddr & 0xff;
                }

                break;
       }
    }
}