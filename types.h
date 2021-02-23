/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifndef DSML_SCORE_TYPES_H
#define DSML_SCORE_TYPES_H

/*TODO #include <sta/score/types.h>*/

#ifdef NULL
#define DSML_NULL NULL
#else /* #ifdef NULL */
#ifdef __cplusplus
#define DSML_NULL ((void*)0)
#else /* #ifdef __cplusplus */
#define DSML_NULL (0)
#endif /* #ifdef __cplusplus */
#endif /* #ifdef NULL */

#ifndef DSML_STATIC
//TODO #warning "DSML_STATIC is undefined ... switching to global symbol mode"
#define DSML_STATIC
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef HOST_IS_XC167
typedef signed int reg;
typedef unsigned int ureg;
typedef char int8;
typedef unsigned char uint8;
typedef short int int16;
typedef unsigned short int uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int int64;
typedef unsigned long long int uint64;
typedef float real32;
typedef double real64;

#define REG_C(x)	((reg)x)
#define UREG_C(x)	((ureg)x##u)
#define INT8_C(x)	((int8)x)
#define UINT8_C(x)	((uint8)x##u)
#define INT16_C(x)	((int16)x)
#define UINT16_C(x)	((uint16)x##u)
#define INT32_C(x)	((int32)x)
#define UINT32_C(x)	((uint32)x##u)
#define INT64_C(x)	((int64)x##ll)
#define UINT64_C(x)	((uint64)x##ull)
#define REAL32_C(x)	((real32)x)
#define REAL64_C(x)	((real64)x)

#else
typedef signed int reg;
typedef unsigned int ureg;
typedef char int8;
typedef unsigned char uint8;
typedef int int16;
typedef unsigned int uint16;
typedef long int32;
typedef unsigned long uint32;
/*typedef long long int int64;*/
/*typedef unsigned long long int uint64;*/
typedef float real32;
typedef double real64;

#define REG_C(x)	((reg)x)
#define UREG_C(x)	((ureg)x##u)
#define INT8_C(x)	((int8)x)
#define UINT8_C(x)	((uint8)x##u)
#define INT16_C(x)	((int16)x)
#define UINT16_C(x)	((uint16)x##u)
#define INT32_C(x)	((int32)x##l)
#define UINT32_C(x)	((uint32)x##ul)
/*#define INT64_C(x)	((int64)x##l)*/
/*#define UINT64_C(x)	((uint64)x##ul)*/
#define REAL32_C(x)	((real32)x)
#define REAL64_C(x)	((real64)x)
#endif



/*TODO global/cpu/asm system includes!!!*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSML_SCORE_TYPES_H */
