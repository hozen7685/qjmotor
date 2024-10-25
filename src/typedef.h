#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#include <stdint.h>
#include <string.h>
#include "config.h"

#define RET_SUCCESS 0
#define RET_ERROR   -1
#ifndef FALSE
typedef enum {
	FALSE = 0,
	TRUE = 1
} bool_t;
#else
typedef int32_t bool_t;
#endif

typedef char cchar;
typedef char schar;
typedef unsigned char uchar;

typedef short sshort;
typedef unsigned short ushort;

typedef int sint;
typedef int slong;
typedef unsigned int ulong;

typedef int8_t ret_t;
#endif /* __TYPEDEF_H__ */
