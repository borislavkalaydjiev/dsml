/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifdef HAVE_CONFIG
#include <config.h>
#endif /* #ifdef HAVE_CONFIG */

#include <dsml/score/debug.h>
#include <dsml/score/core.h>
#include <dsml/score/tools.h>

#undef DSML_SEMICOLON_
#define DSML_SEMICOLON_

#undef DSML_FRAME_ITEM_TOOL
#define DSML_FRAME_ITEM_TOOL(x, rx_tx, src, type, name) \
	((uint16)sizeof(type))+

#define DSML_FRAME_SIZE_TOOL(x) \
	(DSML_FRAME_LIST_ITEM_##x(0, 0) UINT16_C(0))

/* NOTE: workaround to avoid memory allocation */
#define DSML_FRAME_SIZE_ACCESS(x) \
DSML_STATIC uint16 DSML_FRAME_SIZE_##x(void); \
DSML_STATIC uint16 DSML_FRAME_SIZE_##x(void) { return DSML_FRAME_SIZE_TOOL(x); }
/**/
DSML_FRAME_SIZE_ACCESS(idle)
DSML_FRAME_SIZE_ACCESS(cmd)
DSML_FRAME_SIZE_ACCESS(cmd_end)
DSML_FRAME_SIZE_ACCESS(file_init)
DSML_FRAME_SIZE_ACCESS(file_data)
DSML_FRAME_SIZE_ACCESS(file_end)
DSML_FRAME_SIZE_ACCESS(ack)
DSML_FRAME_SIZE_ACCESS(nack)
DSML_FRAME_SIZE_ACCESS(abort)
DSML_FRAME_SIZE_ACCESS(header)
/**/
#define DSML_FRAME_SIZE(x)	(DSML_FRAME_SIZE_##x())
/**/
#ifdef DSML_FRAME_BUFF_SIZE_MIN
#define dsml_frame_buff_size_min() (DSML_FRAME_BUFF_SIZE_MIN)
#else /* #ifdef DSML_FRAME_BUFF_SIZE_MIN */
DSML_STATIC uint16 dsml_frame_buff_size_min(void);
DSML_STATIC uint16 dsml_frame_buff_size_min(void)
{
	register uint16 n;
	DSML_FUNCTION_BEGIN();
	n = UINT16_C(0);
	{
		if(n <	DSML_FRAME_SIZE_TOOL(idle		))
		{ n =	DSML_FRAME_SIZE_TOOL(idle		); }
		else { DSML_DEBUG_EMPTY_CALL(); }
		if(n <	DSML_FRAME_SIZE_TOOL(cmd		))
		{ n =	DSML_FRAME_SIZE_TOOL(cmd		); }
		else { DSML_DEBUG_EMPTY_CALL(); }
		if(n <	DSML_FRAME_SIZE_TOOL(cmd_end	))
		{ n =	DSML_FRAME_SIZE_TOOL(cmd_end	); }
		else { DSML_DEBUG_EMPTY_CALL(); }
		if(n <	DSML_FRAME_SIZE_TOOL(file_init	))
		{ n =	DSML_FRAME_SIZE_TOOL(file_init	); }
		else { DSML_DEBUG_EMPTY_CALL(); }
		if(n <	DSML_FRAME_SIZE_TOOL(file_data	))
		{ n =	DSML_FRAME_SIZE_TOOL(file_data	); }
		else { DSML_DEBUG_EMPTY_CALL(); }
		if(n <	DSML_FRAME_SIZE_TOOL(file_end	))
		{ n =	DSML_FRAME_SIZE_TOOL(file_end	); }
		else { DSML_DEBUG_EMPTY_CALL(); }
		if(n <	DSML_FRAME_SIZE_TOOL(ack		))
		{ n =	DSML_FRAME_SIZE_TOOL(ack		); }
		else { DSML_DEBUG_EMPTY_CALL(); }
		if(n <	DSML_FRAME_SIZE_TOOL(nack		))
		{ n =	DSML_FRAME_SIZE_TOOL(nack		); }
		else { DSML_DEBUG_EMPTY_CALL(); }
		if(n <	DSML_FRAME_SIZE_TOOL(abort		))
		{ n =	DSML_FRAME_SIZE_TOOL(abort		); }
		else { DSML_DEBUG_EMPTY_CALL(); }
	}
	n += DSML_FRAME_SIZE(header);
	n++; /* NOTE: theoretically we need minimum 1 data byte! */
	DSML_FUNCTION_END();
	return n;
}
#endif /* #ifdef DSML_FRAME_BUFF_SIZE_MIN */
/**/
#undef DSML_SEMICOLON_
#define DSML_SEMICOLON_ ;
/**/
#undef DSML_FRAME_ITEM_TOOL
#ifndef HOST_IS_XC167
#define DSML_FRAME_ITEM_TOOL(x, rx_tx, src, type, name) \
	do { \
		if(sizeof(type) == sizeof(uint8)) \
		{ dsml_tools_##rx_tx##_uint8( \
			(void*)&((DSML_CONTEXT.frame_##rx_tx.x).name), &src); } \
		else if(sizeof(type) == sizeof(uint16)) \
		{ dsml_tools_##rx_tx##_uint16( \
			(void*)&((DSML_CONTEXT.frame_##rx_tx.x).name), &src); } \
		else if(sizeof(type) == sizeof(uint32)) \
		{ dsml_tools_##rx_tx##_uint32( \
			(void*)&((DSML_CONTEXT.frame_##rx_tx.x).name), &src); } \
		else if(sizeof(type) == sizeof(uint64)) \
		{ dsml_tools_##rx_tx##_uint64( \
			(void*)&((DSML_CONTEXT.frame_##rx_tx.x).name), &src); } \
		else \
		{ DSML_ASSERT(DSML_FALSE, "bad frame item type"); } \
	} while(0)
#else /* #ifndef HOST_IS_XC167 */
#define DSML_FRAME_ITEM_TOOL(x, rx_tx, src, type, name) \
	do { \
		if(sizeof(type) == sizeof(uint8)) \
		{ dsml_tools_##rx_tx##_uint8( \
			(void*)&((DSML_CONTEXT.frame_##rx_tx.x).name), &src); } \
		else if(sizeof(type) == sizeof(uint16)) \
		{ dsml_tools_##rx_tx##_uint16( \
			(void*)&((DSML_CONTEXT.frame_##rx_tx.x).name), &src); } \
		else if(sizeof(type) == sizeof(uint32)) \
		{ dsml_tools_##rx_tx##_uint32( \
			(void*)&((DSML_CONTEXT.frame_##rx_tx.x).name), &src); } \
		/* \
		else if(sizeof(type) == sizeof(uint64)) \
		{ dsml_tools_##rx_tx##_uint64( \
			(void*)&((DSML_CONTEXT.frame_##rx_tx.x).name), &src); } \
		*/ \
		else \
		{ DSML_ASSERT(DSML_FALSE, "bad frame item type"); } \
	} while(0)
#endif /* #ifndef HOST_IS_XC167 */

DSML_STATIC reg dsml_frame_rx_decode(DSML_CONTEXT_ARG);
DSML_STATIC reg dsml_frame_tx_code(DSML_CONTEXT_ARG);
DSML_STATIC reg dsml_send(DSML_CONTEXT_ARG);
DSML_STATIC reg dsml_send_idle(DSML_CONTEXT_ARG);
DSML_STATIC reg dsml_send_abort(DSML_CONTEXT_ARG, int32 return_code);
#ifndef DSML_SLAVE_DISABLE
DSML_STATIC reg dsml_ack_nack_call(DSML_CONTEXT_ARG,
	void * buff, uint16 user_bytes, int32 return_code);
DSML_STATIC reg dsml_send_ack(DSML_CONTEXT_ARG,
	void * buff, uint16 user_bytes, int32 return_code);
DSML_STATIC reg dsml_send_nack(DSML_CONTEXT_ARG, int32 return_code);
#endif /* #ifndef DSML_SLAVE_DISABLE */
DSML_STATIC reg dsml_close_session(DSML_CONTEXT_ARG);
#ifndef DSML_MASTER_DISABLE
DSML_STATIC void dsml_master_task(DSML_CONTEXT_ARG);
#endif /* #ifndef DSML_MASTER_DISABLE */
#ifndef DSML_SLAVE_DISABLE
DSML_STATIC void dsml_slave_task(DSML_CONTEXT_ARG);
#endif /* #ifndef DSML_SLAVE_DISABLE */
DSML_STATIC void dsml_idle_task(DSML_CONTEXT_ARG);

DSML_STATIC reg dsml_frame_rx_decode(DSML_CONTEXT_ARG)
{
	uint16 checksum;
	uint8 * src;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	DSML_CONTEXT.frame_rx.is_valid = DSML_FALSE;

	if(DSML_CONTEXT.frame_rx.buff_bytes > UINT16_C(0))
	{
		DSML_DEBUG_PRINT("rx frame not empty");

		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.gettime_us);
		DSML_CONTEXT.frame_rx.time_us = (*DSML_CONTEXT.gettime_us)();
	} else { DSML_DEBUG_EMPTY_CALL(); }

	if(DSML_CONTEXT.frame_rx.buff_bytes >= DSML_FRAME_SIZE(header))
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.checksum);
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.frame_rx.buff);
		checksum = (*DSML_CONTEXT.checksum)(
			(const void*)(((const uint8*)DSML_CONTEXT.frame_rx.buff)
				+ sizeof(DSML_CONTEXT.frame_rx.header.checksum)),
			DSML_CONTEXT.frame_rx.buff_bytes
				- (uint16)sizeof(DSML_CONTEXT.frame_rx.header.checksum));

		src = (uint8*)DSML_CONTEXT.frame_rx.buff;

		{
			DSML_FRAME_LIST_ITEM_TOOL(header, rx, src);
		}

		DSML_ASSERT((DSML_FRAME_SIZE(header) + DSML_CONTEXT.frame_rx.header.len)
			<= DSML_CONTEXT.frame_rx.buff_size,
			"incomming data size > rx-buff - checksum should fail!");

		if((DSML_CONTEXT.frame_rx.header.checksum == checksum)
			&& (DSML_CONTEXT.frame_rx.header.protocol_version
				== DSML_PROTOCOL_VERSION))
		{
			switch(DSML_CONTEXT.frame_rx.header.type)
			{
			case DSML_FRAME_TYPE_IDLE:
				if(DSML_CONTEXT.frame_rx.header.len
					>= DSML_FRAME_SIZE(idle))
				{
					DSML_DEBUG_PRINT("received idle frame");
					{
						DSML_FRAME_LIST_ITEM_TOOL(idle, rx, src);
					}

					DSML_CONTEXT.peer_dir_magic =
						DSML_CONTEXT.frame_rx.type_data.idle.dir_magic;
					DSML_CONTEXT.peer_master_priority =
						DSML_CONTEXT.frame_rx.type_data.idle.master_priority;

					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
				} else { DSML_DEBUG_EMPTY_CALL(); }
				break;
#ifndef DSML_CMD_DISABLE
			case DSML_FRAME_TYPE_CMD:
				if(DSML_CONTEXT.frame_rx.header.len
					>= DSML_FRAME_SIZE(cmd))
				{
					DSML_DEBUG_PRINT("received cmd frame");
					{
						DSML_FRAME_LIST_ITEM_TOOL(cmd, rx, src);
					}
					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
				} else { DSML_DEBUG_EMPTY_CALL(); }
				break;
			case DSML_FRAME_TYPE_CMD_END:
				if(DSML_CONTEXT.frame_rx.header.len
					>= DSML_FRAME_SIZE(cmd_end))
				{
					DSML_DEBUG_PRINT("received cmd_end frame");
					{
						DSML_FRAME_LIST_ITEM_TOOL(cmd_end, rx, src);
					}
					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
				} else { DSML_DEBUG_EMPTY_CALL(); }
				break;
#endif /* #ifndef DSML_CMD_DISABLE */
#if !defined(DSML_READ_DISABLE) || !defined(DSML_WRITE_DISABLE)
#ifndef DSML_READ_DISABLE
			case DSML_FRAME_TYPE_READ_INIT:
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
			case DSML_FRAME_TYPE_WRITE_INIT:
#endif /* #ifndef DSML_WRITE_DISABLE */
				if(DSML_CONTEXT.frame_rx.header.len
					>= DSML_FRAME_SIZE(file_init))
				{
					DSML_DEBUG_PRINT("received file_init frame");
					{
						DSML_FRAME_LIST_ITEM_TOOL(file_init, rx, src);
					}
					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
				} else { DSML_DEBUG_EMPTY_CALL(); }
				break;
#ifndef DSML_READ_DISABLE
			case DSML_FRAME_TYPE_READ_DATA:
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
			case DSML_FRAME_TYPE_WRITE_DATA:
#endif /* #ifndef DSML_WRITE_DISABLE */
				if(DSML_CONTEXT.frame_rx.header.len
					>= DSML_FRAME_SIZE(file_data))
				{
					DSML_DEBUG_PRINT("received file_data frame");
					{
						DSML_FRAME_LIST_ITEM_TOOL(file_data, rx, src);
					}
					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
				} else { DSML_DEBUG_EMPTY_CALL(); }
				break;
#ifndef DSML_READ_DISABLE
			case DSML_FRAME_TYPE_READ_END:
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
			case DSML_FRAME_TYPE_WRITE_END:
#endif /* #ifndef DSML_WRITE_DISABLE */
				if(DSML_CONTEXT.frame_rx.header.len
					>= DSML_FRAME_SIZE(file_end))
				{
					DSML_DEBUG_PRINT("received file_end frame");
					{
						DSML_FRAME_LIST_ITEM_TOOL(file_end, rx, src);
					}
					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
				} else { DSML_DEBUG_EMPTY_CALL(); }
				break;
#endif /* #if !defined(DSML_READ_DISABLE) || !defined(DSML_WRITE_DISABLE) */
#ifndef DSML_MASTER_DISABLE
			case DSML_FRAME_TYPE_ACK:
				if(DSML_CONTEXT.frame_rx.header.len
					>= DSML_FRAME_SIZE(ack))
				{
					DSML_DEBUG_PRINT("received ack frame");
					{
						DSML_FRAME_LIST_ITEM_TOOL(ack, rx, src);
					}
					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
				} else { DSML_DEBUG_EMPTY_CALL(); }
				break;
			case DSML_FRAME_TYPE_NACK:
				if(DSML_CONTEXT.frame_rx.header.len
					>= DSML_FRAME_SIZE(nack))
				{
					DSML_DEBUG_PRINT("received nack frame");
					{
						DSML_FRAME_LIST_ITEM_TOOL(nack, rx, src);
					}
					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
				} else { DSML_DEBUG_EMPTY_CALL(); }
				break;
#endif /* #ifndef DSML_MASTER_DISABLE */
			case DSML_FRAME_TYPE_ABORT:
				if(DSML_CONTEXT.frame_rx.header.len
					>= DSML_FRAME_SIZE(abort))
				{
					DSML_DEBUG_PRINT("received abort frame");
					{
						DSML_FRAME_LIST_ITEM_TOOL(abort, rx, src);
					}
					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
				} else { DSML_DEBUG_EMPTY_CALL(); }
				break;
			default:
				DSML_ASSERT(DSML_FALSE, "unknown RX frame type");
				DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
				break;
			}
		} else { DSML_DEBUG_EMPTY_CALL(); }
	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_CONTEXT.frame_rx.user_bytes = UINT16_C(0);
	DSML_CONTEXT.frame_rx.user_buff = DSML_NULL;

	if(DSML_CONTEXT.frame_rx.is_valid == DSML_TRUE)
	{
		DSML_ASSERT((void*)src > DSML_CONTEXT.frame_rx.buff,
			"should not happen");
		DSML_ASSERT((reg)(DSML_CONTEXT.frame_rx.buff_bytes)
			>= (reg)((void*)src - DSML_CONTEXT.frame_rx.buff),
			"should not happen");

		DSML_CONTEXT.frame_rx.user_bytes =
			DSML_CONTEXT.frame_rx.buff_bytes
				- (uint16)(src - (uint8*)DSML_CONTEXT.frame_rx.buff);
		if(DSML_CONTEXT.frame_rx.user_bytes > UINT16_C(0))
		{
			DSML_DEBUG_PRINT("frame contains additional data");

			DSML_CONTEXT.frame_rx.user_buff = (void*)src;
		} else { DSML_DEBUG_EMPTY_CALL(); }

		DSML_DEBUG_FRAME_DUMP(&DSML_CONTEXT, &DSML_CONTEXT.frame_rx);

	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return (DSML_CONTEXT.frame_rx.is_valid == DSML_TRUE
		? DSML_RESULT_OK : DSML_RESULT_ERROR);
}

DSML_STATIC reg dsml_frame_tx_code(DSML_CONTEXT_ARG)
{
	uint16 i;
	uint8 * src;
	const uint8 * ub;

	DSML_FUNCTION_BEGIN();

	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	DSML_CONTEXT.frame_tx.is_valid = DSML_FALSE;

	if(DSML_CONTEXT.frame_tx.buff_size < DSML_FRAME_SIZE(header))
	{
		DSML_ASSERT(DSML_FALSE, "header size > tx-buff");
	}
	else
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.frame_tx.buff);
		src = (uint8*)DSML_CONTEXT.frame_tx.buff;

		DSML_CONTEXT.frame_tx.header.protocol_version = DSML_PROTOCOL_VERSION;
		DSML_CONTEXT.frame_tx.header.session =
			DSML_CONTEXT.session_data.session;
		DSML_CONTEXT.frame_tx.header.sequence_number =
			DSML_CONTEXT.session_data.sequence_number;
		DSML_CONTEXT.frame_tx.header.type = DSML_CONTEXT.session_data.type;
		DSML_CONTEXT.frame_tx.header.len =
			DSML_CONTEXT.frame_tx.buff_size - DSML_FRAME_SIZE(header);
		{
			DSML_FRAME_LIST_ITEM_TOOL(header, tx, src);
		}

		switch(DSML_CONTEXT.frame_tx.header.type)
		{
		case DSML_FRAME_TYPE_IDLE:
			if(DSML_CONTEXT.frame_tx.header.len
				>= DSML_FRAME_SIZE(idle))
			{
				DSML_CONTEXT.frame_tx.type_data.idle.dir_magic
					= DSML_CONTEXT.dir_magic;

				/* check if we need to change arbitration magic numbers */
				while(DSML_CONTEXT.peer_master_priority
					== DSML_CONTEXT.master_priority)
				{
					DSML_DEBUG_PRINT("looking for new arbitration magic");
					DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.rand);
					DSML_CONTEXT.master_priority = (*DSML_CONTEXT.rand)();
				}
				DSML_CONTEXT.frame_tx.type_data.idle.master_priority =
					DSML_CONTEXT.master_priority;

				DSML_DEBUG_PRINT("preparing idle frame");
				{
					DSML_FRAME_LIST_ITEM_TOOL(idle, tx, src);
				}
				DSML_CONTEXT.frame_tx.is_valid = DSML_TRUE;
				DSML_CONTEXT.frame_tx.header.len = DSML_FRAME_SIZE(idle);
			} else { DSML_DEBUG_EMPTY_CALL(); }
			break;
#ifndef DSML_CMD_DISABLE
		case DSML_FRAME_TYPE_CMD:
			if(DSML_CONTEXT.frame_tx.header.len
				>= DSML_FRAME_SIZE(cmd))
			{
				DSML_DEBUG_PRINT("preparing cmd frame");
				{
					DSML_FRAME_LIST_ITEM_TOOL(cmd, tx, src);
				}
				DSML_CONTEXT.frame_tx.is_valid = DSML_TRUE;
				DSML_CONTEXT.frame_tx.header.len = DSML_FRAME_SIZE(cmd);
			} else { DSML_DEBUG_EMPTY_CALL(); }
			break;
		case DSML_FRAME_TYPE_CMD_END:
			if(DSML_CONTEXT.frame_tx.header.len
				>= DSML_FRAME_SIZE(cmd_end))
			{
				DSML_DEBUG_PRINT("preparing cmd_end frame");
				{
					DSML_FRAME_LIST_ITEM_TOOL(cmd_end, tx, src);
				}
				DSML_CONTEXT.frame_tx.is_valid = DSML_TRUE;
				DSML_CONTEXT.frame_tx.header.len = DSML_FRAME_SIZE(cmd_end);
			} else { DSML_DEBUG_EMPTY_CALL(); }
			break;
#endif /* #ifndef DSML_CMD_DISABLE */
#if !defined(DSML_READ_DISABLE) || !defined(DSML_WRITE_DISABLE)
#ifndef DSML_READ_DISABLE
		case DSML_FRAME_TYPE_READ_INIT:
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
		case DSML_FRAME_TYPE_WRITE_INIT:
#endif /* #ifndef DSML_WRITE_DISABLE */
			if(DSML_CONTEXT.frame_tx.header.len
				>= DSML_FRAME_SIZE(file_init))
			{
				DSML_DEBUG_PRINT("preparing file_init frame");
				{
					DSML_FRAME_LIST_ITEM_TOOL(file_init, tx, src);
				}
				DSML_CONTEXT.frame_tx.is_valid = DSML_TRUE;
				DSML_CONTEXT.frame_tx.header.len = DSML_FRAME_SIZE(file_init);
			} else { DSML_DEBUG_EMPTY_CALL(); }
			break;
#ifndef DSML_READ_DISABLE
		case DSML_FRAME_TYPE_READ_DATA:
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
		case DSML_FRAME_TYPE_WRITE_DATA:
#endif /* #ifndef DSML_WRITE_DISABLE */
			if(DSML_CONTEXT.frame_tx.header.len
				>= DSML_FRAME_SIZE(file_data))
			{
				DSML_DEBUG_PRINT("preparing file_data frame");
				{
					DSML_FRAME_LIST_ITEM_TOOL(file_data, tx, src);
				}
				DSML_CONTEXT.frame_tx.is_valid = DSML_TRUE;
				DSML_CONTEXT.frame_tx.header.len = DSML_FRAME_SIZE(file_data);
			} else { DSML_DEBUG_EMPTY_CALL(); }
			break;
#ifndef DSML_READ_DISABLE
		case DSML_FRAME_TYPE_READ_END:
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
		case DSML_FRAME_TYPE_WRITE_END:
#endif /* #ifndef DSML_WRITE_DISABLE */
			if(DSML_CONTEXT.frame_tx.header.len
				>= DSML_FRAME_SIZE(file_end))
			{
				DSML_DEBUG_PRINT("preparing file_end frame");
				{
					DSML_FRAME_LIST_ITEM_TOOL(file_end, tx, src);
				}
				DSML_CONTEXT.frame_tx.is_valid = DSML_TRUE;
				DSML_CONTEXT.frame_tx.header.len = DSML_FRAME_SIZE(file_end);
			} else { DSML_DEBUG_EMPTY_CALL(); }
			break;
#endif /* #if !defined(DSML_READ_DISABLE) || !defined(DSML_WRITE_DISABLE) */
#ifndef DSML_SLAVE_DISABLE
		case DSML_FRAME_TYPE_ACK:
			if(DSML_CONTEXT.frame_tx.header.len
				>= DSML_FRAME_SIZE(ack))
			{
				DSML_DEBUG_PRINT("preparing ack frame");
				{
					DSML_FRAME_LIST_ITEM_TOOL(ack, tx, src);
				}
				DSML_CONTEXT.frame_tx.is_valid = DSML_TRUE;
				DSML_CONTEXT.frame_tx.header.len = DSML_FRAME_SIZE(ack);
			} else { DSML_DEBUG_EMPTY_CALL(); }
			break;
		case DSML_FRAME_TYPE_NACK:
			if(DSML_CONTEXT.frame_tx.header.len
				>= DSML_FRAME_SIZE(nack))
			{
				DSML_DEBUG_PRINT("preparing nack frame");
				{
					DSML_FRAME_LIST_ITEM_TOOL(nack, tx, src);
				}
				DSML_CONTEXT.frame_tx.is_valid = DSML_TRUE;
				DSML_CONTEXT.frame_tx.header.len = DSML_FRAME_SIZE(nack);
			} else { DSML_DEBUG_EMPTY_CALL(); }
			break;
#endif /* #ifndef DSML_SLAVE_DISABLE */
		case DSML_FRAME_TYPE_ABORT:
			if(DSML_CONTEXT.frame_tx.header.len
				>= DSML_FRAME_SIZE(abort))
			{
				DSML_DEBUG_PRINT("preparing abort frame");
				{
					DSML_FRAME_LIST_ITEM_TOOL(abort, tx, src);
				}
				DSML_CONTEXT.frame_tx.is_valid = DSML_TRUE;
				DSML_CONTEXT.frame_tx.header.len = DSML_FRAME_SIZE(abort);
			} else { DSML_DEBUG_EMPTY_CALL(); }
			break;
		default:
			DSML_ASSERT(DSML_FALSE, "unknown TX frame type");
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
			break;
		}
	}

	if((DSML_CONTEXT.frame_tx.is_valid == DSML_TRUE)
		&& (DSML_CONTEXT.frame_tx.user_bytes > UINT16_C(0)))
	{
		if(DSML_CONTEXT.frame_tx.user_bytes >
			(DSML_CONTEXT.frame_tx.buff_size
				- DSML_CONTEXT.frame_tx.header.len - DSML_FRAME_SIZE(header)))
		{
			DSML_CONTEXT.frame_tx.is_valid = DSML_FALSE;

			DSML_ASSERT(DSML_FALSE, "too much user data in TX frame");
		}
		else
		{
			DSML_CONTEXT.frame_tx.header.len +=
				DSML_CONTEXT.frame_tx.user_bytes;

			DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.frame_tx.user_buff);

			if(DSML_CONTEXT.frame_tx.user_bytes > UINT16_C(0))
			{
				DSML_DEBUG_PRINT("frame contains additional data");
			} else { DSML_DEBUG_EMPTY_CALL(); }

			ub = DSML_CONTEXT.frame_tx.user_buff;
			i = DSML_CONTEXT.frame_tx.user_bytes;
			while(i > UINT16_C(0))
			{
				i--;
				*src++ = *ub++;
			}
		}
	} else { DSML_DEBUG_EMPTY_CALL(); }

	if(DSML_CONTEXT.frame_tx.is_valid == DSML_TRUE)
	{
		DSML_CONTEXT.frame_tx.buff_bytes =
			DSML_CONTEXT.frame_tx.header.len + DSML_FRAME_SIZE(header);

		src = (uint8*)DSML_CONTEXT.frame_tx.buff;
		{
			DSML_FRAME_LIST_ITEM_TOOL(header, tx, src);
		}

		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.checksum);
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.frame_tx.buff);
		DSML_CONTEXT.frame_tx.header.checksum =
			(*DSML_CONTEXT.checksum)(
				(const void*)(((const uint8*)DSML_CONTEXT.frame_tx.buff)
					+ sizeof(DSML_CONTEXT.frame_tx.header.checksum)),
				DSML_CONTEXT.frame_tx.buff_bytes
					- (uint16)sizeof(DSML_CONTEXT.frame_tx.header.checksum));

		src = (uint8*)DSML_CONTEXT.frame_tx.buff;
		{
			DSML_FRAME_LIST_ITEM_TOOL(header, tx, src);
		}

		DSML_DEBUG_FRAME_DUMP(&DSML_CONTEXT, &DSML_CONTEXT.frame_tx);

	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return (DSML_CONTEXT.frame_tx.is_valid == DSML_TRUE
		? DSML_RESULT_OK : DSML_RESULT_ERROR);
}

DSML_STATIC reg dsml_send(DSML_CONTEXT_ARG)
{
	reg res;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);
	res = (*DSML_CONTEXT.send)(&DSML_CONTEXT, &DSML_CONTEXT.frame_tx);
	if(res == DSML_RESULT_OK)
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.gettime_us);
		DSML_CONTEXT.frame_tx.time_us = (*DSML_CONTEXT.gettime_us)();
	} else { DSML_DEBUG_EMPTY_CALL(); }
	DSML_FUNCTION_END();
	return res;
}
#define dsml_resend_last_tx_frame(d) do { dsml_send((d)); } while(0)

DSML_STATIC reg dsml_send_idle(DSML_CONTEXT_ARG)
{
	reg res;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

#ifndef DSML_SLAVE_DISABLE
	DSML_ASSERT(!(DSML_CONTEXT.status & DSML_STATUS_SLAVE),
		"not a slave function!");
#endif /* #ifndef DSML_SLAVE_DISABLE */

	/*
		NOTE: DSML_CONTEXT.frame_tx.type_data.idle.xxx
		data will be loaded in dsml_frame_tx_code()
	*/
	DSML_CONTEXT.frame_tx.user_bytes = UINT16_C(0);
	DSML_CONTEXT.frame_tx.user_buff = DSML_NULL;

	DSML_CONTEXT.session_data.type = DSML_STATE_IDLE;
	DSML_CONTEXT.session_data.cmd_type = DSML_STATE_CMD_SUB_TYPE_NONE;
	DSML_CONTEXT.session_data.sequence_number = UINT8_C(0);
	DSML_CONTEXT.session_data.session = UINT8_C(0);

	res = dsml_frame_tx_code(&DSML_CONTEXT);
	if(res == DSML_RESULT_OK) { res = dsml_send(&DSML_CONTEXT); }
	else { DSML_DEBUG_EMPTY_CALL(); }

#ifndef DSML_MASTER_DISABLE
	if((DSML_CONTEXT.frame_rx.is_valid
			&& (DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_NACK))
#ifndef DSML_MASTER_CMD_DISABLE
		|| (DSML_CONTEXT.state == DSML_STATE_CMD_END)
#endif /* #ifndef DSML_MASTER_CMD_DISABLE */
#ifndef DSML_MASTER_READ_DISABLE
		|| (DSML_CONTEXT.state == DSML_STATE_READ_END)
#endif /* #ifndef DSML_MASTER_READ_DISABLE */
#ifndef DSML_MASTER_WRITE_DISABLE
		|| (DSML_CONTEXT.state == DSML_STATE_WRITE_END)
#endif /* #ifndef DSML_MASTER_WRITE_DISABLE */
		)
	{
		DSML_ASSERT(DSML_CONTEXT.status & DSML_STATUS_MASTER,
			"master only case!");
		
		DSML_CONTEXT.state = DSML_STATE_WAIT_FOR_IDLE;
	} else { DSML_DEBUG_EMPTY_CALL(); }
#endif /* #ifndef DSML_MASTER_DISABLE */

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC reg dsml_send_abort(DSML_CONTEXT_ARG, int32 return_code /*TODO*/)
{
	reg res;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	dsml_close_session(&DSML_CONTEXT);

	DSML_CONTEXT.session_data.type = DSML_FRAME_TYPE_ABORT;
	DSML_CONTEXT.session_data.sequence_number =
		DSML_CONTEXT.frame_rx.header.sequence_number;

	DSML_CONTEXT.frame_tx.type_data.abort.return_code = return_code;
	DSML_CONTEXT.frame_tx.user_bytes = UINT16_C(0);
	DSML_CONTEXT.frame_tx.user_buff = DSML_NULL;

	DSML_CALLBACK(&DSML_CONTEXT, ABORT);

	res = dsml_frame_tx_code(&DSML_CONTEXT);
	if(res == DSML_RESULT_OK) { res = dsml_send(&DSML_CONTEXT); }
	else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return res;
}

#ifndef DSML_SLAVE_DISABLE
DSML_STATIC reg dsml_ack_nack_call(DSML_CONTEXT_ARG,
	void * buff, uint16 user_bytes, int32 return_code)
{
	reg res;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	DSML_CONTEXT.session_data.sequence_number =
		DSML_CONTEXT.frame_rx.header.sequence_number;

	DSML_CONTEXT.frame_tx.type_data.ack.type = DSML_CONTEXT.state;
	DSML_CONTEXT.frame_tx.type_data.ack.cmd_type =
		DSML_CONTEXT.session_data.cmd_type;
	DSML_CONTEXT.frame_tx.type_data.ack.file = DSML_CONTEXT.session_data.file;
	DSML_CONTEXT.frame_tx.type_data.ack.file_attrifutes =
		dsml_local_file_attributes(&DSML_CONTEXT,
			DSML_CONTEXT.session_data.file);
	DSML_CONTEXT.frame_tx.type_data.ack.return_code = return_code;
	DSML_CONTEXT.frame_tx.user_bytes = user_bytes;
	DSML_CONTEXT.frame_tx.user_buff = buff;

	res = dsml_frame_tx_code(&DSML_CONTEXT);
	if(res == DSML_RESULT_OK) { res = dsml_send(&DSML_CONTEXT); }
	else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC reg dsml_send_ack(DSML_CONTEXT_ARG,
	void * buff, uint16 user_bytes, int32 return_code)
{
	reg res;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

#ifndef DSML_MASTER_DISABLE
	DSML_ASSERT(!(DSML_CONTEXT.status & DSML_STATUS_MASTER),
		"not a master function!");
#endif /* #ifndef DSML_MASTER_DISABLE */

	DSML_CONTEXT.session_data.type = DSML_FRAME_TYPE_ACK;
	res = dsml_ack_nack_call(&DSML_CONTEXT,
		buff, user_bytes,
		return_code);

	if(DSML_FALSE
#ifndef DSML_SLAVE_CMD_DISABLE
		|| (DSML_CONTEXT.state == DSML_STATE_CMD_END)
#endif /* #ifndef DSML_SLAVE_CMD_DISABLE */
#ifndef DSML_SLAVE_READ_DISABLE
		|| (DSML_CONTEXT.state == DSML_STATE_READ_END)
#endif /* #ifndef DSML_SLAVE_READ_DISABLE */
#ifndef DSML_SLAVE_WRITE_DISABLE
		|| (DSML_CONTEXT.state == DSML_STATE_WRITE_END)
#endif /* #ifndef DSML_SLAVE_WRITE_DISABLE */
		)
	{
		DSML_ASSERT(DSML_CONTEXT.status & DSML_STATUS_SLAVE,
			"slave only case!");

		DSML_CONTEXT.state = DSML_STATE_WAIT_FOR_IDLE;
	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return res;
}

DSML_STATIC reg dsml_send_nack(DSML_CONTEXT_ARG, int32 return_code /*TODO*/)
{
	reg res;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

#ifndef DSML_MASTER_DISABLE
	DSML_ASSERT(!(DSML_CONTEXT.status & DSML_STATUS_MASTER),
		"not a master function!");
#endif /* #ifndef DSML_MASTER_DISABLE */

	DSML_CONTEXT.session_data.type = DSML_FRAME_TYPE_NACK;
	res = dsml_ack_nack_call(&DSML_CONTEXT,
		DSML_NULL, UINT16_C(0),
		return_code);

	if(DSML_CONTEXT.status & DSML_STATUS_BUSY)
	{
		DSML_ASSERT(DSML_CONTEXT.status & DSML_STATUS_SLAVE,
			"slave only case!");

		DSML_CONTEXT.state = DSML_STATE_WAIT_FOR_IDLE;
	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return res;
}
#endif /* #ifndef DSML_SLAVE_DISABLE */

/*TODO*/
DSML_STATIC reg dsml_close_session(DSML_CONTEXT_ARG)
{
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	if(DSML_CONTEXT.status & DSML_STATUS_BUSY)
	{
		if(DSML_CONTEXT.session_data.file != DSML_CMD_FILE_INVALID)
		{
			if(dsml_local_file_attributes(&DSML_CONTEXT,
				DSML_CONTEXT.session_data.file) & DSML_FILE_ATTRIBUTE_OPEN)
			{
				if(DSML_FALSE) { DSML_DEBUG_EMPTY_CALL(); }
#ifndef DSML_SLAVE_DISABLE
				else if(DSML_CONTEXT.status & DSML_STATUS_SLAVE)
				{
					dsml_local_file_close(&DSML_CONTEXT,
						DSML_CONTEXT.session_data.file,
						DSML_FILE_PID_REMOTE);
#ifndef DSML_SLAVE_WRITE_DISABLE
					if(DSML_CONTEXT.status & DSML_STATUS_WRITE)/*TODO*/
					{
						dsml_local_cmd(&DSML_CONTEXT,
							DSML_CONTEXT.session_data.file,
							DSML_STATE_CMD_SUB_TYPE_CORRUPT,
							DSML_NULL, UINT16_C(0), DSML_FILE_PID_REMOTE);
					} else { DSML_DEBUG_EMPTY_CALL(); }
#endif /* #ifndef DSML_SLAVE_WRITE_DISABLE */
				}
#endif /* #ifndef DSML_SLAVE_DISABLE */
#ifndef DSML_MASTER_DISABLE
				else if(DSML_CONTEXT.status & DSML_STATUS_MASTER)
				{
					dsml_local_file_close(&DSML_CONTEXT,
						DSML_CONTEXT.session_data.file,
						DSML_FILE_PID_INTERNAL);
#ifndef DSML_MASTER_READ_DISABLE
					if(DSML_CONTEXT.status & DSML_STATUS_READ)
					{
						dsml_local_cmd(&DSML_CONTEXT,
							DSML_CONTEXT.session_data.file,
							DSML_STATE_CMD_SUB_TYPE_CORRUPT,
							DSML_NULL, UINT16_C(0), DSML_FILE_PID_REMOTE);
					} else { DSML_DEBUG_EMPTY_CALL(); }
#endif /* #ifndef DSML_MASTER_READ_DISABLE */
				}
#endif /* #ifndef DSML_MASTER_DISABLE */
				else
				{
					DSML_ASSERT(DSML_FALSE, "should not happen");
				}
			} else { DSML_DEBUG_EMPTY_CALL(); }
		} else { DSML_DEBUG_EMPTY_CALL(); }

		DSML_CALLBACK(&DSML_CONTEXT, SESSION_END);

		DSML_CONTEXT.session_data.file = DSML_CMD_FILE_INVALID;

		DSML_CONTEXT.state = DSML_STATE_IDLE;
		DSML_CONTEXT.status = DSML_STATUS_INIT | DSML_STATUS_IDLE;
	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return DSML_RESULT_OK;
}

uint16 dsml_local_file_attributes(DSML_CONTEXT_ARG, uint16 file)
{
	uint16 attributes;
	struct dsml_file_tag * f;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);
	attributes = INT16_C(0);
	if(file >= DSML_CONTEXT.dir_size)
	{
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.dir);
		f = DSML_CONTEXT.dir[file];
		DSML_ASSERT_POINTER_CHECK(f);
		attributes = f->attributes;
	}
	DSML_FUNCTION_END();
	return attributes;
}

#ifndef DSML_FILE_USER_ATTRIBUTES_DISABLE
reg dsml_local_file_user_attributes_set(DSML_CONTEXT_ARG,
	uint16 file, uint16 user_attributes)
{
	reg res;
	struct dsml_file_tag * f;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);
	res = DSML_RESULT_ERROR;
	if(file >= DSML_CONTEXT.dir_size)
	{
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else
	{
		if(user_attributes & ~(DSML_FILE_ATTRIBUTE_MASK_USER))
		{
			DSML_DEBUG_PRINT("invalid user attributes!");
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
			DSML_CALLBACK(&DSML_CONTEXT, ERROR);
		}
		else
		{
			DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.dir);
			f = DSML_CONTEXT.dir[file];
			DSML_ASSERT_POINTER_CHECK(f);
			f->attributes |= user_attributes;
			res = DSML_RESULT_OK;
		}
	}
	DSML_FUNCTION_END();
	return res;
}

reg dsml_local_file_user_attributes_clear(DSML_CONTEXT_ARG,
	uint16 file, uint16 user_attributes)
{
	reg res;
	struct dsml_file_tag * f;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);
	res = DSML_RESULT_ERROR;
	if(file >= DSML_CONTEXT.dir_size)
	{
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else
	{
		if(user_attributes & ~(DSML_FILE_ATTRIBUTE_MASK_USER))
		{
			DSML_DEBUG_PRINT("invalid user attributes!");
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
			DSML_CALLBACK(&DSML_CONTEXT, ERROR);
		}
		else
		{
			DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.dir);
			f = DSML_CONTEXT.dir[file];
			DSML_ASSERT_POINTER_CHECK(f);
			f->attributes &= ~user_attributes;
			res = DSML_RESULT_OK;
		}
	}
	DSML_FUNCTION_END();
	return res;
}
#endif /* #ifndef DSML_FILE_USER_ATTRIBUTES_DISABLE */

int32 dsml_local_file_open(DSML_CONTEXT_ARG,
	uint16 file, uint16 oflag, uint16 pid)
{
	int32 res;
	struct dsml_file_tag * f;
	const struct dsml_file_iface_tag * iface;

	DSML_FUNCTION_BEGIN();

	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	DSML_ASSERT(pid != DSML_FILE_PID_NONE, "bad pid value");

	res = INT32_C(0);

	if(file >= DSML_CONTEXT.dir_size)
	{
		res = INT32_C(-1);
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.dir);
		f = DSML_CONTEXT.dir[file];
		DSML_ASSERT_POINTER_CHECK(f);
		if(f->pid == DSML_FILE_PID_NONE)
		{
			DSML_ASSERT(!(f->attributes & DSML_FILE_ATTRIBUTE_OPEN),
				"should not happen");
		
			if(pid == DSML_FILE_PID_INTERNAL)
			{
				if((f->attributes
						& (DSML_FILE_ATTRIBUTE_LOCAL_LOCK
							| DSML_FILE_ATTRIBUTE_REMOTE_LOCK))
					|| ((oflag & DSML_FILE_OFLAG_READ)
							&& !(f->attributes
								& DSML_FILE_ATTRIBUTE_LOCAL_READ))
					|| ((oflag & DSML_FILE_OFLAG_WRITE)
							&& !(f->attributes
								& DSML_FILE_ATTRIBUTE_LOCAL_WRITE)))
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					res = INT32_C(-1);
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}
			else if(pid == DSML_FILE_PID_REMOTE)
			{
				if((f->attributes & DSML_FILE_ATTRIBUTE_LOCAL_LOCK)
					|| ((oflag & DSML_FILE_OFLAG_READ)
						&& !(f->attributes & DSML_FILE_ATTRIBUTE_REMOTE_READ))
					|| ((oflag & DSML_FILE_OFLAG_WRITE)
						&& !(f->attributes & DSML_FILE_ATTRIBUTE_REMOTE_WRITE)))
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					res = INT32_C(-1);
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}
			else /* local application pid */
			{
				DSML_ASSERT(pid >= DSML_FILE_PID_USER_FIRST, "bad pid value");

				if((f->attributes & DSML_FILE_ATTRIBUTE_REMOTE_LOCK)
					|| ((oflag & DSML_FILE_OFLAG_READ)
						&& !(f->attributes & DSML_FILE_ATTRIBUTE_LOCAL_READ))
					|| ((oflag & DSML_FILE_OFLAG_WRITE)
						&& !(f->attributes & DSML_FILE_ATTRIBUTE_LOCAL_WRITE)))
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					res = INT32_C(-1);
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}

			if(res == INT32_C(0))
			{
				iface = f->iface;
				DSML_ASSERT_POINTER_CHECK(iface);
				DSML_ASSERT_POINTER_CHECK(iface->open);
				res = (*iface->open)(&DSML_CONTEXT, f, oflag);
				if(res >= INT32_C(0))
				{
					f->fd = res;
					f->pid = pid;
					f->attributes |= DSML_FILE_ATTRIBUTE_OPEN;

					if(pid >= DSML_FILE_PID_USER_FIRST)
					{
						f->attributes &= ~DSML_FILE_ATTRIBUTE_MODIFIED;
					} else { DSML_DEBUG_EMPTY_CALL(); }

					if(oflag & DSML_FILE_OFLAG_WRITE)
					{
						f->attributes &= ~DSML_FILE_ATTRIBUTE_CORRUPT;
					} else { DSML_DEBUG_EMPTY_CALL(); }
				} else { DSML_DEBUG_EMPTY_CALL(); }
			} else { DSML_DEBUG_EMPTY_CALL(); }
		}
		else if(f->pid == pid)
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EMFILE);
			res = INT32_C(-1);
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_ETXTBSY);
			res = INT32_C(-1);
		}
	}

	DSML_FUNCTION_END();
	return res;
}

int32 dsml_local_file_close(DSML_CONTEXT_ARG, uint16 file, uint16 pid)
{
	int32 res;
	struct dsml_file_tag * f;
	const struct dsml_file_iface_tag * iface;

	DSML_FUNCTION_BEGIN();

	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	DSML_ASSERT(pid != DSML_FILE_PID_NONE, "bad pid value");

	res = INT32_C(0);

	if(file >= DSML_CONTEXT.dir_size)
	{
		res = INT32_C(-1);
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.dir);
		f = DSML_CONTEXT.dir[file];
		DSML_ASSERT_POINTER_CHECK(f);
		if(f->pid == DSML_FILE_PID_NONE)
		{
			DSML_ASSERT(!(f->attributes & DSML_FILE_ATTRIBUTE_OPEN),
				"should not happen");

			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EBADF);
			res = INT32_C(-1);
		}
		else if(f->pid != pid)
		{
			DSML_ASSERT(f->attributes & DSML_FILE_ATTRIBUTE_OPEN,
				"should not happen");

			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
			res = INT32_C(-1);
		}
		else
		{
			DSML_ASSERT(f->attributes & DSML_FILE_ATTRIBUTE_OPEN,
				"should not happen");

			iface = f->iface;
			DSML_ASSERT_POINTER_CHECK(iface);
			DSML_ASSERT_POINTER_CHECK(iface->close);
			res = (*iface->close)(&DSML_CONTEXT, f);
			if(res >= INT32_C(0))
			{
				f->fd = INT32_C(-1);
				f->pid = DSML_FILE_PID_NONE;
				f->attributes &= ~DSML_FILE_ATTRIBUTE_OPEN;
			} else { DSML_DEBUG_EMPTY_CALL(); }
		}
	}

	DSML_FUNCTION_END();
	return res;
}

int32 dsml_local_file_read(DSML_CONTEXT_ARG,
	uint16 file, void * buff, uint32 nbyte, uint32 offset, uint16 pid)
{
	int32 res;
	struct dsml_file_tag * f;
	const struct dsml_file_iface_tag * iface;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	DSML_ASSERT(pid != DSML_FILE_PID_NONE, "bad pid value");

	res = INT32_C(0);

	if(file >= DSML_CONTEXT.dir_size)
	{
		res = INT32_C(-1);
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.dir);
		f = DSML_CONTEXT.dir[file];
		DSML_ASSERT_POINTER_CHECK(f);
		if(f->pid == DSML_FILE_PID_NONE)
		{
			DSML_ASSERT(!(f->attributes & DSML_FILE_ATTRIBUTE_OPEN),
				"should not happen");

			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EBADF);
			res = INT32_C(-1);
		}
		else if(f->pid != pid)
		{
			DSML_ASSERT(f->attributes & DSML_FILE_ATTRIBUTE_OPEN,
				"should not happen");

			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
			res = INT32_C(-1);
		}
		else
		{
			DSML_ASSERT(f->attributes & DSML_FILE_ATTRIBUTE_OPEN,
				"should not happen");

			if(pid == DSML_FILE_PID_INTERNAL)
			{
				if(!(f->attributes & DSML_FILE_ATTRIBUTE_LOCAL_READ))
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					res = INT32_C(-1);
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}
			else if(pid == DSML_FILE_PID_REMOTE)
			{
				if(!(f->attributes & DSML_FILE_ATTRIBUTE_REMOTE_READ))
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					res = INT32_C(-1);
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}
			else /* local application pid */
			{
				DSML_ASSERT(pid >= DSML_FILE_PID_USER_FIRST, "bad pid value");

				if(!(f->attributes & DSML_FILE_ATTRIBUTE_LOCAL_READ))
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					res = INT32_C(-1);
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}

			if(res == INT32_C(0))
			{
				iface = f->iface;
				DSML_ASSERT_POINTER_CHECK(iface);
				DSML_ASSERT_POINTER_CHECK(iface->read);
				res = (*iface->read)(&DSML_CONTEXT, f, buff, nbyte, offset);
			} else { DSML_DEBUG_EMPTY_CALL(); }
		}
	}

	DSML_FUNCTION_END();
	return res;
}

int32 dsml_local_file_write(DSML_CONTEXT_ARG,
	uint16 file, const void * buff, uint32 nbyte, uint32 offset, uint16 pid)
{
	int32 res;
	struct dsml_file_tag * f;
	const struct dsml_file_iface_tag * iface;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	DSML_ASSERT(pid != DSML_FILE_PID_NONE, "bad pid value");

	res = INT32_C(0);

	if(file >= DSML_CONTEXT.dir_size)
	{
		res = INT32_C(-1);
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.dir);
		f = DSML_CONTEXT.dir[file];
		DSML_ASSERT_POINTER_CHECK(f);
		if(f->pid == DSML_FILE_PID_NONE)
		{
			DSML_ASSERT(!(f->attributes & DSML_FILE_ATTRIBUTE_OPEN),
				"should not happen");

			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EBADF);
			res = INT32_C(-1);
		}
		else if(f->pid != pid)
		{
			DSML_ASSERT(f->attributes & DSML_FILE_ATTRIBUTE_OPEN,
				"should not happen");

			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
			res = INT32_C(-1);
		}
		else
		{
			DSML_ASSERT(f->attributes & DSML_FILE_ATTRIBUTE_OPEN,
				"should not happen");

			if(pid == DSML_FILE_PID_INTERNAL)
			{
				if(!(f->attributes & DSML_FILE_ATTRIBUTE_LOCAL_WRITE))
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					res = INT32_C(-1);
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}
			else if(pid == DSML_FILE_PID_REMOTE)
			{
				if(!(f->attributes & DSML_FILE_ATTRIBUTE_REMOTE_WRITE))
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					res = INT32_C(-1);
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}
			else /* local application pid */
			{
				DSML_ASSERT(pid >= DSML_FILE_PID_USER_FIRST, "bad pid value");

				if(!(f->attributes & DSML_FILE_ATTRIBUTE_LOCAL_WRITE))
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					res = INT32_C(-1);
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}

			if(res == INT32_C(0))
			{
				iface = f->iface;
				DSML_ASSERT_POINTER_CHECK(iface);
				DSML_ASSERT_POINTER_CHECK(iface->write);
				res = (*iface->write)(&DSML_CONTEXT, f, buff, nbyte, offset);
				if(res > INT32_C(0))
				{
					f->attributes |= DSML_FILE_ATTRIBUTE_MODIFIED;
				} else { DSML_DEBUG_EMPTY_CALL(); }
			} else { DSML_DEBUG_EMPTY_CALL(); }
		}
	}

	DSML_FUNCTION_END();
	return res;
}

int32 dsml_local_file_size(DSML_CONTEXT_ARG, uint16 file)
{
	int32 res;
	struct dsml_file_tag * f;
	const struct dsml_file_iface_tag * iface;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	if(file >= DSML_CONTEXT.dir_size)
	{
		res = INT32_C(-1);
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.dir);
		f = DSML_CONTEXT.dir[file];
		DSML_ASSERT_POINTER_CHECK(f);
		iface = f->iface;
		DSML_ASSERT_POINTER_CHECK(iface);
		DSML_ASSERT_POINTER_CHECK(iface->size);
		res = (*iface->size)(&DSML_CONTEXT, f);
	}

	DSML_FUNCTION_END();
	return res;
}

#ifndef DSML_MASTER_CMD_DISABLE
reg dsml_remote_cmd(DSML_CONTEXT_ARG,
	uint16 file, uint8 cmd, const void * buff, uint16 nbyte)
{
	reg res;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	res = DSML_RESULT_ERROR;
	
	if((file >= DSML_CONTEXT.dir_size) && (file != DSML_CMD_FILE_INVALID))
	{
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else if(nbyte > (DSML_CONTEXT.frame_tx.buff_size
		- DSML_FRAME_SIZE(header) - DSML_FRAME_SIZE(cmd)))
	{
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else if(!(DSML_CONTEXT.status & DSML_STATUS_BUSY))
	{
		DSML_ASSERT(DSML_FRAME_SIZE(cmd) == DSML_FRAME_SIZE(cmd_end),
			"buffer data are stored in the frame_tx!");

		DSML_CONTEXT.state = DSML_STATE_CMD;

		DSML_CONTEXT.status |=
			DSML_STATUS_CMD | DSML_STATUS_MASTER
			| DSML_STATUS_BUSY;

		DSML_CONTEXT.frame_tx.type_data.cmd.cmd_type = cmd;
		DSML_CONTEXT.frame_tx.type_data.cmd.file = file;

		DSML_CONTEXT.frame_tx.user_bytes = nbyte;
		DSML_CONTEXT.frame_tx.user_buff = (void*)buff;

		if(nbyte > UINT16_C(0))
		{
			DSML_ASSERT_POINTER_CHECK(buff);
		} else { DSML_DEBUG_EMPTY_CALL(); }

		DSML_CONTEXT.session_data.type = DSML_STATE_CMD;
		DSML_CONTEXT.session_data.cmd_type = cmd;
		DSML_CONTEXT.session_data.file = file;
		DSML_CONTEXT.session_data.nbyte = nbyte;
		DSML_CONTEXT.session_data.offset = UINT32_C(0);
		DSML_CONTEXT.session_data.nbyte_remaining = UINT32_C(0);
		DSML_CONTEXT.session_data.offset_current = UINT32_C(0);
		DSML_CONTEXT.session_data.retry_count = UINT8_C(0);
		DSML_CONTEXT.session_data.sequence_number = UINT8_C(0);
		DSML_CONTEXT.session++;
		if(!DSML_CONTEXT.session) { DSML_CONTEXT.session++; }
		else { DSML_DEBUG_EMPTY_CALL(); }
		DSML_CONTEXT.session_data.session = DSML_CONTEXT.session;

		res = dsml_frame_tx_code(&DSML_CONTEXT);
		if(res == DSML_RESULT_OK) { res = dsml_send(&DSML_CONTEXT); }
		else { DSML_DEBUG_EMPTY_CALL(); }
	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return res;
}
#endif /* #ifndef DSML_MASTER_CMD_DISABLE */

reg dsml_local_cmd(DSML_CONTEXT_ARG,
	uint16 file, uint8 cmd, const void * buff, uint16 nbyte, uint16 pid)
{
	reg res;
	struct dsml_file_tag * f;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	res = DSML_RESULT_ERROR;

	if((file >= DSML_CONTEXT.dir_size) && (file != DSML_CMD_FILE_INVALID))
	{
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else if(nbyte > (DSML_CONTEXT.frame_tx.buff_size
		- DSML_FRAME_SIZE(header) - DSML_FRAME_SIZE(cmd)))
	{
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else if((!(DSML_CONTEXT.status & DSML_STATUS_BUSY))
		|| (pid == DSML_FILE_PID_REMOTE))
	{
		DSML_ASSERT(DSML_FRAME_SIZE(cmd) == DSML_FRAME_SIZE(cmd_end),
			"buffer data are stored in the frame_tx!");

		switch(cmd)
		{
		case DSML_STATE_CMD_SUB_TYPE_NONE:
			DSML_DEBUG_PRINT("ignoring unsuported STD_NONE command!!!");
			break;
		case DSML_STATE_CMD_SUB_TYPE_RELOAD:
			DSML_CALLBACK(&DSML_CONTEXT, RELOAD);
			break;
		case DSML_STATE_CMD_SUB_TYPE_EXEC:
		case DSML_STATE_CMD_SUB_TYPE_CORRUPT:
		case DSML_STATE_CMD_SUB_TYPE_LOCK:
		case DSML_STATE_CMD_SUB_TYPE_UNLOCK:
			if(file == DSML_CMD_FILE_INVALID)
			{
				DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
			}
			else
			{
				DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.dir);
				f = DSML_CONTEXT.dir[file];
				DSML_ASSERT_POINTER_CHECK(f);
				if((f->pid == DSML_FILE_PID_NONE) || (f->pid == pid))
				{
					DSML_ASSERT(!(f->attributes & DSML_FILE_ATTRIBUTE_OPEN),
						"should not happen");

					if(pid == DSML_FILE_PID_INTERNAL)
					{
						DSML_ASSERT(DSML_FALSE, "should not happen");

						DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EACCES);
					}
					else if(pid == DSML_FILE_PID_REMOTE)
					{
						if(f->attributes & DSML_FILE_ATTRIBUTE_LOCAL_LOCK)
						{
							DSML_LAST_ERROR_SET(&DSML_CONTEXT,
								DSML_ERRNO_EACCES);
						}
						else
						{
							res = DSML_RESULT_OK;
						}
					}
					else /* local application pid */
					{
						DSML_ASSERT(pid >= DSML_FILE_PID_USER_FIRST,
							"bad pid value");

						if(f->attributes & DSML_FILE_ATTRIBUTE_REMOTE_LOCK)
						{
							DSML_LAST_ERROR_SET(&DSML_CONTEXT,
								DSML_ERRNO_EACCES);
						}
						else
						{
							res = DSML_RESULT_OK;
						}
					}

					if(res == DSML_RESULT_OK)
					{
						switch(cmd)
						{
							case DSML_STATE_CMD_SUB_TYPE_EXEC:
								DSML_CALLBACK(&DSML_CONTEXT, EXEC);
								break;
							case DSML_STATE_CMD_SUB_TYPE_CORRUPT:
								f->attributes |= DSML_FILE_ATTRIBUTE_CORRUPT
									| DSML_FILE_ATTRIBUTE_MODIFIED;
								break;
							case DSML_STATE_CMD_SUB_TYPE_LOCK:
								if(pid == DSML_FILE_PID_REMOTE)
								{
									if(f->attributes
										& DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW)
									{
										f->attributes |=
											DSML_FILE_ATTRIBUTE_REMOTE_LOCK;
									}
									else
									{
										DSML_LAST_ERROR_SET(&DSML_CONTEXT,
											DSML_ERRNO_EACCES);
									}
								}
								else
								{
									if(f->attributes
										& DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW)
									{
										f->attributes |=
											DSML_FILE_ATTRIBUTE_LOCAL_LOCK;
									}
									else
									{
										DSML_LAST_ERROR_SET(&DSML_CONTEXT,
											DSML_ERRNO_EACCES);
									}
								}
								break;
							case DSML_STATE_CMD_SUB_TYPE_UNLOCK:
								if(pid == DSML_FILE_PID_REMOTE)
								{
									if(f->attributes
										& DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW)
									{
										f->attributes &=
											~DSML_FILE_ATTRIBUTE_REMOTE_LOCK;
									}
									else
									{
										DSML_LAST_ERROR_SET(&DSML_CONTEXT,
											DSML_ERRNO_EACCES);
									}
								}
								else
								{
									if(f->attributes
										& DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW)
									{
										f->attributes &=
											~DSML_FILE_ATTRIBUTE_LOCAL_LOCK;
									}
									else
									{
										DSML_LAST_ERROR_SET(&DSML_CONTEXT,
											DSML_ERRNO_EACCES);
									}
								}
								break;
							default:
								DSML_ASSERT(DSML_FALSE, "should not happen");
								DSML_LAST_ERROR_SET(&DSML_CONTEXT,
									DSML_ERRNO_EINVAL);
								break;
						}
					} else { DSML_DEBUG_EMPTY_CALL(); }
				}
				else
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_ETXTBSY);
				}
			}
			break;
		default:
			if(cmd >= DSML_STATE_CMD_TYPE_USER_FIRST)
			{
				if(pid == DSML_FILE_PID_REMOTE)
				{
					DSML_CALLBACK(&DSML_CONTEXT, USER_CMD);
				}
				else
				{
					DSML_CONTEXT.state = DSML_STATE_CMD_END;

					DSML_CONTEXT.status |= DSML_STATUS_CMD | DSML_STATUS_SLAVE
						| DSML_STATUS_BUSY;

					DSML_CONTEXT.frame_rx.is_valid = DSML_TRUE;
					DSML_CONTEXT.frame_rx.header.type = DSML_FRAME_TYPE_ACK;

					DSML_CONTEXT.frame_rx.type_data.ack.type =
						DSML_FRAME_TYPE_CMD_END;
					DSML_CONTEXT.frame_rx.type_data.ack.cmd_type = cmd;
					DSML_CONTEXT.frame_rx.type_data.ack.file = file;
					DSML_CONTEXT.frame_rx.type_data.ack.file_attrifutes =
						UINT16_C(0);
					DSML_CONTEXT.frame_rx.type_data.ack.return_code =
						INT32_C(0);

					DSML_CONTEXT.frame_rx.user_bytes = nbyte;
					DSML_CONTEXT.frame_rx.user_buff = (void*)buff;

					DSML_CONTEXT.session_data.type = DSML_STATE_CMD_END;
					DSML_CONTEXT.session_data.cmd_type = cmd;
					DSML_CONTEXT.session_data.file = file;

					DSML_CALLBACK(&DSML_CONTEXT, USER_CMD);

					DSML_CONTEXT.frame_rx.is_valid = DSML_FALSE;

					DSML_CONTEXT.state = DSML_STATE_IDLE;
					DSML_CONTEXT.status &= ~(DSML_STATUS_CMD
						| DSML_STATUS_SLAVE | DSML_STATUS_BUSY);
				}
			}
			else
			{
				DSML_DEBUG_PRINT("ignoring unsuported STD command!!!");
			}
			break;
		}

		res = DSML_RESULT_OK;
	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return res;
}

#ifndef DSML_MASTER_READ_DISABLE
reg dsml_remote_read(DSML_CONTEXT_ARG, uint16 file, uint32 nbyte, uint32 offset)
{
	reg res;
	int32 fd;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	res = DSML_RESULT_ERROR;

	if(file >= DSML_CONTEXT.dir_size)
	{
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else if(!(DSML_CONTEXT.status & DSML_STATUS_BUSY))
	{
		fd = dsml_local_file_size(&DSML_CONTEXT, file);

		DSML_ASSERT(((uint64)nbyte + (uint64)offset) <
			UINT64_C(0x7fffffff), "file size not supported");

		if((fd >= INT32_C(0)) && ((uint32)fd >= (nbyte + offset)))
		{
			fd = dsml_local_file_open(&DSML_CONTEXT,
				file, DSML_FILE_OFLAG_WRITE, DSML_FILE_PID_INTERNAL);
			if(fd >= INT32_C(0))
			{
				DSML_CONTEXT.state = DSML_STATE_READ_INIT;

				DSML_CONTEXT.status |= DSML_STATUS_READ | DSML_STATUS_MASTER
					| DSML_STATUS_BUSY;

				DSML_CONTEXT.frame_tx.type_data.file_init.file = file;
				DSML_CONTEXT.frame_tx.type_data.file_init.nbyte = nbyte;
				DSML_CONTEXT.frame_tx.type_data.file_init.offset = offset;
				DSML_CONTEXT.frame_tx.user_bytes = UINT16_C(0);
				DSML_CONTEXT.frame_tx.user_buff = DSML_NULL;

				DSML_CONTEXT.session_data.type = DSML_STATE_READ_INIT;
				DSML_CONTEXT.session_data.cmd_type =
					DSML_STATE_CMD_SUB_TYPE_NONE;
				DSML_CONTEXT.session_data.file = file;
				DSML_CONTEXT.session_data.nbyte = nbyte;
				DSML_CONTEXT.session_data.offset = offset;
				DSML_CONTEXT.session_data.nbyte_remaining = nbyte;
				DSML_CONTEXT.session_data.offset_current = offset;
				DSML_CONTEXT.session_data.retry_count = UINT8_C(0);
				DSML_CONTEXT.session_data.sequence_number = UINT8_C(0);
				DSML_CONTEXT.session++;
				if(!DSML_CONTEXT.session) { DSML_CONTEXT.session++; }
				else { DSML_DEBUG_EMPTY_CALL(); }
				DSML_CONTEXT.session_data.session = DSML_CONTEXT.session;

				res = dsml_frame_tx_code(&DSML_CONTEXT);
				if(res == DSML_RESULT_OK) { res = dsml_send(&DSML_CONTEXT); }
				else { DSML_DEBUG_EMPTY_CALL(); }
			} else { DSML_DEBUG_EMPTY_CALL(); }
		}
		else
		{
			DSML_DEBUG_PRINT("invalid file size access!");
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
			DSML_CALLBACK(&DSML_CONTEXT, ERROR);
		}
	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return res;
}
#endif /* #ifndef DSML_MASTER_READ_DISABLE */

#ifndef DSML_MASTER_WRITE_DISABLE
reg dsml_remote_write(DSML_CONTEXT_ARG,
	uint16 file, uint32 nbyte, uint32 offset)
{
	reg res;
	int32 fd;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	res = DSML_RESULT_ERROR;
	
	if(file >= DSML_CONTEXT.dir_size)
	{
		DSML_DEBUG_PRINT("invalid file access!");
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
		DSML_CALLBACK(&DSML_CONTEXT, ERROR);
	}
	else if(!(DSML_CONTEXT.status & DSML_STATUS_BUSY))
	{
		fd = dsml_local_file_size(&DSML_CONTEXT, file);

		DSML_ASSERT(((uint64)nbyte + (uint64)offset) <
			UINT64_C(0x7fffffff), "file size not supported");

		if((fd >= INT32_C(0)) && ((uint32)fd >= (nbyte + offset)))
		{
			fd = dsml_local_file_open(&DSML_CONTEXT,
				file, DSML_FILE_OFLAG_READ, DSML_FILE_PID_INTERNAL);
			if(fd >= INT32_C(0))
			{
				DSML_CONTEXT.state = DSML_STATE_WRITE_INIT;

				DSML_CONTEXT.status |= DSML_STATUS_WRITE | DSML_STATUS_MASTER
					| DSML_STATUS_BUSY;

				DSML_CONTEXT.frame_tx.type_data.file_init.file = file;
				DSML_CONTEXT.frame_tx.type_data.file_init.nbyte = nbyte;
				DSML_CONTEXT.frame_tx.type_data.file_init.offset = offset;
				DSML_CONTEXT.frame_tx.user_bytes = UINT16_C(0);
				DSML_CONTEXT.frame_tx.user_buff = DSML_NULL;

				DSML_CONTEXT.session_data.type = DSML_STATE_WRITE_INIT;
				DSML_CONTEXT.session_data.cmd_type =
					DSML_STATE_CMD_SUB_TYPE_NONE;
				DSML_CONTEXT.session_data.file = file;
				DSML_CONTEXT.session_data.nbyte = nbyte;
				DSML_CONTEXT.session_data.offset = offset;
				DSML_CONTEXT.session_data.nbyte_remaining = nbyte;
				DSML_CONTEXT.session_data.offset_current = offset;
				DSML_CONTEXT.session_data.retry_count = UINT8_C(0);
				DSML_CONTEXT.session_data.sequence_number = UINT8_C(0);
				DSML_CONTEXT.session++;
				if(!DSML_CONTEXT.session) { DSML_CONTEXT.session++; }
				else { DSML_DEBUG_EMPTY_CALL(); }
				DSML_CONTEXT.session_data.session = DSML_CONTEXT.session;

				res = dsml_frame_tx_code(&DSML_CONTEXT);
				if(res == DSML_RESULT_OK) { res = dsml_send(&DSML_CONTEXT); }
				else { DSML_DEBUG_EMPTY_CALL(); }
			} else { DSML_DEBUG_EMPTY_CALL(); }
		}
		else
		{
			DSML_DEBUG_PRINT("invalid file size access!");
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_EINVAL);
			DSML_CALLBACK(&DSML_CONTEXT, ERROR);
		}
	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_FUNCTION_END();
	return res;
}
#endif /* #ifndef DSML_MASTER_WRITE_DISABLE */

#ifndef DSML_MASTER_READ_DISABLE
reg dsml_remote_read_file(DSML_CONTEXT_ARG, uint16 file)
{
	reg res;
	int32 nbyte;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);
	res = DSML_RESULT_ERROR;
	nbyte = dsml_local_file_size(&DSML_CONTEXT, file);
	if(nbyte >= INT32_C(0))
	{ res = dsml_remote_read(&DSML_CONTEXT, file, nbyte, UINT32_C(0)); }
	else { DSML_DEBUG_EMPTY_CALL(); }
	DSML_FUNCTION_END();
	return res;
}
#endif /* #ifndef DSML_MASTER_READ_DISABLE */

#ifndef DSML_MASTER_WRITE_DISABLE
reg dsml_remote_write_file(DSML_CONTEXT_ARG, uint16 file)
{
	reg res;
	int32 nbyte;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);
	res = DSML_RESULT_ERROR;
	nbyte = dsml_local_file_size(&DSML_CONTEXT, file);
	if(nbyte >= INT32_C(0))
	{ res = dsml_remote_write(&DSML_CONTEXT, file, nbyte, UINT32_C(0)); }
	else { DSML_DEBUG_EMPTY_CALL(); }
	DSML_FUNCTION_END();
	return res;
}
#endif /* #ifndef DSML_MASTER_WRITE_DISABLE */

reg dsml_callback(DSML_CONTEXT_ARG, reg event)
{
	reg res;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);
	DSML_DEBUG_PRINT("USER CALLBACK");
	DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.callback);
	res = (*DSML_CONTEXT.callback)(&DSML_CONTEXT, event);
	DSML_FUNCTION_END();
	return res;
}

#ifndef DSML_MASTER_DISABLE
DSML_STATIC void dsml_master_task(DSML_CONTEXT_ARG)
{
	reg res;
	int32 nbyte;
	int32 fd;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	DSML_ASSERT(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_ACK,
		"master task can receive only ACK frames");
	
	switch(DSML_CONTEXT.state)
	{
#ifndef DSML_MASTER_CMD_DISABLE
	case DSML_STATE_CMD:
		if(DSML_CONTEXT.frame_rx.type_data.ack.type == DSML_FRAME_TYPE_CMD)
		{
			DSML_CONTEXT.state = DSML_STATE_CMD_END;

			DSML_CONTEXT.frame_tx.type_data.cmd_end.cmd_type =
				DSML_CONTEXT.session_data.cmd_type;
			DSML_CONTEXT.frame_tx.type_data.cmd_end.file =
				DSML_CONTEXT.session_data.file;
			DSML_CONTEXT.frame_tx.user_bytes =
				DSML_CONTEXT.session_data.nbyte;
			DSML_ASSERT(DSML_FRAME_SIZE(cmd) == DSML_FRAME_SIZE(cmd_end),
				"buffer data are stored in the frame_tx!");
			DSML_CONTEXT.frame_tx.user_buff =
				(void*)(((uint8*)DSML_CONTEXT.frame_tx.buff)
					+ DSML_FRAME_SIZE(header) + DSML_FRAME_SIZE(cmd_end));

			DSML_CONTEXT.session_data.type = DSML_STATE_CMD_END;
			DSML_CONTEXT.session_data.cmd_type =
				DSML_CONTEXT.session_data.cmd_type;
			DSML_CONTEXT.session_data.sequence_number++;

			res = dsml_frame_tx_code(&DSML_CONTEXT);
			if(res == DSML_RESULT_OK) { dsml_send(&DSML_CONTEXT); }
			else { DSML_DEBUG_EMPTY_CALL(); }
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;	
	case DSML_STATE_CMD_END:
		if(DSML_CONTEXT.frame_rx.type_data.ack.type ==
			DSML_FRAME_TYPE_CMD_END)
		{
			dsml_send_idle(&DSML_CONTEXT);

			DSML_CALLBACK(&DSML_CONTEXT, CMD_END);
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;
#endif /* #ifndef DSML_MASTER_CMD_DISABLE */
#ifndef DSML_MASTER_READ_DISABLE
	case DSML_STATE_READ_INIT:
		if(DSML_CONTEXT.frame_rx.type_data.ack.type ==
			DSML_FRAME_TYPE_READ_INIT)
		{
			DSML_CONTEXT.state = DSML_STATE_READ_DATA;

			DSML_CONTEXT.frame_tx.type_data.file_data.file =
				DSML_CONTEXT.session_data.file;
			DSML_CONTEXT.frame_tx.type_data.file_data.nbyte =
				DSML_CONTEXT.session_data.nbyte_remaining;
			DSML_CONTEXT.frame_tx.type_data.file_data.offset =
				DSML_CONTEXT.session_data.offset_current;
			DSML_CONTEXT.frame_tx.user_bytes = UINT16_C(0);
			DSML_CONTEXT.frame_tx.user_buff = DSML_NULL;

			DSML_CONTEXT.session_data.type = DSML_CONTEXT.state;
			DSML_CONTEXT.session_data.cmd_type =
				DSML_STATE_CMD_SUB_TYPE_NONE;
			DSML_CONTEXT.session_data.sequence_number++;

			res = dsml_frame_tx_code(&DSML_CONTEXT);
			if(res == DSML_RESULT_OK) { dsml_send(&DSML_CONTEXT); }
			else { DSML_DEBUG_EMPTY_CALL(); }
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;
	case DSML_STATE_READ_DATA:
		if(DSML_CONTEXT.frame_rx.type_data.ack.type ==
			DSML_FRAME_TYPE_READ_DATA)
		{
			if(DSML_CONTEXT.frame_rx.user_bytes != UINT16_C(0))
			{
				nbyte = dsml_local_file_write(&DSML_CONTEXT,
					DSML_CONTEXT.session_data.file,
					DSML_CONTEXT.frame_rx.user_buff,
					(uint32)DSML_CONTEXT.frame_rx.user_bytes,
					DSML_CONTEXT.session_data.offset_current,
					DSML_FILE_PID_INTERNAL);
			} else { nbyte = INT32_C(0); }

			if(nbyte == (int32)DSML_CONTEXT.frame_rx.user_bytes)
			{
				DSML_CONTEXT.session_data.nbyte_remaining -=
					(uint32)DSML_CONTEXT.frame_rx.user_bytes;
				DSML_CONTEXT.session_data.offset_current +=
					(uint32)DSML_CONTEXT.frame_rx.user_bytes;

				if(DSML_CONTEXT.session_data.nbyte_remaining > UINT32_C(0))
				{
					DSML_CONTEXT.frame_tx.type_data.file_data.file =
						DSML_CONTEXT.session_data.file;
					DSML_CONTEXT.frame_tx.type_data.file_data.nbyte =
						DSML_CONTEXT.session_data.nbyte_remaining;
					DSML_CONTEXT.frame_tx.type_data.file_data.offset =
						DSML_CONTEXT.session_data.offset_current;
				}
				else
				{
					DSML_CONTEXT.state = DSML_STATE_READ_END;

					DSML_CONTEXT.frame_tx.type_data.file_end.file =
						DSML_CONTEXT.session_data.file;
				}

				DSML_CONTEXT.session_data.type = DSML_CONTEXT.state;
				DSML_CONTEXT.session_data.cmd_type =
					DSML_STATE_CMD_SUB_TYPE_NONE;
				DSML_CONTEXT.session_data.sequence_number++;

				res = dsml_frame_tx_code(&DSML_CONTEXT);
				if(res == DSML_RESULT_OK) { dsml_send(&DSML_CONTEXT); }
				else { DSML_DEBUG_EMPTY_CALL(); }
			}
			else
			{
				dsml_send_abort(&DSML_CONTEXT,
					DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;
	case DSML_STATE_READ_END:
		if(DSML_CONTEXT.frame_rx.type_data.ack.type ==
			DSML_FRAME_TYPE_READ_END)
		{
			fd = dsml_local_file_close(&DSML_CONTEXT,
				DSML_CONTEXT.session_data.file, DSML_FILE_PID_INTERNAL);
			if(fd < INT32_C(0))
			{
				dsml_send_abort(&DSML_CONTEXT,
					DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
			else
			{
				dsml_send_idle(&DSML_CONTEXT);

				DSML_CALLBACK(&DSML_CONTEXT, READ_END);
			}
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;
#endif /* #ifndef DSML_MASTER_READ_DISABLE */
#ifndef DSML_MASTER_WRITE_DISABLE
	case DSML_STATE_WRITE_INIT:
		if(DSML_CONTEXT.frame_rx.type_data.ack.type ==
			DSML_FRAME_TYPE_WRITE_INIT)
		{
			DSML_CONTEXT.state = DSML_STATE_WRITE_DATA;
			DSML_CONTEXT.frame_rx.type_data.ack.type =
				DSML_FRAME_TYPE_WRITE_DATA;
			/* NOTE: we fall through to the next case !!! */
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			break;
		}
	case DSML_STATE_WRITE_DATA:
		if(DSML_CONTEXT.frame_rx.type_data.ack.type ==
			DSML_FRAME_TYPE_WRITE_DATA)
		{
			if(DSML_CONTEXT.session_data.nbyte_remaining > UINT32_C(0))
			{
				DSML_CONTEXT.frame_tx.user_buff =
					(void*)(((uint8*)DSML_CONTEXT.frame_tx.buff)
						+ DSML_FRAME_SIZE(header)
						+ DSML_FRAME_SIZE(file_data));
				DSML_CONTEXT.frame_tx.user_bytes =
					DSML_CONTEXT.frame_tx.buff_size
						- DSML_FRAME_SIZE(header)
						- DSML_FRAME_SIZE(file_data);

				if(DSML_CONTEXT.session_data.nbyte_remaining <
					(uint32)DSML_CONTEXT.frame_tx.user_bytes)
				{
					DSML_CONTEXT.frame_tx.user_bytes =
						DSML_CONTEXT.session_data.nbyte_remaining;
				} else { DSML_DEBUG_EMPTY_CALL(); }

				if(DSML_CONTEXT.frame_tx.user_bytes != UINT16_C(0))
				{
					nbyte = dsml_local_file_read(&DSML_CONTEXT,
						DSML_CONTEXT.session_data.file,
						DSML_CONTEXT.frame_tx.user_buff,
						(uint32)DSML_CONTEXT.frame_tx.user_bytes,
						DSML_CONTEXT.session_data.offset_current,
						DSML_FILE_PID_INTERNAL);
				} else { nbyte = INT32_C(0); }

				if((nbyte >= INT32_C(0))
					&& (nbyte == (int32)DSML_CONTEXT.frame_tx.user_bytes))
				{
					DSML_CONTEXT.frame_tx.type_data.file_data.file
						= DSML_CONTEXT.session_data.file;
					DSML_CONTEXT.frame_tx.type_data.file_data.nbyte
						= DSML_CONTEXT.session_data.nbyte_remaining;
					DSML_CONTEXT.frame_tx.type_data.file_data.offset
						= DSML_CONTEXT.session_data.offset_current;

					DSML_CONTEXT.session_data.type = DSML_STATE_WRITE_DATA;
					DSML_CONTEXT.session_data.cmd_type
						= DSML_STATE_CMD_SUB_TYPE_NONE;
					DSML_CONTEXT.session_data.sequence_number++;

			 		DSML_CONTEXT.session_data.nbyte_remaining -=
						DSML_CONTEXT.frame_tx.user_bytes;
					DSML_CONTEXT.session_data.offset_current +=
						DSML_CONTEXT.frame_tx.user_bytes;

					res = dsml_frame_tx_code(&DSML_CONTEXT);
					if(res == DSML_RESULT_OK) { dsml_send(&DSML_CONTEXT); }
					else { DSML_DEBUG_EMPTY_CALL(); }
				}
				else
				{
					dsml_send_abort(&DSML_CONTEXT,
						DSML_LAST_ERROR_GET(&DSML_CONTEXT));
				}
			}
			else
			{
				DSML_CONTEXT.state = DSML_STATE_WRITE_END;

				DSML_CONTEXT.frame_tx.type_data.file_end.file =
					DSML_CONTEXT.session_data.file;
				DSML_CONTEXT.frame_tx.user_bytes = UINT16_C(0);
				DSML_CONTEXT.frame_tx.user_buff = DSML_NULL;

				DSML_CONTEXT.session_data.type = DSML_STATE_WRITE_END;
				DSML_CONTEXT.session_data.cmd_type =
					DSML_STATE_CMD_SUB_TYPE_NONE;
				DSML_CONTEXT.session_data.sequence_number++;

				res = dsml_frame_tx_code(&DSML_CONTEXT);
				if(res == DSML_RESULT_OK) { dsml_send(&DSML_CONTEXT); }
				else { DSML_DEBUG_EMPTY_CALL(); }
			}
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;
	case DSML_STATE_WRITE_END:
		if(DSML_CONTEXT.frame_rx.type_data.ack.type ==
			DSML_FRAME_TYPE_WRITE_END)
		{
			fd = dsml_local_file_close(&DSML_CONTEXT,
				DSML_CONTEXT.session_data.file, DSML_FILE_PID_INTERNAL);
			if(fd < INT32_C(0))
			{
				dsml_send_abort(&DSML_CONTEXT,
					DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
			else
			{
				dsml_send_idle(&DSML_CONTEXT);

				DSML_CALLBACK(&DSML_CONTEXT, WRITE_END);
			}
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;
#endif /* #ifndef DSML_MASTER_WRITE_DISABLE */
	default:
		DSML_DEBUG_PRINT("protocol error!");
		/* the frame checksum should be okay. we have an invalid frame! */
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		break;
	}

	DSML_FUNCTION_END();
}
#endif /* #ifndef DSML_MASTER_DISABLE */

#ifndef DSML_SLAVE_DISABLE
DSML_STATIC void dsml_slave_task(DSML_CONTEXT_ARG)
{
	int32 fd;
	int32 nbyte;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);
	
	switch(DSML_CONTEXT.state)
	{
#ifndef DSML_SLAVE_CMD_DISABLE
	case DSML_STATE_CMD:
		/*
			if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_CMD)
				the master may have not received our first ACK!
				but we will resend in the main task!
		*/

		/* request for execute */
		if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_CMD_END)
		{
			fd = INT32_C(0);
			if(DSML_CONTEXT.session_data.file != DSML_CMD_FILE_INVALID)
			{
				fd = dsml_local_file_close(&DSML_CONTEXT,
					DSML_CONTEXT.session_data.file, DSML_FILE_PID_REMOTE);
			} else { DSML_DEBUG_EMPTY_CALL(); }

			if(fd >= INT32_C(0))
			{
				dsml_local_cmd(&DSML_CONTEXT, DSML_CONTEXT.session_data.file,
					DSML_CONTEXT.session_data.cmd_type,
					DSML_CONTEXT.frame_rx.user_buff,
					DSML_CONTEXT.frame_rx.user_bytes,
					DSML_FILE_PID_REMOTE);

				DSML_CONTEXT.state = DSML_STATE_CMD_END;
				dsml_send_ack(&DSML_CONTEXT,
					DSML_NULL, UINT16_C(0),
					DSML_LAST_ERROR_GET(&DSML_CONTEXT));

				DSML_CALLBACK(&DSML_CONTEXT, CMD_END);
			}
			else
			{
				dsml_send_nack(&DSML_CONTEXT,
					DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_nack(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;
#endif /* #ifndef DSML_SLAVE_CMD_DISABLE */
#ifndef DSML_SLAVE_READ_DISABLE
	case DSML_STATE_READ_INIT:
		/*
			if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_READ_INIT)
				the master may have not received our first ACK!
				but we will resend in the main task!
		*/
		if(DSML_CONTEXT.frame_rx.header.type != DSML_FRAME_TYPE_READ_DATA)
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_nack(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			break;
		}
		else
		{
			DSML_CONTEXT.state = DSML_STATE_READ_DATA;
			/* NOTE: we fall through to the next case !!! */
		}
	case DSML_STATE_READ_DATA:
		if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_READ_DATA)
		{
			DSML_ASSERT(DSML_CONTEXT.session_data.file ==
				DSML_CONTEXT.frame_rx.type_data.file_data.file,
				"protocol error");

			DSML_CONTEXT.session_data.nbyte_remaining =
				DSML_CONTEXT.frame_rx.type_data.file_data.nbyte;
			DSML_CONTEXT.session_data.offset_current =
				DSML_CONTEXT.frame_rx.type_data.file_data.offset;

			DSML_CONTEXT.frame_tx.user_buff =
				(void*)(((uint8*)DSML_CONTEXT.frame_tx.buff)
					+ DSML_FRAME_SIZE(header)
					+ DSML_FRAME_SIZE(ack));
			DSML_CONTEXT.frame_tx.user_bytes =
				DSML_CONTEXT.frame_tx.buff_size
					- DSML_FRAME_SIZE(header)
					- DSML_FRAME_SIZE(ack);

			if(DSML_CONTEXT.session_data.nbyte_remaining <
				(uint32)DSML_CONTEXT.frame_tx.user_bytes)
			{
				DSML_CONTEXT.frame_tx.user_bytes =
					DSML_CONTEXT.session_data.nbyte_remaining;
			} else { DSML_DEBUG_EMPTY_CALL(); }

			if(DSML_CONTEXT.frame_tx.user_bytes != UINT16_C(0))
			{
				nbyte = dsml_local_file_read(&DSML_CONTEXT,
					DSML_CONTEXT.session_data.file,
					DSML_CONTEXT.frame_tx.user_buff,
					(uint32)DSML_CONTEXT.frame_tx.user_bytes,
					DSML_CONTEXT.session_data.offset_current,
					DSML_FILE_PID_REMOTE);
			} else { nbyte = INT32_C(0); }

			if((nbyte >= INT32_C(0))
				&& (nbyte == (int32)DSML_CONTEXT.frame_tx.user_bytes))
			{
				dsml_send_ack(&DSML_CONTEXT,
					DSML_CONTEXT.frame_tx.user_buff,
					DSML_CONTEXT.frame_tx.user_bytes,
					INT32_C(0));
			}
			else
			{
				dsml_send_nack(&DSML_CONTEXT,
					DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
			break;
		}
		else if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_READ_END)
		{
			DSML_CONTEXT.state = DSML_STATE_READ_END;
			/* NOTE: we fall through to the next case !!! */
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_nack(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			break;
		}
	case DSML_STATE_READ_END:
		if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_READ_END)
		{
			fd = dsml_local_file_close(&DSML_CONTEXT,
				DSML_CONTEXT.session_data.file, DSML_FILE_PID_REMOTE);
			if(fd < INT32_C(0))
			{
				dsml_send_nack(&DSML_CONTEXT,
					DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
			else
			{
				dsml_send_ack(&DSML_CONTEXT,
					DSML_NULL, UINT16_C(0),
					INT32_C(0));

				DSML_CALLBACK(&DSML_CONTEXT, READ_END);
			}
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_nack(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;
#endif /* #ifndef DSML_SLAVE_READ_DISABLE */
#ifndef DSML_SLAVE_WRITE_DISABLE
	case DSML_STATE_WRITE_INIT:
		/*
			if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_WRITE_INIT)
				the master may have not received our first ACK!
				but we will resend in the main task!
		*/
		if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_WRITE_DATA)
		{
			DSML_CONTEXT.state = DSML_STATE_WRITE_DATA;
			/* NOTE: we fall through to the next case !!! */
		}
		else if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_WRITE_END)
		{
			DSML_CONTEXT.state = DSML_STATE_WRITE_DATA;
			DSML_CONTEXT.frame_rx.header.type = DSML_FRAME_TYPE_WRITE_END;
			/* NOTE: we fall through to the next case !!! */
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_nack(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			break;
		}
	case DSML_STATE_WRITE_DATA:
		if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_WRITE_DATA)
		{
			DSML_ASSERT(DSML_CONTEXT.session_data.file ==
				DSML_CONTEXT.frame_rx.type_data.file_data.file,
				"protocol error");

			DSML_CONTEXT.session_data.nbyte_remaining =
				DSML_CONTEXT.frame_rx.type_data.file_data.nbyte;
			DSML_CONTEXT.session_data.offset_current =
				DSML_CONTEXT.frame_rx.type_data.file_data.offset;

			/*
				NOTE: DSML_CONTEXT.frame_rx.user_buff
				& DSML_CONTEXT.frame_rx.user_bytes should be set here!
			*/

			if(DSML_CONTEXT.frame_rx.user_bytes != UINT16_C(0))
			{
				nbyte = dsml_local_file_write(&DSML_CONTEXT,
					DSML_CONTEXT.session_data.file,
					DSML_CONTEXT.frame_rx.user_buff,
					(uint32)DSML_CONTEXT.frame_rx.user_bytes,
					DSML_CONTEXT.session_data.offset_current,
					DSML_FILE_PID_REMOTE);
			} else { nbyte = INT32_C(0); }

			if((nbyte >= INT32_C(0))
				&& (nbyte == (int32)DSML_CONTEXT.frame_rx.user_bytes))
			{
				dsml_send_ack(&DSML_CONTEXT,
					DSML_NULL, UINT16_C(0),
					INT32_C(0));
			}
			else
			{
				dsml_send_nack(&DSML_CONTEXT,
					DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
			break;
		}
		else if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_WRITE_END)
		{
			DSML_CONTEXT.state = DSML_STATE_WRITE_END;
			/* NOTE: we fall through to the next case !!! */
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_nack(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			break;
		}
	case DSML_STATE_WRITE_END:
		if(DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_WRITE_END)
		{
			fd = dsml_local_file_close(&DSML_CONTEXT,
				DSML_CONTEXT.session_data.file, DSML_FILE_PID_REMOTE);
			if(fd < INT32_C(0))
			{
				dsml_send_nack(&DSML_CONTEXT,
					DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
			else
			{
				dsml_send_ack(&DSML_CONTEXT,
					DSML_NULL, UINT16_C(0),
					INT32_C(0));

				DSML_CALLBACK(&DSML_CONTEXT, WRITE_END);
			}
		}
		else
		{
			DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
			dsml_send_nack(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		}
		break;
#endif /* #ifndef DSML_SLAVE_WRITE_DISABLE */
	default:
		DSML_DEBUG_PRINT("protocol error!");
		/* the frame checksum should be okay. we have an invalid frame! */
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		break;
	}

	DSML_FUNCTION_END();
}
#endif /* #ifndef DSML_SLAVE_DISABLE */

DSML_STATIC void dsml_idle_task(DSML_CONTEXT_ARG)
{
	int32 fd;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	switch(DSML_CONTEXT.frame_rx.header.type)
	{
#ifndef DSML_SLAVE_DISABLE
#ifndef DSML_SLAVE_CMD_DISABLE
	case DSML_STATE_CMD:
		DSML_DEBUG_PRINT("command request");
		
		fd = INT32_C(0);
		if(DSML_CONTEXT.frame_rx.type_data.cmd.file != DSML_CMD_FILE_INVALID)
		{
			DSML_DEBUG_PRINT("command init with !DSML_CMD_FILE_INVALID");
			
			fd = dsml_local_file_open(&DSML_CONTEXT,
				DSML_CONTEXT.frame_rx.type_data.cmd.file,
				DSML_FILE_OFLAG_WRITE,
				DSML_FILE_PID_REMOTE);
		}
		else
		{
			DSML_DEBUG_PRINT("command init with DSML_CMD_FILE_INVALID");
		}

		if(fd >= INT32_C(0))
		{
			DSML_CONTEXT.state = DSML_STATE_CMD;
			DSML_CONTEXT.status |= DSML_STATUS_CMD | DSML_STATUS_SLAVE
				| DSML_STATUS_BUSY;

			DSML_CONTEXT.session_data.cmd_type =
				DSML_CONTEXT.frame_rx.type_data.cmd.cmd_type;
			DSML_CONTEXT.session_data.file =
				DSML_CONTEXT.frame_rx.type_data.cmd.file;
/*TODO buff data??!!*/
			DSML_CONTEXT.session_data.nbyte = UINT32_C(0);
			DSML_CONTEXT.session_data.offset = UINT32_C(0);
			DSML_CONTEXT.session_data.nbyte_remaining = UINT32_C(0);
			DSML_CONTEXT.session_data.offset_current = UINT32_C(0);
			DSML_CONTEXT.session_data.retry_count = UINT8_C(0);
			DSML_CONTEXT.session_data.sequence_number =
				DSML_CONTEXT.frame_rx.header.sequence_number;
			DSML_CONTEXT.session = DSML_CONTEXT.frame_rx.header.session;
			DSML_CONTEXT.session_data.session = DSML_CONTEXT.session;

			dsml_send_ack(&DSML_CONTEXT, DSML_NULL, UINT16_C(0), INT32_C(0));

			DSML_CALLBACK(&DSML_CONTEXT, CMD_INIT);
		}
		else
		{
			dsml_send_nack(&DSML_CONTEXT, DSML_LAST_ERROR_GET(&DSML_CONTEXT));
		}
		break;
#endif /* #ifndef DSML_SLAVE_CMD_DISABLE */
#ifndef DSML_SLAVE_READ_DISABLE
	case DSML_STATE_READ_INIT:
		DSML_DEBUG_PRINT("read request");

		fd = dsml_local_file_size(&DSML_CONTEXT,
			DSML_CONTEXT.frame_rx.type_data.file_init.file);

		DSML_ASSERT(((uint64)DSML_CONTEXT.frame_rx.type_data.file_init.nbyte
				+ (uint64)DSML_CONTEXT.frame_rx.type_data.file_init.offset)
			< UINT64_C(0x7fffffff),
			"file size not supported");

		if((fd >= INT32_C(0))
			&& ((uint32)fd >= (DSML_CONTEXT.frame_rx.type_data.file_init.nbyte
				+ DSML_CONTEXT.frame_rx.type_data.file_init.offset)))
		{
			fd = dsml_local_file_open(&DSML_CONTEXT,
				DSML_CONTEXT.frame_rx.type_data.file_init.file,
				DSML_FILE_OFLAG_READ,
				DSML_FILE_PID_REMOTE);
			if(fd >= INT32_C(0))
			{
				DSML_CONTEXT.state = DSML_STATE_READ_INIT;
				DSML_CONTEXT.status |= DSML_STATUS_SLAVE
					| DSML_STATUS_READ | DSML_STATUS_BUSY;

				DSML_CONTEXT.session_data.cmd_type =
					DSML_STATE_CMD_SUB_TYPE_NONE;
				DSML_CONTEXT.session_data.file =
					DSML_CONTEXT.frame_rx.type_data.file_init.file;
				DSML_CONTEXT.session_data.nbyte =
					DSML_CONTEXT.frame_rx.type_data.file_init.nbyte;
				DSML_CONTEXT.session_data.offset =
					DSML_CONTEXT.frame_rx.type_data.file_init.offset;
				DSML_CONTEXT.session_data.nbyte_remaining =
					DSML_CONTEXT.frame_rx.type_data.file_init.nbyte;
				DSML_CONTEXT.session_data.offset_current =
					DSML_CONTEXT.frame_rx.type_data.file_init.offset;
				DSML_CONTEXT.session_data.retry_count = UINT8_C(0);
				DSML_CONTEXT.session_data.sequence_number =
					DSML_CONTEXT.frame_rx.header.sequence_number;
				DSML_CONTEXT.session = DSML_CONTEXT.frame_rx.header.session;
				DSML_CONTEXT.session_data.session = DSML_CONTEXT.session;

				dsml_send_ack(&DSML_CONTEXT,
					DSML_NULL, UINT16_C(0),
					INT32_C(0));

				DSML_CALLBACK(&DSML_CONTEXT, READ_INIT);
			}
			else
			{
				dsml_send_nack(&DSML_CONTEXT, DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
		}
		else
		{
			dsml_send_nack(&DSML_CONTEXT, DSML_LAST_ERROR_GET(&DSML_CONTEXT));
		}
		break;
#endif /* #ifndef DSML_SLAVE_READ_DISABLE */
#ifndef DSML_SLAVE_WRITE_DISABLE
	case DSML_STATE_WRITE_INIT:
		DSML_DEBUG_PRINT("write request");

		fd = dsml_local_file_size(&DSML_CONTEXT,
			DSML_CONTEXT.frame_rx.type_data.file_init.file);

		DSML_ASSERT(((uint64)DSML_CONTEXT.frame_rx.type_data.file_init.nbyte
				+ (uint64)DSML_CONTEXT.frame_rx.type_data.file_init.offset)
			< UINT64_C(0x7fffffff),
			"file size not supported");

		if((fd >= INT32_C(0))
			&& ((uint32)fd >= (DSML_CONTEXT.frame_rx.type_data.file_init.nbyte
				+ DSML_CONTEXT.frame_rx.type_data.file_init.offset)))
		{
			fd = dsml_local_file_open(&DSML_CONTEXT,
				DSML_CONTEXT.frame_rx.type_data.file_init.file,
				DSML_FILE_OFLAG_WRITE,
				DSML_FILE_PID_REMOTE);
			if(fd >= INT32_C(0))
			{
				DSML_CONTEXT.state = DSML_STATE_WRITE_INIT;
				DSML_CONTEXT.status |= DSML_STATUS_SLAVE
					| DSML_STATUS_WRITE | DSML_STATUS_BUSY;

				DSML_CONTEXT.session_data.cmd_type =
					DSML_STATE_CMD_SUB_TYPE_NONE;
				DSML_CONTEXT.session_data.file =
					DSML_CONTEXT.frame_rx.type_data.file_init.file;
				DSML_CONTEXT.session_data.nbyte =
					DSML_CONTEXT.frame_rx.type_data.file_init.nbyte;
				DSML_CONTEXT.session_data.offset =
					DSML_CONTEXT.frame_rx.type_data.file_init.offset;
				DSML_CONTEXT.session_data.nbyte_remaining =
					DSML_CONTEXT.frame_rx.type_data.file_init.nbyte;
				DSML_CONTEXT.session_data.offset_current =
					DSML_CONTEXT.frame_rx.type_data.file_init.offset;
				DSML_CONTEXT.session_data.retry_count = UINT8_C(0);
				DSML_CONTEXT.session_data.sequence_number =
					DSML_CONTEXT.frame_rx.header.sequence_number;
				DSML_CONTEXT.session = DSML_CONTEXT.frame_rx.header.session;
				DSML_CONTEXT.session_data.session = DSML_CONTEXT.session;

				dsml_send_ack(&DSML_CONTEXT,
					DSML_NULL, UINT16_C(0),
					INT32_C(0));

				DSML_CALLBACK(&DSML_CONTEXT, WRITE_INIT);
			}
			else
			{
				dsml_send_nack(&DSML_CONTEXT, DSML_LAST_ERROR_GET(&DSML_CONTEXT));
			}
		}
		else
		{
			dsml_send_nack(&DSML_CONTEXT, DSML_LAST_ERROR_GET(&DSML_CONTEXT));
		}
		break;
#endif /* #ifndef DSML_SLAVE_WRITE_DISABLE */
#endif /* #ifndef DSML_SLAVE_DISABLE */
	case DSML_STATE_IDLE:
		if(DSML_CONTEXT.frame_rx.type_data.idle.dir_magic
			!= DSML_CONTEXT.dir_magic)
		{
			DSML_CALLBACK(&DSML_CONTEXT, BAD_DIR_MAGIC);
		} else { DSML_DEBUG_EMPTY_CALL(); }

		/* be sure that master priorities are correct */
		if(DSML_CONTEXT.peer_master_priority == DSML_CONTEXT.master_priority)
		{
			dsml_send_idle(&DSML_CONTEXT);
		}
		else
		{
			DSML_CALLBACK(&DSML_CONTEXT, PEER_IDLE);

			if(!(DSML_CONTEXT.status & DSML_STATUS_BUSY))
			{
				dsml_send_idle(&DSML_CONTEXT);
			} else { DSML_DEBUG_EMPTY_CALL(); }
		}
		break;
	default:
		DSML_DEBUG_PRINT("protocol error!");
		/* the frame checksum should be okay. we have an invalid frame! */
		DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
		break;
	}

	DSML_FUNCTION_END();
}

reg dsml_force_abort(DSML_CONTEXT_ARG)
{
	reg res;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);
	res = dsml_send_abort(&DSML_CONTEXT, -1/*TODO*/);
	DSML_FUNCTION_END();
	return res;
}

void dsml_task(DSML_CONTEXT_ARG)
{
	reg res;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_ASSERT_INIT_DONE(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	DSML_DEBUG_DUMP(&DSML_CONTEXT);

	DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.receive);
	res = (*DSML_CONTEXT.receive)(&DSML_CONTEXT, &(DSML_CONTEXT.frame_rx));

	if(res == DSML_RESULT_OK)
	{
		DSML_DEBUG_PRINT("new frame received");

		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.gettime_us);
		DSML_CONTEXT.frame_rx.time_us = (*DSML_CONTEXT.gettime_us)();

		dsml_frame_rx_decode(&DSML_CONTEXT);
	}
	else
	{
		DSML_CONTEXT.frame_rx.is_valid = DSML_FALSE;
	}
	
	/* check if we are requested to abort the session */
	if((DSML_CONTEXT.frame_rx.is_valid == DSML_TRUE)
		&& (DSML_CONTEXT.frame_rx.header.type == DSML_FRAME_TYPE_ABORT))
	{
		DSML_DEBUG_PRINT("peer abort request received");

		/* TODO check for idle ?!?!? */
		dsml_close_session(&DSML_CONTEXT);

		DSML_CALLBACK(&DSML_CONTEXT, PEER_ABORT);

		dsml_send_idle(&DSML_CONTEXT); /* TODO */
	}
	else
	{
		if(0) { DSML_DEBUG_EMPTY_CALL(); }
#ifndef DSML_MASTER_DISABLE
		else if(DSML_CONTEXT.status & DSML_STATUS_MASTER)
		{
			DSML_DEBUG_PRINT("we are in master mode");

			if(DSML_CONTEXT.frame_rx.is_valid == DSML_TRUE)
			{
				res = DSML_RESULT_OK;

				/* check for arbitration */
				if((DSML_CONTEXT.frame_rx.header.type == DSML_CONTEXT.state)
					&& (DSML_FALSE
#ifndef DSML_MASTER_CMD_DISABLE
						|| (DSML_CONTEXT.state == DSML_STATE_CMD)
#endif /* #ifndef DSML_MASTER_CMD_DISABLE */
#ifndef DSML_MASTER_READ_DISABLE
						|| (DSML_CONTEXT.state == DSML_STATE_READ_INIT)
#endif /* #ifndef DSML_MASTER_READ_DISABLE */
#ifndef DSML_MASTER_WRITE_DISABLE
						|| (DSML_CONTEXT.state == DSML_STATE_WRITE_INIT)
#endif /* #ifndef DSML_MASTER_WRITE_DISABLE */
						))
				{
					res = DSML_RESULT_ERROR;
					
					if(DSML_CONTEXT.master_priority ==
						DSML_CONTEXT.peer_master_priority)
					{
						DSML_DEBUG_PRINT("dropping arbitration session");

						DSML_LAST_ERROR_SET(&DSML_CONTEXT,
							DSML_ERRNO_BAD_ARBITRATION);
						dsml_send_abort(&DSML_CONTEXT,
							DSML_ERRNO_BAD_ARBITRATION);
					}
					else if(DSML_CONTEXT.master_priority >
						DSML_CONTEXT.peer_master_priority)
					{
						DSML_DEBUG_PRINT("arbitration lost");

						dsml_close_session(&DSML_CONTEXT);

						DSML_CALLBACK(&DSML_CONTEXT, ARBITRATION_LOST);
					}
					else
					{
 						DSML_DEBUG_PRINT("arbitration win");

						DSML_CALLBACK(&DSML_CONTEXT, ARBITRATION_WIN);

						dsml_resend_last_tx_frame(&DSML_CONTEXT);
					}
				} else { DSML_DEBUG_EMPTY_CALL(); }

				if(res == DSML_RESULT_OK)
				{
					if(DSML_CONTEXT.frame_rx.header.session ==
							DSML_CONTEXT.session_data.session)
					{
						if(DSML_CONTEXT.frame_rx.header.sequence_number ==
								DSML_CONTEXT.frame_tx.header.sequence_number)
						{
							/*
								the master can receive only ACK or NACK!
								ABORT is handled globaly!
							*/
							if((DSML_CONTEXT.frame_rx.header.type ==
									DSML_FRAME_TYPE_ACK))
							{
								dsml_master_task(&DSML_CONTEXT);
							}
							else if((DSML_CONTEXT.frame_rx.header.type ==
									DSML_FRAME_TYPE_NACK))
							{
								DSML_CALLBACK(&DSML_CONTEXT, NACK);
								
								dsml_send_idle(&DSML_CONTEXT);
							}
							else if((DSML_CONTEXT.state ==
									DSML_STATE_WAIT_FOR_IDLE)
								&& (DSML_CONTEXT.frame_rx.header.type ==
									DSML_FRAME_TYPE_IDLE))
							{
								DSML_DEBUG_PRINT("closing session");
								dsml_close_session(&DSML_CONTEXT);
								dsml_idle_task(&DSML_CONTEXT);
							}
							else
							{
								DSML_LAST_ERROR_SET(&DSML_CONTEXT,
									DSML_ERRNO_WRONG_FRAME);
								dsml_send_abort(&DSML_CONTEXT,
									DSML_ERRNO_WRONG_FRAME);
							}
						}
						else
						{
							DSML_DEBUG_PRINT("resending - "
								"bad sequence slave response");

							dsml_resend_last_tx_frame(&DSML_CONTEXT);
						}
					}
					else if(DSML_CONTEXT.frame_rx.header.type ==
						DSML_FRAME_TYPE_IDLE)
					{
						DSML_DEBUG_PRINT("ignoring idle frame");

						DSML_CONTEXT.session_data.retry_count++;
						if(DSML_CONTEXT.session_data.retry_count >
							DSML_CONTEXT.retry_max)
						{
							DSML_DEBUG_PRINT("aborting - session timeout");

							DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_TIMEOUT);
							dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_TIMEOUT);
							DSML_CALLBACK(&DSML_CONTEXT, TIMEOUT);
						} else { DSML_DEBUG_EMPTY_CALL(); }
					}
					else
					{
						DSML_DEBUG_PRINT("aborting - "
							"bad session slave response");

						DSML_LAST_ERROR_SET(&DSML_CONTEXT,
							DSML_ERRNO_WRONG_FRAME);
						dsml_send_abort(&DSML_CONTEXT,
							DSML_ERRNO_WRONG_FRAME);
					}
				} else { DSML_DEBUG_EMPTY_CALL(); }
			}
			else
			{
				if(((*DSML_CONTEXT.gettime_us)()
					- DSML_CONTEXT.frame_tx.time_us) > DSML_CONTEXT.timeout_us)
				{
					DSML_CONTEXT.session_data.retry_count++;
					if(DSML_CONTEXT.session_data.retry_count >
						DSML_CONTEXT.retry_max)
					{
						DSML_DEBUG_PRINT("aborting - session timeout");

						DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_TIMEOUT);
						dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_TIMEOUT);
						DSML_CALLBACK(&DSML_CONTEXT, TIMEOUT);
					}
					else
					{
						DSML_DEBUG_PRINT("resending - retry timeout");
						dsml_resend_last_tx_frame(&DSML_CONTEXT);
					}
				} else { /* wait */ DSML_DEBUG_EMPTY_CALL(); }
			}
		}
#endif /* #ifndef DSML_MASTER_DISABLE */
#ifndef DSML_SLAVE_DISABLE
		else if(DSML_CONTEXT.status & DSML_STATUS_SLAVE)
		{
			DSML_DEBUG_PRINT("we are in slave mode");

			if(DSML_CONTEXT.frame_rx.is_valid == DSML_TRUE)
			{
				if((DSML_CONTEXT.frame_rx.header.session ==
						DSML_CONTEXT.session_data.session)
					&& (DSML_CONTEXT.frame_rx.header.sequence_number ==
						DSML_CONTEXT.frame_tx.header.sequence_number))
				{
					DSML_DEBUG_PRINT("resending - last frame re-requested");
					
					dsml_resend_last_tx_frame(&DSML_CONTEXT);
				}
				else if((DSML_CONTEXT.frame_rx.header.session ==
						DSML_CONTEXT.session_data.session)
					&& (DSML_CONTEXT.frame_rx.header.sequence_number ==
						(DSML_CONTEXT.frame_tx.header.sequence_number
							+ UINT8_C(1))))
				{
					dsml_slave_task(&DSML_CONTEXT);
				}
				else if((DSML_CONTEXT.state == DSML_STATE_WAIT_FOR_IDLE)
					&& (DSML_CONTEXT.frame_rx.header.type ==
						DSML_FRAME_TYPE_IDLE))
				{
					DSML_DEBUG_PRINT("closing session");
					dsml_close_session(&DSML_CONTEXT);
					dsml_idle_task(&DSML_CONTEXT);
				}
				else
				{
					DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
					dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_WRONG_FRAME);
				}
			}
			else
			{
				if(((*DSML_CONTEXT.gettime_us)()
						- DSML_CONTEXT.frame_tx.time_us)
					> DSML_CONTEXT.timeout_us)
				{
					DSML_CONTEXT.session_data.retry_count++;
					if(DSML_CONTEXT.session_data.retry_count >
						DSML_CONTEXT.retry_max)
					{
						DSML_DEBUG_PRINT("aborting - session timeout");

						DSML_LAST_ERROR_SET(&DSML_CONTEXT, DSML_ERRNO_TIMEOUT);
						dsml_send_abort(&DSML_CONTEXT, DSML_ERRNO_TIMEOUT);
						DSML_CALLBACK(&DSML_CONTEXT, TIMEOUT);
					}
					else
					{
						DSML_CONTEXT.frame_tx.time_us =
							(*DSML_CONTEXT.gettime_us)();
					}
				} else { /* wait */ DSML_DEBUG_EMPTY_CALL(); }
			}
		}
#endif /* #ifndef DSML_SLAVE_DISABLE */
		else /* idle */
		{
			DSML_DEBUG_PRINT("we are in idle mode");

			DSML_ASSERT(DSML_CONTEXT.status & DSML_STATUS_IDLE,
				"should not happen");
	
			if(DSML_CONTEXT.frame_rx.is_valid == DSML_TRUE)
			{
				dsml_idle_task(&DSML_CONTEXT);
			}
			else
			{
				if(((*DSML_CONTEXT.gettime_us)()
					- DSML_CONTEXT.frame_tx.time_us) > DSML_CONTEXT.timeout_us)
				{
					DSML_CONTEXT.session_data.retry_count++;
					if(DSML_CONTEXT.session_data.retry_count >
						DSML_CONTEXT.retry_max)
					{
						DSML_DEBUG_PRINT("we lost connection");

						DSML_CONTEXT.session_data.retry_count = UINT8_C(0);
						DSML_LAST_ERROR_SET(&DSML_CONTEXT,
							DSML_ERRNO_CONNECTION_LOST);
						DSML_CALLBACK(&DSML_CONTEXT, CONNECTION_LOST);
					}
					else if(!DSML_CONTEXT.session_data.retry_count)
					{
						DSML_CALLBACK(&DSML_CONTEXT, IDLE);

						if(!(DSML_CONTEXT.status & DSML_STATUS_BUSY))
						{
							DSML_DEBUG_PRINT("sending idle frame"
								" to keep connection open");

							dsml_send_idle(&DSML_CONTEXT);
						} else { DSML_DEBUG_EMPTY_CALL(); }
					}
					else
					{
						dsml_send_idle(&DSML_CONTEXT);
					}
				} else { /* wait */ DSML_DEBUG_EMPTY_CALL(); }
			}
		}
	}

	DSML_CONTEXT.frame_rx.is_valid = DSML_FALSE;

	DSML_DEBUG_DUMP(&DSML_CONTEXT);
	DSML_FUNCTION_END();
}

reg dsml_load(DSML_CONTEXT_ARG)
{
	reg res;

	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	if(DSML_CONTEXT.status & DSML_STATUS_INIT)
	{
		DSML_CALLBACK(&DSML_CONTEXT, RELOAD);
		dsml_unload(&DSML_CONTEXT);
	}
	else
	{
		DSML_CALLBACK(&DSML_CONTEXT, LOAD);
	}

	DSML_CONTEXT.session = UINT16_C(0);
	DSML_CONTEXT.session_data.file = DSML_CMD_FILE_INVALID;
	DSML_CONTEXT.state = DSML_STATE_IDLE;
	DSML_CONTEXT.status = DSML_STATUS_INIT | DSML_STATUS_IDLE;

	DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.load);
	res = (*DSML_CONTEXT.load)(&DSML_CONTEXT);

	DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.gettime_us);

	DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.frame_tx.buff);
	DSML_ASSERT(DSML_CONTEXT.frame_tx.buff_size >= dsml_frame_buff_size_min(),
		"tx buffer is too small");
	DSML_CONTEXT.frame_tx.user_bytes = UINT16_C(0);
	DSML_CONTEXT.frame_tx.user_buff = DSML_NULL;
	DSML_CONTEXT.frame_tx.is_valid = DSML_FALSE;
	DSML_CONTEXT.frame_tx.time_us = (*DSML_CONTEXT.gettime_us)();

	DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.frame_rx.buff);
	DSML_ASSERT(DSML_CONTEXT.frame_rx.buff_size >= dsml_frame_buff_size_min(),
		"rx buffer is too small");
	DSML_CONTEXT.frame_rx.user_bytes = UINT16_C(0);
	DSML_CONTEXT.frame_rx.user_buff = DSML_NULL;
	DSML_CONTEXT.frame_rx.is_valid = DSML_FALSE;
	DSML_CONTEXT.frame_rx.time_us = (*DSML_CONTEXT.gettime_us)();

	if(res == DSML_RESULT_OK)
	{
		DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.rand);
		DSML_CONTEXT.master_priority = (*DSML_CONTEXT.rand)();

		DSML_CALLBACK(&DSML_CONTEXT, LOAD_DONE);
	}
	else
	{
		DSML_CONTEXT.status = DSML_STATUS_INIT | DSML_STATUS_FATAL;
		DSML_CALLBACK(&DSML_CONTEXT, FATAL);
	}

	DSML_FUNCTION_END();
	return res;
}

void dsml_unload(DSML_CONTEXT_ARG)
{
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(&DSML_CONTEXT);
	DSML_LAST_ERROR_CLEAR(&DSML_CONTEXT);

	if(DSML_CONTEXT.status & DSML_STATUS_INIT)
	{
		dsml_close_session(&DSML_CONTEXT);
	} else { DSML_DEBUG_EMPTY_CALL(); }

	DSML_CONTEXT.status = DSML_STATUS_NONE;
	DSML_CONTEXT.state = DSML_STATE_NONE;

	DSML_ASSERT_POINTER_CHECK(DSML_CONTEXT.unload);
	(*DSML_CONTEXT.unload)(&DSML_CONTEXT);

	DSML_CALLBACK(&DSML_CONTEXT, UNLOAD);

	DSML_FUNCTION_END();
}
