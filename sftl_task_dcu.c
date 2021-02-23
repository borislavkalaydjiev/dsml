/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifdef HAVE_CONFIG
#include <config.h>
#endif /* #ifdef HAVE_CONFIG */

#include <dsml/score/debug.h>
#include <dsml/score/core.h>

#define DSML_DCU_FRAME_BUFF_SIZE 40

struct dsml_dcu_frame_buff_tag
{
	reg full;
	uint8 buff[DSML_DCU_FRAME_BUFF_SIZE];
};

union dsml_dcu_frame_data_tag
{
	struct frame_buff_tag d;
	reg a[(sizeof(struct frame_buff_tag) + sizeof(reg) - 1)/sizeof(reg)];
};

DSML_STATIC volatile struct dsml_dcu_frame_data_tag dsml_dcu_frame_buff_tx;
DSML_STATIC volatile struct dsml_dcu_frame_data_tag dsml_dcu_frame_buff_rx;
DSML_STATIC struct dsml_dcu_frame_data_tag dsml_dcu_frame_buff_rx_lib;

DSML_STATIC reg dsml_dcu_send(DSML_CONTEXT_ARG, const struct dsml_frame_data_tag * const f)
{
	dsml_dcu_frame_buff_tx.d.buff[0]++;
	dsml_dcu_frame_buff_tx.d.buff[1] = (uint8)f->buff_bytes;
	dsml_dcu_frame_buff_tx.d.full = DSML_TRUE;
	return DSML_RESULT_OK;
}

DSML_STATIC reg dsml_dcu_receive(DSML_CONTEXT_ARG, struct dsml_frame_data_tag * const f)
{
	register reg i;
	register reg * src;
	register reg * dest;

	if(dsml_dcu_frame_buff_rx.d.full
		&& (dsml_dcu_frame_buff_rx.d.buff[0]
			!= dsml_dcu_frame_buff_rx_lib.d.buff[0]))
	{
		f->buff_bytes = (uint16)dsml_dcu_frame_buff_rx.d.buff[1];
		src = (reg*)dsml_dcu_frame_buff_rx.a;
		dest = (reg*)dsml_dcu_frame_buff_rx_lib.a;
		i = sizeof(union dsml_dcu_frame_data_tag)/sizeof(reg);
		while(i--) { *dest++ = *src++; }
		dsml_dcu_frame_buff_rx.d.full = DSML_FALSE;
		return DSML_RESULT_OK;
	} else { return DSML_RESULT_ERROR; }
}

DSML_STATIC reg dsml_dcu_load(DSML_CONTEXT_ARG)
{
	dsml_dcu_frame_buff_tx.d.full = DSML_FALSE;
	dsml_dcu_frame_buff_rx.d.full = DSML_FALSE;
	dsml_dcu_frame_buff_rx_lib.d.full = DSML_FALSE;
	dsml_dcu_frame_buff_tx.d.buff[0] = UINT8_C(0);
	dsml_dcu_frame_buff_rx.d.buff[0] = UINT8_C(0);
	dsml_dcu_frame_buff_rx_lib.d.buff[0] = UINT8_C(0);
	return DSML_RESULT_OK;
}

DSML_STATIC void dsml_dcu_unload(DSML_CONTEXT_ARG)
{
	/* nothing */
}

DSML_STATIC uint32 dsml_dcu_gettime_us(void)
{
	clk_time d_time;
	distr_clock_read_distr_clock(D_CLK, &d_time)
	return d_time.lsb;
}

DSML_STATIC uint16 dsml_dcu_rand(void)
{
	return (uint16)(&dsml_dcu_rand) * (uint16)dsml_dcu_gettime_us();
}

DSML_STATIC reg dsml_dcu_callback(DSML_CONTEXT_ARG, reg event)
{
	/*TODO*/
	return DSML_RESULT_OK;
}

DSML_MEM_FILE_DECLARE(dcu, 0x0000);
DSML_MEM_FILE_DECLARE(dcu, 0x0001);

DSML_MEM_FILE_DEFINE(dcu, 0x0000, 512, DSML_FILE_ATTRIBUTE_NONE
		| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
		| DSML_FILE_ATTRIBUTE_LOCAL_READ
		| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
		| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
		| DSML_FILE_ATTRIBUTE_REMOTE_READ
		| DSML_FILE_ATTRIBUTE_REMOTE_WRITE
	);
DSML_MEM_FILE_DEFINE(dcu, 0x0001, 512, DSML_FILE_ATTRIBUTE_NONE
		| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
		| DSML_FILE_ATTRIBUTE_LOCAL_READ
		| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
		| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
		| DSML_FILE_ATTRIBUTE_REMOTE_READ
		| DSML_FILE_ATTRIBUTE_REMOTE_WRITE
	);

DSML_STATIC struct dsml_file_tag * dsml_dcu_dir[2] =
{
	&DSML_MEM_FILE_SYMBOL(dcu, 0x0001),
	&DSML_MEM_FILE_SYMBOL(dcu, 0x0001)
};

DSML_STATIC struct dsml_tag dsml_data =
{
	.id = 0,
	.load = &dsml_dcu_load,
	.unload = &dsml_dcu_unload,
	.send = &dsml_dcu_send,
	.receive = &dsml_dcu_receive,
	.checksum = &dsml_tools_checksum_default,
	.rand = &dsml_dcu_rand,
	.callback = &dsml_dcu_callback,
#ifndef DSML_ERRNO_DISABLE
	.errno = 0,
#endif /* #ifndef DSML_ERRNO_DISABLE */
	.gettime_us = &dsml_dcu_gettime_us,
	.timeout_us = 1000,
	.state = 0,
	.status = 0,
	.master_priority = 0,
	.peer_master_priority = 0,
	.session = 0,
	.session_data = { 0 },
	.retry_max = 10,
	.dir_magic = 0x1234,
	.peer_dir_magic = 0,
	.dir = dsml_dcu_dir,
	.dir_size = sizeof(dsml_dcu_dir)/sizeof(dsml_dcu_dir[0]),
	.frame_tx = { .buff_size = DSML_DCU_FRAME_BUFF_SIZE-2, .buff = &dsml_dcu_frame_buff_tx.d.buff[2] },
	.frame_rx = { .buff_size = DSML_DCU_FRAME_BUFF_SIZE-2, .buff = &dsml_dcu_frame_buff_rx.d.buff[2] },
	.userdata = 0
};

void dsml_task_dcu()
{
	if(dsml_dcu_frame_buff_tx.d.full == DSML_FALSE)
	{
		dsml_task_dcu(&dsml_data);
	}
	else { /* nothing */ }
}

void dsml_dcu_init()
{
	if(dsml_load(&dsml_data) == DSML_RESULT_ERROR)
	{
		/* TODO: add error handling here!!! */
	}
	else { /* nothing */ }
}


















