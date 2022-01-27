#include "./modrm.h"

struct ModRM parseModRM(unsigned char b /*byte as param to parse into modrm*/) {

    struct ModRM m; //empty modrm struct to store data in
    m.rm = b & 0b00000111;
    m.reg = b>>=3 & 0b00000111;
    m.mod = b>>=3 & 0b00000011;

    return m;
}