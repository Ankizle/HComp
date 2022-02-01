#ifndef SIB_H_
#define SIB_H_

#ifdef __cplusplus
extern "C" {
#endif

struct SIB {
    unsigned char scale: 2;
    unsigned char index: 3;
    unsigned char base: 3;
};

struct SIB parseSIB(unsigned char);

#ifdef __cplusplus
}
#endif

#endif