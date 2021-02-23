/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#include <dsml/score/debug.h>
#include <dsml/score/core.h>

#include <dsml/score/posix_file_iface.h>
#include <dsml/score/mem_file_iface.h>
#include <dsml/score/tools.h>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <string.h>

#define MAX_FILE_BUFF_SIZE 1024
#define FRAME_BUFF_SIZE 40
#define _MEM_FILE_SIDE 51

DSML_STATIC unsigned char tmp_buff[MAX_FILE_BUFF_SIZE];

#define _CHECK_ERRNO_SET() \
	do { \
		DSML_ASSERT(DSML_LAST_ERROR_GET(d), "errno should not be set!"); \
	} while(0)
#define _CHECK_ERRNO_N_SET() \
	do { \
		DSML_ASSERT(!DSML_LAST_ERROR_GET(d), "errno should not be set!"); \
	} while(0)

struct frame_buff_tag
{
	uint8 buff[FRAME_BUFF_SIZE];
	uint16 size;
	uint8 full;
};
DSML_STATIC struct frame_buff_tag frame_buff_tx0;
DSML_STATIC struct frame_buff_tag frame_buff_tx1;

DSML_STATIC uint8 fbuff_rx_0[FRAME_BUFF_SIZE];
DSML_STATIC uint8 fbuff_tx_0[FRAME_BUFF_SIZE];
DSML_STATIC uint8 fbuff_rx_1[FRAME_BUFF_SIZE];
DSML_STATIC uint8 fbuff_tx_1[FRAME_BUFF_SIZE];

DSML_STATIC reg send_01(DSML_CONTEXT_ARG, const struct dsml_frame_data_tag * const f)
{
	if(DSML_CONTEXT.id == 0)
	{
		//if(frame_buff_tx0.full) return DSML_RESULT_ERROR;
		memcpy(frame_buff_tx0.buff, f->buff, frame_buff_tx0.size = f->buff_bytes);
		frame_buff_tx0.full = 1;
		return DSML_RESULT_OK;
	}
	else
	{
		//if(frame_buff_tx1.full) return DSML_RESULT_ERROR;
		memcpy(frame_buff_tx1.buff, f->buff, frame_buff_tx1.size = f->buff_bytes);
		frame_buff_tx1.full = 1;
		return DSML_RESULT_OK;
	}
}

DSML_STATIC reg receive_01(DSML_CONTEXT_ARG, struct dsml_frame_data_tag * const f)
{
	if(DSML_CONTEXT.id == 0)
	{
		if(!frame_buff_tx1.full) return DSML_RESULT_ERROR;
		memcpy(f->buff, frame_buff_tx1.buff, frame_buff_tx1.size);
		f->buff_bytes = frame_buff_tx1.size;
		frame_buff_tx1.size = 0;
		frame_buff_tx1.full = 0;
		return DSML_RESULT_OK;
	}
	else
	{
		if(!frame_buff_tx0.full) return DSML_RESULT_ERROR;
		memcpy(f->buff, frame_buff_tx0.buff, frame_buff_tx0.size);
		f->buff_bytes = frame_buff_tx0.size;
		frame_buff_tx0.size = 0;
		frame_buff_tx0.full = 0;
		return DSML_RESULT_OK;
	}
}

DSML_STATIC reg load_01(DSML_CONTEXT_ARG)
{
	return DSML_RESULT_OK;
}

DSML_STATIC void unload_01(DSML_CONTEXT_ARG)
{

}

DSML_STATIC uint32 gettime_us_01(void)
{
	struct timeval tv;
	struct timezone tz;
	gettimeofday(&tv, &tz);
	return tv.tv_sec*10000000 + tv.tv_usec;
}

DSML_STATIC uint16 rand_01(void)
{
	return rand();
}

DSML_STATIC reg callback_01(DSML_CONTEXT_ARG, reg event)
{
	return DSML_RESULT_OK;
}

