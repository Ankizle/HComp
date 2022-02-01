#include "./sib.h"

struct SIB parseSIB(unsigned char b /*byte as param to parse into sib*/) {

    struct SIB s; //empty sib struct to store data in
    s.base = b & 0b00000111;
    s.index = b>>=3 & 0b00000111;
    s.scale = b>>=3 & 0b00000011;

    return s;
}