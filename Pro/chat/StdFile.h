#ifndef __STDFILE_H_
#define __STDFILE_H_
#include "DoubleLinkList.h"
#include <stddef.h>

int IsFileExist(const char *FilePath);

char *LoardFromFile(const char *FilePath);

DLlist *GetLineFromFile(const char *FilePath);

void WriteToFile(const char *FilePath, void *ptr, size_t size);

void WriteLineToFile(const char *FilePath, DLlist *list);

void AppendToFile(const char *FilePath, void *ptr, size_t size);

void CopyFile(const char *SourcePath, const char *TargetPath);



#endif
