#include "./modrm.h"
#include "./sib.h"
#include "../app.h"
#include "../../util.h"
#include "./exec_elf.h"

struct ModRM parseModRM(unsigned char b /*byte as param to parse into modrm*/) {

    struct ModRM m; //empty modrm struct to store data in
    m.rm = b & 0b00000111;
    m.reg = b>>=3 & 0b00000111;
    m.mod = b>>=3 & 0b00000011;

    return m;
}

long long* getregister(unsigned char prefix, struct App* app, int enc, char idxobs, unsigned char mod) {
    switch (enc) {
        case 0b000: return app->registers.rax;
        case 0b001: return app->registers.rcx;
        case 0b010: return app->registers.rdx;
        case 0b011: return app->registers.rbx;
        case 0b100: 
            if (idxobs == 1) return 0;
            else return app->registers.rsp;
        case 0b101: 
            if (mod == 0b00 && idxobs == 0) return 0;
            else return app->registers.rbp;
        case 0b110: return app->registers.rsi;
        case 0b111: return app->registers.rdi;
    }
}

void interpretModRM(struct ModRM* m, struct App* app, unsigned char prefix) {
    m->offset = 0;

    if (m->mod != 0b11) {
        //rm is a memory location
        int disp = m->mod * 2;

        if (m->rm = 0b100) {
            char sib_byte = app->mem_start[++app->registers.rip];
            struct SIB s = parseSIB(sib_byte);

            int scale = 1 << s.scale;
            long long* idx = getregister(prefix, app, s.index, true, m->mod);
            long long* base = getregister(prefix, app, s.base, false, m->mod);
            if (base == 0)
                base = (long long*) ((app->mem_start) + next(app, 4));
            m->offset = base;
        } else
            if (m->mod == 0b00 && m->rm == 0b101) m->offset = (long long*) next(app, 4);
            else m->offset = getregister(prefix, app, m->rm, 3, m->mod) + next(app, disp);
    } else {
        //we are using two registers
        m->offset = getregister(prefix, app, m->rm, 3, m->mod);
    }

    m->regval = getregister(prefix, app, m->rm, 3, m->mod);
}