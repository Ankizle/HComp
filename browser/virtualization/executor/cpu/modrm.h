#ifndef MODRM_H_
#define MODRM_H_

#ifdef __cplusplus
extern "C" {
#endif

struct ModRM {
    unsigned char mod: 2; //two bits
    unsigned char reg: 3; //three bits
    unsigned char rm: 3; //three bits
};

struct ModRM parseModRM(unsigned char);

#ifdef __cplusplus
}
#endif

#endif