DSML_STATIC struct dsml_posix_file_userdata_tag file_0_userdata[2] =
{
	{ .filename = "node0/0.txt" },
	{ .filename = "node0/1.txt" }
};
DSML_STATIC unsigned char mem_buff_0[2][_MEM_FILE_SIDE];
DSML_STATIC struct dsml_mem_file_userdata_tag file_0_userdata_mem[2] =
{
	{
		.buff = &mem_buff_0[0][0],
		.size = _MEM_FILE_SIDE
	},
	{
		.buff = &mem_buff_0[1][0],
		.size = _MEM_FILE_SIDE
	},
};
DSML_STATIC struct dsml_file_tag file_0[4] =
{
	{
		.attributes = DSML_FILE_ATTRIBUTE_NONE
			| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_LOCAL_READ
			| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
			| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_REMOTE_READ
			| DSML_FILE_ATTRIBUTE_REMOTE_WRITE,
		.iface = &dsml_posix_file_iface,
		.userdata = &file_0_userdata[0]
	},
	{
		.attributes = DSML_FILE_ATTRIBUTE_NONE
			| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_LOCAL_READ
			| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
			| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_REMOTE_READ
			| DSML_FILE_ATTRIBUTE_REMOTE_WRITE,
		.iface = &dsml_posix_file_iface,
		.userdata = &file_0_userdata[1]
	},
	{
		.attributes = DSML_FILE_ATTRIBUTE_NONE
			| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_LOCAL_READ
			| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
			| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_REMOTE_READ
			| DSML_FILE_ATTRIBUTE_REMOTE_WRITE,
		.iface = &dsml_mem_file_iface,
		.userdata = &file_0_userdata_mem[0]
	},
	{
		.attributes = DSML_FILE_ATTRIBUTE_NONE
			| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_LOCAL_READ
			| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
			| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_REMOTE_READ
			| DSML_FILE_ATTRIBUTE_REMOTE_WRITE,
		.iface = &dsml_mem_file_iface,
		.userdata = &file_0_userdata_mem[1]
	}
};
DSML_STATIC struct dsml_file_tag * dir_0[5] =
{
	&file_0[0],
	&file_0[1],
	&file_0[2],
	&file_0[3],
	&file_0[3] /*NOTE: this for testing nack!!! */
};

DSML_STATIC struct dsml_posix_file_userdata_tag file_1_userdata[2] =
{
	{ .filename = "node1/0.txt" },
	{ .filename = "node1/1.txt" }
};
DSML_STATIC unsigned char mem_buff_1[2][_MEM_FILE_SIDE];
DSML_STATIC struct dsml_mem_file_userdata_tag file_1_userdata_mem[2] =
{
	{
		.buff = &mem_buff_1[0][0],
		.size = _MEM_FILE_SIDE
	},
	{
		.buff = &mem_buff_1[1][0],
		.size = _MEM_FILE_SIDE
	},
};
DSML_STATIC struct dsml_file_tag file_1[4] =
{
	{
		.attributes = DSML_FILE_ATTRIBUTE_NONE
			| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_LOCAL_READ
			| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
			| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_REMOTE_READ
			| DSML_FILE_ATTRIBUTE_REMOTE_WRITE,
		.iface = &dsml_posix_file_iface,
		.userdata = &file_1_userdata[0]
	},
	{
		.attributes = DSML_FILE_ATTRIBUTE_NONE
			| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_LOCAL_READ
			| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
			| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_REMOTE_READ
			| DSML_FILE_ATTRIBUTE_REMOTE_WRITE,
		.iface = &dsml_posix_file_iface,
		.userdata = &file_1_userdata[1]
	},
	{
		.attributes = DSML_FILE_ATTRIBUTE_NONE
			| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_LOCAL_READ
			| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
			| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_REMOTE_READ
			| DSML_FILE_ATTRIBUTE_REMOTE_WRITE,
		.iface = &dsml_mem_file_iface,
		.userdata = &file_1_userdata_mem[0]
	},
	{
		.attributes = DSML_FILE_ATTRIBUTE_NONE
			| DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_LOCAL_READ
			| DSML_FILE_ATTRIBUTE_LOCAL_WRITE
			| DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW
			| DSML_FILE_ATTRIBUTE_REMOTE_READ
			| DSML_FILE_ATTRIBUTE_REMOTE_WRITE,
		.iface = &dsml_mem_file_iface,
		.userdata = &file_1_userdata_mem[1]
	}
};
DSML_STATIC struct dsml_file_tag * dir_1[4] =
{
	&file_1[0],
	&file_1[1],
	&file_1[2],
	&file_1[3]
};

