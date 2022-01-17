#ifndef SEGMENT_H_
#define SEGMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

struct SegmentFlags {
    bool execute, write, read;
};

//represent a memory segment
struct Segment {
    unsigned char* start;
    struct SegmentFlags flags;
    int align;
    unsigned long long memsz;
};

#ifdef __cplusplus
}
#endif

#endif