#include <bits/types.h>
#include <stdlib.h>
#include "util.h"

//idx 0 is the lsb
__uint64_t bytes_conv(char* v, int n) {
    __uint64_t fin = 0;
    for (int i = 0; i < n; i++) {
        __uint64_t mult = 1;
        for (int d = 0; d < i; d++)
            mult+=0xff;
        fin+=((__uint64_t)v[i]) * mult;            
    }
    return fin;
}

__uint64_t twobytes_conv(char v[2]) {
    return bytes_conv(v, 2);
}