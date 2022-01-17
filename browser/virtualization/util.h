#ifndef UTIL_H_
#define UTIL_H_

#include <sys/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

//convert multiple bytes as digits into one uint64
__uint64_t bytes_conv(unsigned char* v, int n);

//most values are pairs of bytes
//this function converts it to a single uint64
__uint64_t twobytes_conv(unsigned char v[2]);

#ifdef __cplusplus
}
#endif

#endif