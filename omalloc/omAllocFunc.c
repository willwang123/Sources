/*******************************************************************
 *  File:    omAllocFunc.c
 *  Purpose: implementation of ANSI-C conforming malloc functions
 *           which are sure to be functions, which start with the om prefix,
 *           and end with the Func suffix.
 *  Author:  obachman@mathematik.uni-kl.de (Olaf Bachmann)
 *  Created: 11/99
 *******************************************************************/

#define malloc      omMallocFunc
#define calloc      omCallocFunc
#define free        omFreeFunc
#define freeSize    omFreeSizeFunc
#define realloc     omReallocFunc
#define reallocSize omReallocSizeFunc
#define memalign    omMemalignFunc
#define strdup      omStrdupFunc
#define valloc      omVallocFunc

#define OMALLOC_FUNC
#include <omalloc/omalloc.c>
