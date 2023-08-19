#ifndef __005SHAREDMEMORY_H_
#define __005SHAREDMEMORY_H_
#include <stddef.h>

struct SharedMemory;
typedef struct SharedMemory ShMemory;

ShMemory *InitSharedMemory(const char *path, int pro_id, size_t size);

void ClearSharedMemory(ShMemory *m);
void ReadFromSharedMemory(ShMemory *m, void *ptr, size_t size);
void WriteToSharedMemory(ShMemory *m, void *ptr, size_t size);

#endif