#ifndef LOAD_H_
#define LOAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "app.h"

struct App load_elfmem_file(FILE* file);
struct App load_elfmem(char* bin);

#ifdef __cplusplus
}
#endif

#endif