//
// Created by hujianzhe
//

#ifndef	UTIL_C_SYSLIB_MISC_H
#define UTIL_C_SYSLIB_MISC_H

#include "../platform_define.h"

#if defined(_WIN32) || defined(_WIN64)
	#include <malloc.h>
	#ifndef alloca
		#define alloca		_alloca
	#endif
#else
	#if	__linux__
		#include <alloca.h>
		#include <malloc.h>
	#endif
#endif
#include <stdlib.h>

#define	alignedAlloca(nbytes, alignment)\
((void*)(((size_t)alloca(nbytes + alignment)) + (alignment - 1) & ~(((size_t)alignment) - 1)))

#ifdef	__cplusplus
extern "C" {
#endif

__declspec_dll void* alignMalloc(size_t nbytes, size_t alignment);
__declspec_dll void alignFree(const void* p);

__declspec_dll Iobuf_t* iobufPop(Iobuf_t* iov, size_t n);
__declspec_dll unsigned int iobufShardCopy(const Iobuf_t* iov, unsigned int iovcnt, unsigned int* iov_i, unsigned int* iov_off, void* buf, unsigned int n);

#ifdef	__cplusplus
}
#endif

#endif
