#ifndef SEGMENT_H_
#define SEGMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

struct CPU_SegmentFlags {
    bool execute, write, read;
};

//represent a memory segment
struct CPU_Segment {
    unsigned char* start;
    struct CPU_SegmentFlags flags;
    int align;
    unsigned long long memsz;
};

#ifdef __cplusplus
}
#endif

#endif