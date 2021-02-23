/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifndef DSML_SCORE_DEBUG_H
#define DSML_SCORE_DEBUG_H

#include <dsml/score/core.h>

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef DSML_DEBUG

#define DSML_DEBUG_EMPTY_CALL()	do { dsml_debug_empty_call(); } while(0)
#define DSML_DEBUG_PRINT(x)		do { dsml_debug_print(__LINE__, __FILE__, x); } while(0)
#define DSML_FUNCTION_BEGIN()	do { dsml_debug_function_begin(__LINE__, __FILE__, __FUNCTION__); } while(0)
#define DSML_FUNCTION_END()		do { dsml_debug_function_end(__LINE__, __FILE__, __FUNCTION__); } while(0)
#define DSML_ASSERT(x, y)		do { dsml_debug_assert(__LINE__, __FILE__, (x), "Assert failed (" #x "): " y); } while(0)
#define DSML_ASSERT_POINTER_CHECK(x) \
	do { \
		DSML_ASSERT(((void*)(x)) != DSML_NULL, "Pointer check failed (" #x ")"); \
	} while(0)
#define DSML_ASSERT_INIT_DONE(x) \
	do { \
		DSML_ASSERT((x)->status & DSML_STATUS_INIT, "instance not initialized!"); \
	} while(0)
#define DSML_DEBUG_DUMP(d)		do { dsml_debug_dump(__LINE__, __FILE__, (d)); } while(0)
#define DSML_DEBUG_FRAME_DUMP(d, f)	do { dsml_debug_frame_dump(__LINE__, __FILE__, (d), (f)); } while(0)

extern void dsml_debug_empty_call();
extern void dsml_debug_function_begin(int line, const char * file, const char * function);
extern void dsml_debug_function_end(int line, const char * file, const char * function);
extern void dsml_debug_assert(int line, const char * file, int expression, const char * str);
extern void dsml_debug_print(int line, const char * file, const char * str);
extern void dsml_debug_dump(int line, const char * file, DSML_CONTEXT_ARG);
extern void dsml_debug_frame_dump(int line, const char * file, DSML_CONTEXT_ARG, const struct dsml_frame_data_tag * const f);

#else /* #ifdef DSML_DEBUG */

#define DSML_DEBUG_EMPTY_CALL()			do { } while(0)
#define DSML_DEBUG_PRINT(x)				do { } while(0)
#define DSML_FUNCTION_BEGIN()			do { } while(0)
#define DSML_FUNCTION_END()				do { } while(0)
#define DSML_ASSERT(x, y)				do { } while(0)
#define DSML_ASSERT_POINTER_CHECK(x)	do { } while(0)
#define DSML_ASSERT_INIT_DONE(x)		do { } while(0)
#define DSML_DEBUG_DUMP(d)				do { } while(0)
#define DSML_DEBUG_FRAME_DUMP(d, f)		do { } while(0)

#endif /* #ifdef DSML_DEBUG */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSML_SCORE_DEBUG_H */
