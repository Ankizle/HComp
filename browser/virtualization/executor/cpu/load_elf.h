#ifndef LOAD_ELF_H_
#define LOAD_ELD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../app.h"

//load an elf binary into virtual memory allocated in an App structure
void load_elf(struct App* app);

#ifdef __cplusplus
}
#endif

#endif