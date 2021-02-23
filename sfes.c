/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifdef HAVE_CONFIG
#include <config.h>
#endif /* #ifdef HAVE_CONFIG */

#include <dsml/score/debug.h>
#include <dsml/score/sfes.h>

DSML_STATIC reg dsml_sfes_callback(DSML_CONTEXT_ARG, reg event);

reg dsml_sfes_add(struct dsml_sfes_tag * const d, uint16 file, uint16 oflag)
{
	reg res;
	struct dsml_tag * dsml;

	DSML_ASSERT_POINTER_CHECK(d);
	DSML_ASSERT_POINTER_CHECK(d->dsml);

	dsml = d->dsml;

	res = DSML_RESULT_ERROR;

	if(file < dsml->dir_size)
	{
		if(oflag & DSML_FILE_OFLAG_READ)
		{
			DSML_ASSERT_POINTER_CHECK(d->read);
			d->read[file/(sizeof(reg)*8)] |=
				(REG_C(1) << (file%(sizeof(reg)*8)));
			DSML_ASSERT_POINTER_CHECK(dsml->gettime_us);
			DSML_ASSERT_POINTER_CHECK(d->update_time_us_read);
			d->update_time_us_read[file] = (*dsml->gettime_us)();
			res = DSML_RESULT_OK;
		} else { DSML_DEBUG_EMPTY_CALL(); }

		if(oflag & DSML_FILE_OFLAG_WRITE)
		{
			DSML_ASSERT_POINTER_CHECK(d->write);
			d->write[file/(sizeof(reg)*8)] |=
				(REG_C(1) << (file%(sizeof(reg)*8)));
			DSML_ASSERT_POINTER_CHECK(dsml->gettime_us);
			DSML_ASSERT_POINTER_CHECK(d->update_time_us_write);
			d->update_time_us_write[file] = (*dsml->gettime_us)();
			res = DSML_RESULT_OK;
		} else { DSML_DEBUG_EMPTY_CALL(); }

	} else { DSML_DEBUG_EMPTY_CALL(); }

	return res;
}

reg dsml_sfes_remove(struct dsml_sfes_tag * const d, uint16 file, uint16 oflag)
{
	reg res;
	struct dsml_tag * dsml;

	DSML_ASSERT_POINTER_CHECK(d);
	DSML_ASSERT_POINTER_CHECK(d->dsml);

	dsml = d->dsml;

	res = DSML_RESULT_ERROR;

	if(file < dsml->dir_size)
	{
		if(oflag & DSML_FILE_OFLAG_READ)
		{
			DSML_ASSERT_POINTER_CHECK(d->read);
			d->read[file/(sizeof(reg)*8)] &=
				~(REG_C(1) << (file%(sizeof(reg)*8)));
			res = DSML_RESULT_OK;
		} else { DSML_DEBUG_EMPTY_CALL(); }

		if(oflag & DSML_FILE_OFLAG_WRITE)
		{
			DSML_ASSERT_POINTER_CHECK(d->write);
			d->write[file/(sizeof(reg)*8)] &=
				~(REG_C(1) << (file%(sizeof(reg)*8)));
			res = DSML_RESULT_OK;
		} else { DSML_DEBUG_EMPTY_CALL(); }

	} else { DSML_DEBUG_EMPTY_CALL(); }

	return res;
}

