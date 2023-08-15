#ifndef __STDFIFO_H_
#define __STDFIFO_H_
#define PATH_SIZE 100
#include <stddef.h> //size_t

typedef enum STDMode
{
    ReadOnly,
    WriteOnly
} Mode;

struct StdFIFO;
typedef struct StdFIFO FIFO;


FIFO *InitFIFO(const char *path);
int OpenFIFO(FIFO *f, Mode mode);

void WriteToFIFO(FIFO *f, void *buff, size_t size);
void ReadFromFIFO(FIFO *f, void *buff, size_t size);

void ClearFIFO(FIFO *f);

void SetBlock(FIFO *f, int IsBlock);
#endif