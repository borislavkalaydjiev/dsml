/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifdef HAVE_CONFIG
#include <config.h>
#endif /* #ifdef HAVE_CONFIG */

#include <dsml/score/debug.h>
#include <dsml/score/mem_file_iface.h>

DSML_STATIC int32 dsml_mem_file_open(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, uint16 oflag)
{
	int32 res;
	struct dsml_mem_file_userdata_tag * userdata;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_mem_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->buff);

	f->fd = INT32_C(0);
	res = INT32_C(0);

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC int32 dsml_mem_file_close(DSML_CONTEXT_ARG, struct dsml_file_tag * const f)
{
	int32 res;
	struct dsml_mem_file_userdata_tag * userdata;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_mem_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->buff);

	f->fd = INT32_C(-1);
	res = INT32_C(0);

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC int32 dsml_mem_file_read(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, void * buff, uint32 nbyte, uint32 offset)
{
	int32 res;
	struct dsml_mem_file_userdata_tag * userdata;
	uint8 * src;
	uint8 * dest;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(buff);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_mem_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->buff);

	if(userdata->size <= (int32)offset)
	{ res = -(int32)DSML_ERRNO_EINVAL; }
	else
	{
		if(userdata->size < (int32)(offset + nbyte))
		{ nbyte = userdata->size - offset; }
		else { /* nothing */ }

		res = (int32)nbyte;
		dest = (uint8*)buff;
		src = (uint8*)userdata->buff;
		src += offset;
		while(nbyte--) { *dest++ = *src++; }
	}

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC int32 dsml_mem_file_write(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, const void * buff, uint32 nbyte, uint32 offset)
{
	int32 res;
	struct dsml_mem_file_userdata_tag * userdata;
	uint8 * src;
	uint8 * dest;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(buff);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_mem_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->buff);

	if(userdata->size <= (int32)offset)
	{ res = -(int32)DSML_ERRNO_EINVAL; }
	else
	{
		if(userdata->size < (int32)(offset + nbyte))
		{ nbyte = userdata->size - offset; }
		else { /* nothing */ }

		res = (int32)nbyte;
		dest = (uint8*)userdata->buff;
		dest += offset;
		src = (uint8*)buff;
		while(nbyte--) { *dest++ = *src++; }
	}

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC int32 dsml_mem_file_size(DSML_CONTEXT_ARG, const struct dsml_file_tag * const f)
{
	int32 res;
	struct dsml_mem_file_userdata_tag * userdata;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_POINTER_CHECK(f);
	DSML_ASSERT_POINTER_CHECK(f->userdata);

	userdata = (struct dsml_mem_file_userdata_tag*)f->userdata;

	DSML_ASSERT_POINTER_CHECK(userdata->buff);

	res = userdata->size;

	DSML_FUNCTION_END();
	return res;
}

const struct dsml_file_iface_tag dsml_mem_file_iface =
{
	/* open */	&dsml_mem_file_open,
	/* close */	&dsml_mem_file_close,
	/* read */	&dsml_mem_file_read,
	/* write */	&dsml_mem_file_write,
	/* size */	&dsml_mem_file_size
};