DSML_STATIC reg dsml_sfes_callback(DSML_CONTEXT_ARG, reg event)
{
	reg res;
	struct dsml_sfes_tag * sfes;

	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);

	sfes = (struct dsml_sfes_tag*)DSML_CONTEXT.userdata;
	
	DSML_ASSERT_POINTER_CHECK(sfes);

	DSML_ASSERT_POINTER_CHECK(d->callback);
	res = (*d->callback)(&DSML_CONTEXT, event);

	switch(event)
	{
	case DSML_CALLBACK_READ_END:
		DSML_ASSERT_POINTER_CHECK(sfes->update_time_us_read);
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.gettime_us);
		sfes->update_time_us_read[sfes->current_file] =
			(*DSML_CONTEXT.gettime_us)();
		break;
	case DSML_CALLBACK_WRITE_END:
		DSML_ASSERT_POINTER_CHECK(sfes->update_time_us_write);
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.gettime_us);
		sfes->update_time_us_write[sfes->current_file] =
			(*DSML_CONTEXT.gettime_us)();
		break;
	case DSML_CALLBACK_IDLE:
		if(!(DSML_CONTEXT.status & DSML_STATUS_BUSY))
		{
			do
			{
				if(sfes->current_file_read == DSML_FALSE)
				{
					DSML_ASSERT_POINTER_CHECK(sfes->read);
					if(sfes->read[sfes->current_file/(sizeof(reg)*8)]
						& (~(REG_C(1) << (sfes->current_file%(sizeof(reg)*8)))))
					{
						sfes->current_file_read = DSML_TRUE;
						dsml_remote_read_file(&DSML_CONTEXT,
							sfes->current_file);
						break;
					} else { DSML_DEBUG_EMPTY_CALL(); }
				} else { DSML_DEBUG_EMPTY_CALL(); }

				DSML_ASSERT_POINTER_CHECK(sfes->write);
				if(sfes->write[sfes->current_file/(sizeof(reg)*8)]
					& (~(REG_C(1) << (sfes->current_file%(sizeof(reg)*8)))))
				{
					sfes->current_file_read = DSML_FALSE;
					dsml_remote_write_file(&DSML_CONTEXT,
						sfes->current_file);
					sfes->current_file++;
					if(sfes->current_file >= DSML_CONTEXT.dir_size)
					{ sfes->current_file = UINT16_C(0); }
					else { DSML_DEBUG_EMPTY_CALL(); }
					break;
				} else { DSML_DEBUG_EMPTY_CALL(); }

				sfes->current_file++;
				if(sfes->current_file >= DSML_CONTEXT.dir_size)
				{ sfes->current_file = UINT16_C(0); }

			} while(sfes->current_file != UINT16_C(0));
		} else { DSML_DEBUG_EMPTY_CALL(); }
		break;
	default:
		break;
	}

	return res;
}

void dsml_sfes_task(struct dsml_sfes_tag * const d)
{
	reg i;
	uint32 time_us;
	uint32 time_past_us;
	struct dsml_tag * dsml;

	DSML_ASSERT_POINTER_CHECK(d);
	DSML_ASSERT_POINTER_CHECK(d->dsml);

	dsml = d->dsml;

	DSML_ASSERT_POINTER_CHECK(dsml->gettime_us);
	time_us = (*dsml->gettime_us)();
	time_past_us = time_us - d->timeout_us;

	for(i = 0; i < dsml->dir_size; i++)
	{
		DSML_ASSERT_POINTER_CHECK(d->read);
		if((time_us - d->update_time_us_read[i]) >= d->timeout_us)
		{
			DSML_ASSERT_POINTER_CHECK(d->timeout);
			(*d->timeout)(d, (uint16)i);
			DSML_ASSERT_POINTER_CHECK(d->update_time_us_read);
			d->update_time_us_read[i] = time_past_us;
		} else { DSML_DEBUG_EMPTY_CALL(); }

		DSML_ASSERT_POINTER_CHECK(d->write);
		if((time_us - d->update_time_us_write[i]) >= d->timeout_us)
		{
			DSML_ASSERT_POINTER_CHECK(d->timeout);
			(*d->timeout)(d, (uint16)i);
			DSML_ASSERT_POINTER_CHECK(d->update_time_us_write);
			d->update_time_us_write[i] = time_past_us;
		} else { DSML_DEBUG_EMPTY_CALL(); }
	}
}

reg dsml_sfes_load(struct dsml_sfes_tag * const d)
{
	reg i;
	uint32 time_us;
	struct dsml_tag * dsml;

	DSML_ASSERT_POINTER_CHECK(d);
	DSML_ASSERT_POINTER_CHECK(d->dsml);

	dsml = d->dsml;

	d->current_file = UINT16_C(0);

	DSML_ASSERT_POINTER_CHECK(dsml->gettime_us);
	time_us = (*dsml->gettime_us)();

	i = (reg)dsml->dir_size;
	DSML_ASSERT_POINTER_CHECK(d->update_time_us_read);
	DSML_ASSERT_POINTER_CHECK(d->update_time_us_write);
	while(i--)
	{
		d->update_time_us_read[i] = time_us;
		d->update_time_us_write[i] = time_us;
	}

	d->callback = dsml->callback;
	dsml->callback = &dsml_sfes_callback;

	dsml->userdata = d;

	return DSML_RESULT_OK;
}

void dsml_sfes_unload(struct dsml_sfes_tag * const d)
{
	struct dsml_tag * dsml;

	DSML_ASSERT_POINTER_CHECK(d);
	DSML_ASSERT_POINTER_CHECK(d->dsml);

	dsml = d->dsml;

	dsml->callback = d->callback;
}

















