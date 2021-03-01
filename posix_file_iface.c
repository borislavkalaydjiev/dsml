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
	int _fd;
	int _oflag;
	struct dsml_posix_file_userdata_tag * userdata;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_posix_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->filename);

	oflag &= DSML_FILE_OFLAG_MASK;
	res = INT32_C(0);

	if(oflag == DSML_FILE_OFLAG_READ)		{ _oflag = O_RDONLY; }
	else if(oflag == DSML_FILE_OFLAG_WRITE)	{ _oflag = O_WRONLY; }
	else if(oflag == DSML_FILE_OFLAG_RW)	{ _oflag = O_RDWR; }
	else									{ res = -(int32)EINVAL; }

	if(res == INT32_C(0))
	{
		_fd = open(userdata->filename, _oflag);
		if(_fd >= 0)	{ res = (f->fd = (int32)_fd); }
		else			{ res = -(int32)errno; }
	} else { /* nothing */ }

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC int32 dsml_posix_file_close(DSML_CONTEXT_ARG, struct dsml_file_tag * const f)
{
	int32 res;
	struct dsml_posix_file_userdata_tag * userdata;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_posix_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->filename);

	if(!close(f->fd))	{ res = INT32_C(0); f->fd = INT32_C(-1); }
	else				{ res = -(int32)errno; }

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC int32 dsml_posix_file_read(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, void * buff, uint32 nbyte, uint32 offset)
{
	int32 res;
	off_t _off;
	ssize_t _ssize;
	struct dsml_posix_file_userdata_tag * userdata;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(buff);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_posix_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->filename);

	_off = lseek((int)f->fd, (off_t)offset, SEEK_SET);
	if(_off == (off_t)-1)
	{ res = -(int32)errno; }
	else
	{
		_ssize = read((int)f->fd, buff, (size_t)nbyte);
		if(_ssize == (ssize_t)-1)	{ res = -(int32)errno; }
		else						{ res = (int32)_ssize; }
	}

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC int32 dsml_posix_file_write(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, const void * buff, uint32 nbyte, uint32 offset)
{
	int32 res;
	off_t _off;
	ssize_t _ssize;
	struct dsml_posix_file_userdata_tag * userdata;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(buff);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_posix_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->filename);

	_off = lseek((int)f->fd, (off_t)offset, SEEK_SET);
	if(_off == (off_t)-1)
	{ res = -(int32)errno; }
	else
	{
		_ssize = write((int)f->fd, buff, (size_t)nbyte);
		if(_ssize == (ssize_t)-1)	{ res = -(int32)errno; }
		else						{ res = (int32)_ssize; }
	}

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC int32 dsml_posix_file_size(DSML_CONTEXT_ARG, const struct dsml_file_tag * const f)
{
	int32 res;
	struct stat _stat;
	struct dsml_posix_file_userdata_tag * userdata;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_posix_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->filename);

	res = stat((const char*)userdata->filename, &_stat);
	if(res == INT32_C(-1))	{ res = -(int32)errno; }
	else					{ res = (int32)_stat.st_size; }

	DSML_FUNCTION_END();
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
