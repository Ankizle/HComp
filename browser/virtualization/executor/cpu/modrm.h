#ifndef MODRM_H_
#define MODRM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../app.h"

struct ModRM {
    unsigned char mod: 2; //two bits
    unsigned char reg: 3; //three bits
    unsigned char rm: 3; //three bits

    long long* offset; //offset value (found in the following SIB byte)
    long long* regval; //register pointer
};

struct ModRM parseModRM(unsigned char);
void interpretModRM(struct ModRM*, struct App*, unsigned char);

#ifdef __cplusplus
}
#endif

#endif