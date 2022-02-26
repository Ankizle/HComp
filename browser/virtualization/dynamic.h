#ifndef DYNAMIC_H_
#define DYNAMIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <elf.h>
#include "app.h"

void interpret_dynamic_sect(struct App*, Elf64_Phdr);

#ifdef __cplusplus
}
#endif

#endif