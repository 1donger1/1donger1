#ifndef __STDFILE_H_
#define __STDFILE_H_
#include "DoubleLinkList.h"
char *LoardFromFile(const char *FilePath);

DLlist *GetLineFromFile(const char *FilePath);

#endif