DSML_STATIC struct dsml_tag dsml_d[2] =
{
	{
		.id = 0,
		.load = &load_01,
		.unload = &unload_01,
		.send = &send_01,
		.receive = &receive_01,
		.checksum = &dsml_tools_checksum_default,
		.rand = &rand_01,
		.callback = &callback_01,
		.errcode = 0,
		.gettime_us = &gettime_us_01,
		.timeout_us = 10000,
		.state = 0,
		.status = 0,
		.master_priority = 0,
		.peer_master_priority = 0,
		.session = 0,
		.session_data = { 0 },
		.retry_max = 10,
		.dir_magic = 0x1234,
		.peer_dir_magic = 0,
		.dir = dir_0,
		.dir_size = sizeof(dir_0)/sizeof(dir_0[0]),
		.frame_tx = { .buff_size = FRAME_BUFF_SIZE, .buff = fbuff_tx_0 },
		.frame_rx = { .buff_size = FRAME_BUFF_SIZE, .buff = fbuff_rx_0 },
		.userdata = 0
	},
	{
		.id = 1,
		.load = &load_01,
		.unload = &unload_01,
		.send = &send_01,
		.receive = &receive_01,
		.checksum = &dsml_tools_checksum_default,
		.rand = &rand_01,
		.callback = &callback_01,
		.errcode = 0,
		.gettime_us = &gettime_us_01,
		.timeout_us = 10000,
		.state = 0,
		.status = 0,
		.master_priority = 0,
		.peer_master_priority = 0,
		.session = 0,
		.session_data = { 0 },
		.retry_max = 10,
		.dir_magic = 0x1234,
		.peer_dir_magic = 0,
		.dir = dir_1,
		.dir_size =  sizeof(dir_1)/sizeof(dir_1[0]),
		.frame_tx = { .buff_size = FRAME_BUFF_SIZE, .buff = fbuff_tx_1 },
		.frame_rx = { .buff_size = FRAME_BUFF_SIZE, .buff = fbuff_rx_1 },
		.userdata = 0
	}
};

#ifdef DSML_SINGLE_INSTANCE
struct dsml_tag DSML_SINGLE_INSTANCE;
#endif

