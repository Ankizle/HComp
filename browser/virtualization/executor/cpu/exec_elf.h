#ifndef EXEC_ELF_H_
#define EXEC_ELF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../app.h"

void exec_elf(struct App*);
long long next(struct App*, int);

#ifdef __cplusplus
}
#endif

#endif