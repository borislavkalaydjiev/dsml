/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifdef HAVE_CONFIG
#include <config.h>
#endif /* #ifdef HAVE_CONFIG */

#include <dsml/score/debug.h>
#include <dsml/score/posix_file_iface.h>

#ifndef __unix__
#error "Compiling on a none UNIX platform!"
#else /* #ifndef __unix__ */
#include <unistd.h>
#include <sys/stat.h> /* NOTE: posix optional include! */
#include <fcntl.h>
#include <errno.h>
#if !defined(_POSIX_VERSION) || !defined(_POSIX2_VERSION)
#error "Compiling on a none POSIX UNIX platform!"
#endif /* #if !defined(_POSIX_VERSION) || !defined(_POSIX2_VERSION) */
#endif /* #ifndef __unix__ */

DSML_STATIC int32 dsml_posix_file_open(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, uint16 oflag)
{
	int32 res;
	// TODO
	return res;
}

DSML_STATIC int32 dsml_posix_file_close(DSML_CONTEXT_ARG, struct dsml_file_tag * const f)
{
	int32 res;
	// TODO
	return res;
}

DSML_STATIC int32 dsml_posix_file_read(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, void * buff, uint32 nbyte, uint32 offset)
{
	int32 res;
	// TODO
	return res;
}

DSML_STATIC int32 dsml_posix_file_write(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, const void * buff, uint32 nbyte, uint32 offset)
{
	int32 res;
	// TODO
	return res;
}

DSML_STATIC int32 dsml_posix_file_size(DSML_CONTEXT_ARG, const struct dsml_file_tag * const f)
{
	int32 res;
	// TODO
	return res;
}

const struct dsml_file_iface_tag dsml_posix_file_iface =
{
	/* open */	&dsml_posix_file_open,
	/* close */	&dsml_posix_file_close,
	/* read */	&dsml_posix_file_read,
	/* write */	&dsml_posix_file_write,
	/* size */	&dsml_posix_file_size
};
