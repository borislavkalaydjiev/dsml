/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifndef DSML_SCORE_POSIX_FILE_IFACE_H
#define DSML_SCORE_POSIX_FILE_IFACE_H

#include <dsml/score/core.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct dsml_posix_file_userdata_tag
{
	const char * filename;
};

extern const struct dsml_file_iface_tag dsml_posix_file_iface;

#define DSML_POSIX_FILE_SYMBOL_NAME(symbol, file_id, postfix) \
	dsml_posix_file_##symbol##_##file_id##postfix

#define DSML_POSIX_FILE_SYMBOL(symbol, file_id) \
	DSML_POSIX_FILE_SYMBOL_NAME(symbol, file_id, )

#define DSML_POSIX_FILE_DEFINE(symbol, file_id, filename, file_attributes) \
	DSML_STATIC struct dsml_posix_file_userdata_tag \
		DSML_POSIX_FILE_SYMBOL_NAME(symbol, file_id, _userdata) = \
	{ \
		/*.filename =*/ filename \
	}; \
	struct dsml_file_tag \
		DSML_POSIX_FILE_SYMBOL(symbol, file_id) = \
	{ \
		/*.id =*/ UINT16_C(file_id), \
		/*.pid =*/ DSML_FILE_PID_NONE, \
		/*.attributes =*/ (file_attributes), \
		/*.fd =*/ INT32_C(-1), \
		/*.iface =*/ &dsml_posix_file_iface, \
		/*.userdata =*/ &DSML_POSIX_FILE_SYMBOL_NAME(symbol, file_id, _userdata) \
	}

#define DSML_POSIX_FILE_DECLARE(symbol, file_id) \
	extern struct dsml_file_tag DSML_POSIX_FILE_SYMBOL(symbol, file_id)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSML_SCORE_POSIX_FILE_IFACE_H */
