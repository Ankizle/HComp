#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "load_elf.h"
#include "app.h"
#include "segment.h"
#include "../util.h"
#include "../elf_l.h"

void load_elf(struct App* app) {

    app->segments = malloc(sizeof(struct Segment) * app->lib->nprogramheaders);
    for (int i = 0; i < app->lib->nprogramheaders; i++) {
        struct Segment s;

        int start = bytes_conv(app->lib->program_headers[i].vaddr, 8);
        s.start = (app->mem_start) + start;

        int flags = bytes_conv(app->lib->program_headers[i].flags, 4);
        struct SegmentFlags flags_struct;
        //regarding flags, they have 3 bits we care about
        //lsb + 0 is if it is executable or not
        //lsb + 1 is if it is writeable or not
        //lsb + 2 is if it is readable or not
        flags_struct.execute = flags & 1;
        flags_struct.write = (flags >> 1) & 1;
        flags_struct.read = (flags >> 2) & 1;

        s.align = bytes_conv(app->lib->program_headers[i].align, 8);
        s.memsz = bytes_conv(app->lib->program_headers[i].memsz, 8);

        int elf_off = bytes_conv(app->lib->program_headers[i].offset, 8);
        int elf_siz = bytes_conv(app->lib->program_headers[i].filesz, 8);

        app->lib->execfileidx = elf_off;
        readcurinc(s.start, elf_siz, app->lib);

        app->segments[i] = s;
    }

    app->entry = bytes_conv(app->lib->elf_header.entry, 8);
}