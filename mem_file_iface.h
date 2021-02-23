/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifndef DSML_SCORE_MEM_FILE_IFACE_H
#define DSML_SCORE_MEM_FILE_IFACE_H

#include <dsml/score/core.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct dsml_mem_file_userdata_tag
{
	void * buff;
	int32 size;
};

extern const struct dsml_file_iface_tag dsml_mem_file_iface;

#define DSML_MEM_FILE_SYMBOL_NAME(symbol, file_id, postfix) \
	dsml_mem_file_##symbol##_##file_id##postfix

#define DSML_MEM_FILE_SYMBOL(symbol, file_id) \
	DSML_MEM_FILE_SYMBOL_NAME(symbol, file_id, )

#define DSML_MEM_FILE_DEFINE(symbol, file_id, file_size, file_attributes) \
	DSML_STATIC uint8 dsml_mem_file_##symbol##_##file_id##_buff[(file_size)]; \
	DSML_STATIC struct dsml_mem_file_userdata_tag \
		DSML_MEM_FILE_SYMBOL_NAME(symbol, file_id, _userdata) = \
	{ \
		/*.buff =*/(void*)DSML_MEM_FILE_SYMBOL_NAME(symbol, file_id, _buff), \
		/*.size =*/ sizeof(DSML_MEM_FILE_SYMBOL_NAME(symbol, file_id, _buff)) \
	}; \
	struct dsml_file_tag \
		DSML_MEM_FILE_SYMBOL(symbol, file_id) = \
	{ \
		/*.id =*/ UINT16_C(file_id), \
		/*.pid =*/ DSML_FILE_PID_NONE, \
		/*.attributes =*/ (file_attributes), \
		/*.fd =*/ INT32_C(-1), \
		/*.iface =*/ &dsml_mem_file_iface, \
		/*.userdata =*/ &DSML_MEM_FILE_SYMBOL_NAME(symbol, file_id, _userdata) \
	}

#define DSML_MEM_FILE_DECLARE(symbol, file_id) \
	extern struct dsml_file_tag DSML_MEM_FILE_SYMBOL(symbol, file_id)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSML_SCORE_MEM_FILE_IFACE_H */