DSML_STATIC void rand_files_data()
{
	int i, j, k, l, m;
	unsigned char c;
	struct dsml_tag * d;
	for(i = 0; i < sizeof(dsml_d)/sizeof(dsml_d[0]); i++)
	{
		d = &dsml_d[i];
		for(j = 0; j < d->dir_size; j++)
		{
			k = dsml_local_file_size(d, j);
			_CHECK_ERRNO_N_SET();
			/**/
			dsml_local_file_open(d, j, DSML_FILE_OFLAG_WRITE, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			/**/
			for(l = 0; l < k; l++)
			{
				c = (*d->rand)();
				dsml_local_file_write(d, j, &c, 1, l, DSML_FILE_PID_USER_FIRST);
				_CHECK_ERRNO_N_SET();
			}
			dsml_local_file_close(d, j, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
		}
	}
}
/**/
DSML_STATIC reg check_diff_files_data(uint16 file)
{
	reg res;
	int32 i, j, k;
	struct dsml_tag * d;
	unsigned char buff[2][MAX_FILE_BUFF_SIZE];

	res = DSML_RESULT_ERROR;

	if((file < dsml_d[0].dir_size) && (file < dsml_d[1].dir_size))
	{
		d = &dsml_d[0];
		i = dsml_local_file_size(d, file);
		_CHECK_ERRNO_N_SET();
		d = &dsml_d[1];
		j = dsml_local_file_size(d, file);
		_CHECK_ERRNO_N_SET();

		if(i == j)
		{
			d = &dsml_d[0];
			dsml_local_file_open(d, file, DSML_FILE_OFLAG_READ, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_local_file_read(d, file, &buff[0][0], i, 0, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_local_file_close(d, file, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			/**/
			d = &dsml_d[1];
			dsml_local_file_open(d, file, DSML_FILE_OFLAG_READ, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_local_file_read(d, file, &buff[1][0], i, 0, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_local_file_close(d, file, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();

			if(!memcmp(&buff[0][0], &buff[1][0], i))
			{ res = DSML_RESULT_OK; }
		}
	}

	return res;
}


void work(unsigned int cycles, unsigned int delay)
{
	while(cycles--)
	{
		usleep(delay);
		dsml_task(&dsml_d[0]);
		dsml_task(&dsml_d[1]);
		if((dsml_d[0].state == DSML_STATE_IDLE)
			&& (dsml_d[1].state == DSML_STATE_IDLE))
		{ break; }
	}
}

int main(int argn, char ** argv)
{
	int8 i8;
	int16 i16;
	int32 i32;
	int64 i64;
	unsigned char * src;
	reg res;
	int i, j, k, l, m;
	unsigned char buff[10];
	struct dsml_tag * d;

#define _CHECK_IO_RX_TX(n) \
	do { \
		i##n = 123; \
		src = tmp_buff; \
		dsml_tools_tx_uint##n((void*)&i##n, &src); \
		src = tmp_buff; \
		dsml_tools_rx_uint##n((void*)&i##n, &src); \
		DSML_ASSERT(i##n == 123, "upss!"); \
	} while(0)
	_CHECK_IO_RX_TX(8);
	_CHECK_IO_RX_TX(16);
	_CHECK_IO_RX_TX(32);
	_CHECK_IO_RX_TX(64);

	d = &dsml_d[0]; dsml_load(d);
	_CHECK_ERRNO_N_SET();
	d = &dsml_d[1]; dsml_load(d);
	_CHECK_ERRNO_N_SET();

#define _WORK_CYCLES 200
#define _CYCLE_DELAY_US 0

	/*force master priority reload */
	dsml_d[0].master_priority = dsml_d[1].master_priority;

#if 0
	d = &dsml_d[0];
	dsml_remote_write_file(d, 0);
	_CHECK_ERRNO_N_SET();
	work(_WORK_CYCLES, _CYCLE_DELAY_US);
	dsml_remote_write_file(d, 1);
	_CHECK_ERRNO_N_SET();
	work(_WORK_CYCLES, _CYCLE_DELAY_US);
	
	return 0;
#endif

	for(i = 0; i < sizeof(dsml_d)/sizeof(dsml_d[0]); i++)
	{
		d = &dsml_d[i];
		for(j = 0; j < d->dir_size; j++)
		{
			/* bad file */
			dsml_local_std_cmd(d, d->dir_size, DSML_STATE_CMD_SUB_TYPE_NONE, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_SET();

#ifndef DSML_MASTER_CMD_DISABLE
			/* bad file */
			dsml_remote_std_cmd(d, d->dir_size, DSML_STATE_CMD_SUB_TYPE_NONE);
			_CHECK_ERRNO_SET();

			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			/**/
			dsml_local_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_NONE, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_remote_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_NONE);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			dsml_local_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_RELOAD, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_remote_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_RELOAD);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			dsml_local_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_EXEC, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_remote_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_EXEC);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			dsml_local_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_CORRUPT, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_remote_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_CORRUPT);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			dsml_local_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_LOCK, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_remote_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_LOCK);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			dsml_local_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_UNLOCK, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_remote_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_UNLOCK);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			/**/
			for(k = DSML_STATE_CMD_TYPE_USER_FIRST; k <= DSML_STATE_CMD_TYPE_USER_FIRST+2; k++)
			{
				dsml_local_user_cmd(d, j, k, DSML_NULL, UINT16_C(0), DSML_FILE_PID_USER_FIRST);
				_CHECK_ERRNO_N_SET();
				dsml_remote_user_cmd(d, j, k, DSML_NULL, UINT16_C(0));
				_CHECK_ERRNO_N_SET();
				work(_WORK_CYCLES, _CYCLE_DELAY_US);
				dsml_local_user_cmd(d, j, k, buff, sizeof(buff), DSML_FILE_PID_USER_FIRST);
				_CHECK_ERRNO_N_SET();
				dsml_remote_user_cmd(d, j, k, buff, sizeof(buff));
				_CHECK_ERRNO_N_SET();
				work(_WORK_CYCLES, _CYCLE_DELAY_US);

				/* bad user data length */
				dsml_remote_user_cmd(d, j, k, tmp_buff, sizeof(tmp_buff));
				_CHECK_ERRNO_SET();
			}

			/* bad file */
			dsml_local_std_cmd(d, d->dir_size, DSML_STATE_CMD_SUB_TYPE_NONE, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_SET();
#endif /* #ifndef DSML_CMD_DISABLE */

#ifndef DSML_MASTER_READ_DISABLE
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			/**/
			rand_files_data();
			DSML_ASSERT(check_diff_files_data(j) == DSML_RESULT_ERROR, "upss!");
			dsml_remote_read_file(d, j);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			if((j < dsml_d[0].dir_size) && (j < dsml_d[1].dir_size))
			{ DSML_ASSERT(check_diff_files_data(j) == DSML_RESULT_OK, "upss!"); }
			else
			{ DSML_ASSERT(check_diff_files_data(j) == DSML_RESULT_ERROR, "upss!"); }
			/**/
			for(k = 0; k < 8; k++)
			{
				for(l = 0; l < 8; l++)
				{
					dsml_remote_read(d, j, k, l);
					_CHECK_ERRNO_N_SET();
					work(_WORK_CYCLES, _CYCLE_DELAY_US);
				}
			}
			/**/
			dsml_remote_read(d, j, dsml_local_file_size(d, j), 1);
			_CHECK_ERRNO_SET();
#endif /* #ifndef DSML_READ_DISABLE */

#ifndef DSML_MASTER_WRITE_DISABLE
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			/**/
			rand_files_data();
			DSML_ASSERT(check_diff_files_data(j) == DSML_RESULT_ERROR, "upss!");
			dsml_remote_write_file(d, j);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			if((j < dsml_d[0].dir_size) && (j < dsml_d[1].dir_size))
			{ DSML_ASSERT(check_diff_files_data(j) == DSML_RESULT_OK, "upss!"); }
			else
			{ DSML_ASSERT(check_diff_files_data(j) == DSML_RESULT_ERROR, "upss!"); }
			/**/
			for(k = 0; k < 8; k++)
			{
				for(l = 0; l < 8; l++)
				{
					dsml_remote_write(d, j, k, l);
					_CHECK_ERRNO_N_SET();
					work(_WORK_CYCLES, _CYCLE_DELAY_US);
				}
			}
			/**/
			dsml_remote_write(d, j, dsml_local_file_size(d, j), 1);
			_CHECK_ERRNO_SET();
#endif /* #ifndef DSML_WRITE_DISABLE */

#ifndef DSML_FILE_USER_ATTRIBUTES_DISABLE
			dsml_local_file_user_attributes(d, j);
			_CHECK_ERRNO_N_SET();
			/**/
			dsml_local_file_user_attributes_set(d, j, DSML_FILE_ATTRIBUTE_MASK_USER);
			_CHECK_ERRNO_N_SET();
			dsml_local_file_user_attributes_clear(d, j, DSML_FILE_ATTRIBUTE_MASK_USER);
			_CHECK_ERRNO_N_SET();
			/**/
			dsml_local_file_user_attributes_set(d, j, ~DSML_FILE_ATTRIBUTE_MASK_USER);
			_CHECK_ERRNO_SET();
			dsml_local_file_user_attributes_clear(d, j, ~DSML_FILE_ATTRIBUTE_MASK_USER);
			_CHECK_ERRNO_SET();
			/* bad file */
			dsml_local_file_user_attributes_set(d, d->dir_size, DSML_FILE_ATTRIBUTE_MASK_USER);
			_CHECK_ERRNO_SET();
			dsml_local_file_user_attributes_clear(d, d->dir_size, DSML_FILE_ATTRIBUTE_MASK_USER);
			_CHECK_ERRNO_SET();
#endif /* #ifndef DSML_FILE_USER_ATTRIBUTES_DISABLE */
		}

		dsml_callback(d, DSML_CALLBACK_USER_FIRST);
		_CHECK_ERRNO_N_SET();
		dsml_callback(d, DSML_CALLBACK_USER_LAST);
		_CHECK_ERRNO_N_SET();

		dsml_force_abort(d);
		work(_WORK_CYCLES, _CYCLE_DELAY_US);
	}

#ifndef DSML_MASTER_CMD_DISABLE
	file_0[0].attributes &= ~DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW;
	file_0[1].attributes &= ~DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW;
	/**/
	file_1[0].attributes &= ~DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW;
	file_1[1].attributes &= ~DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW;
	/**/
	for(i = 0; i < sizeof(dsml_d)/sizeof(dsml_d[0]); i++)
	{
		d = &dsml_d[i];
		for(j = 0; j < d->dir_size; j++)
		{
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			/**/
			dsml_remote_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_LOCK);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			/**/
			dsml_remote_std_cmd(d, j, DSML_STATE_CMD_SUB_TYPE_UNLOCK);
			_CHECK_ERRNO_N_SET();
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
		}
	}
	/**/
	file_0[0].attributes |= DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW;
	file_0[1].attributes |= DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW;
	/**/
	file_1[0].attributes |= DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW;
	file_1[1].attributes |= DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW;
#endif /* #ifndef DSML_CMD_DISABLE */

	for(i = 0; i < sizeof(dsml_d)/sizeof(dsml_d[0]); i++)
	{
		d = &dsml_d[i];
		for(j = 0; j < d->dir_size; j++)
		{
			work(_WORK_CYCLES, _CYCLE_DELAY_US);
			/**/
			dsml_local_file_open(d, j, DSML_FILE_OFLAG_READ, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_local_file_read(d, j, &k, 1, 0, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_local_file_close(d, j, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			/**/
			dsml_local_file_open(d, j, DSML_FILE_OFLAG_WRITE, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_local_file_write(d, j, &k, 1, 0, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			dsml_local_file_close(d, j, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_N_SET();
			/**/
			dsml_local_file_size(d, j);
			_CHECK_ERRNO_N_SET();
			/* bad file */
			dsml_local_file_open(d, d->dir_size, DSML_FILE_OFLAG_READ, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_SET();
			dsml_local_file_read(d, d->dir_size, &k, 1, 0, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_SET();
			dsml_local_file_close(d, d->dir_size, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_SET();
			/**/
			dsml_local_file_open(d, d->dir_size, DSML_FILE_OFLAG_WRITE, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_SET();
			dsml_local_file_write(d, d->dir_size, &k, 1, 0, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_SET();
			dsml_local_file_close(d, d->dir_size, DSML_FILE_PID_USER_FIRST);
			_CHECK_ERRNO_SET();
			/**/
			dsml_local_file_size(d, d->dir_size);
			_CHECK_ERRNO_SET();
		}
	}

	/* check connection lost */
	work(_WORK_CYCLES, _CYCLE_DELAY_US);
	k = _WORK_CYCLES;
	while(k--)
	{
		usleep(1000);
		dsml_task(&dsml_d[0]);
	}
	work(_WORK_CYCLES, _CYCLE_DELAY_US);

	/* check slave connection lost */
	dsml_remote_read_file(&dsml_d[0], 0);
	work(5, _CYCLE_DELAY_US);
	k = _WORK_CYCLES;
	while(k--)
	{
		usleep(10000);
		dsml_task(&dsml_d[0]);
		if(dsml_d[0].state == DSML_STATE_IDLE)
		{ break; }
	}
	/* check master connection lost */
	work(_WORK_CYCLES, _CYCLE_DELAY_US);
	dsml_remote_read_file(&dsml_d[0], 0);
	work(5, _CYCLE_DELAY_US);
	k = _WORK_CYCLES;
	while(k--)
	{
		usleep(0);
		dsml_task(&dsml_d[1]);
		if(dsml_d[1].state == DSML_STATE_IDLE)
		{ break; }
	}

	/* check arbitration */
	work(_WORK_CYCLES, _CYCLE_DELAY_US);
	rand_files_data();
	DSML_ASSERT(check_diff_files_data(0) == DSML_RESULT_ERROR, "upss!");
	d = &dsml_d[0]; dsml_remote_read_file(d, 0);
	_CHECK_ERRNO_N_SET();
	d = &dsml_d[1]; dsml_remote_read_file(d, 0);
	_CHECK_ERRNO_N_SET();
	work(_WORK_CYCLES, _CYCLE_DELAY_US);
	DSML_ASSERT(check_diff_files_data(0) == DSML_RESULT_OK, "upss!");
	/**/
	/*force master priority reload */
	dsml_d[0].master_priority = dsml_d[1].master_priority;
	/* check arbitration */
	rand_files_data();
	DSML_ASSERT(check_diff_files_data(0) == DSML_RESULT_ERROR, "upss!");
	d = &dsml_d[0]; dsml_remote_read_file(d, 0);
	_CHECK_ERRNO_N_SET();
	d = &dsml_d[1]; dsml_remote_read_file(d, 0);
	_CHECK_ERRNO_N_SET();
	work(_WORK_CYCLES, _CYCLE_DELAY_US);
	DSML_ASSERT(check_diff_files_data(0) == DSML_RESULT_ERROR, "should be error - both masters shall give-up!");

	/* NOTE: this will resize posix (FS) files */
	for(i = 0; i < sizeof(dsml_d)/sizeof(dsml_d[0]); i++)
	{
		d = &dsml_d[i];
		for(j = 0; j < d->dir_size; j++)
		{
			dsml_local_file_open(d, j, DSML_FILE_OFLAG_READ, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_read(d, j, tmp_buff, dsml_local_file_size(d, j), 1, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_close(d, j, DSML_FILE_PID_USER_FIRST);
			/**/
			dsml_local_file_open(d, j, DSML_FILE_OFLAG_READ, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_read(d, j, tmp_buff, 1, dsml_local_file_size(d, j), DSML_FILE_PID_USER_FIRST);
			dsml_local_file_close(d, j, DSML_FILE_PID_USER_FIRST);
			/**/
			dsml_local_file_open(d, j, DSML_FILE_OFLAG_WRITE, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_write(d, j, tmp_buff, dsml_local_file_size(d, j), 1, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_close(d, j, DSML_FILE_PID_USER_FIRST);
			/**/
			dsml_local_file_open(d, j, DSML_FILE_OFLAG_WRITE, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_write(d, j, tmp_buff, 1, dsml_local_file_size(d, j), DSML_FILE_PID_USER_FIRST);
			dsml_local_file_close(d, j, DSML_FILE_PID_USER_FIRST);
			/**/
			dsml_local_file_open(d, j, DSML_FILE_OFLAG_RW, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_read(d, j, tmp_buff, dsml_local_file_size(d, j), 1, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_write(d, j, tmp_buff, dsml_local_file_size(d, j), 1, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_read(d, j, tmp_buff, 1, dsml_local_file_size(d, j), DSML_FILE_PID_USER_FIRST);
			dsml_local_file_write(d, j, tmp_buff, 1, dsml_local_file_size(d, j), DSML_FILE_PID_USER_FIRST);
			dsml_local_file_close(d, j, DSML_FILE_PID_USER_FIRST);
			/**/
			dsml_local_file_open(d, j, ~DSML_FILE_OFLAG_MASK, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_read(d, j, tmp_buff, dsml_local_file_size(d, j), 1, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_write(d, j, tmp_buff, dsml_local_file_size(d, j), 1, DSML_FILE_PID_USER_FIRST);
			dsml_local_file_read(d, j, tmp_buff, 1, dsml_local_file_size(d, j), DSML_FILE_PID_USER_FIRST);
			dsml_local_file_write(d, j, tmp_buff, 1, dsml_local_file_size(d, j), DSML_FILE_PID_USER_FIRST);
			dsml_local_file_close(d, j, DSML_FILE_PID_USER_FIRST);
		}
	}
	/**/
	d = &dsml_d[0];
	((struct dsml_posix_file_userdata_tag*)d->dir[0]->userdata)->filename = "xxxyyyzzz";
	/**/
	dsml_local_file_open(d, 0, DSML_FILE_OFLAG_READ, DSML_FILE_PID_USER_FIRST);
	dsml_local_file_read(d, 0, tmp_buff, dsml_local_file_size(d, 0), 1, DSML_FILE_PID_USER_FIRST);
	dsml_local_file_close(d, 0, DSML_FILE_PID_USER_FIRST);
	/**/
	dsml_local_file_open(d, 0, DSML_FILE_OFLAG_READ, DSML_FILE_PID_USER_FIRST);
	dsml_local_file_read(d, 0, tmp_buff, 1, dsml_local_file_size(d, 0), DSML_FILE_PID_USER_FIRST);
	dsml_local_file_write(d, 0, tmp_buff, 1, dsml_local_file_size(d, 0), DSML_FILE_PID_USER_FIRST);
	dsml_local_file_close(d, 0, DSML_FILE_PID_USER_FIRST);

	d = &dsml_d[0]; dsml_unload(&dsml_d[0]);
	_CHECK_ERRNO_N_SET();
	d = &dsml_d[0]; dsml_unload(&dsml_d[1]);
	_CHECK_ERRNO_N_SET();

	return 0;
}

