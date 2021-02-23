/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifndef DSML_SCORE_CORE_H
#define DSML_SCORE_CORE_H

#include <dsml/score/types.h>

#define DSML_PROTOCOL_VERSION		UINT8_C(0x01)

#ifdef DSML_CONFIG_FILE
#include DSML_CONFIG_FILE
#else /* #ifdef DSML_CONFIG_FILE */
#include <dsml/score/config_default.h>
#endif /* #ifdef DSML_CONFIG_FILE */

/* NOTE: post-config checks! */
#if defined(DSML_MASTER_DISABLE) && defined(DSML_SLAVE_DISABLE)
#error "don't use DSML_MASTER_DISABLE and DSML_SLAVE_DISABLE simultaneously!"
#endif /* #if defined(DSML_MASTER_DISABLE) && defined(DSML_SLAVE_DISABLE) */
/**/
#ifdef DSML_MASTER_DISABLE
#ifndef DSML_MASTER_CMD_DISABLE
#define DSML_MASTER_CMD_DISABLE
#endif /* #ifndef DSML_MASTER_CMD_DISABLE */
#ifndef DSML_MASTER_READ_DISABLE
#define DSML_MASTER_READ_DISABLE
#endif /* #ifndef DSML_MASTER_READ_DISABLE */
#ifndef DSML_MASTER_WRITE_DISABLE
#define DSML_MASTER_WRITE_DISABLE
#endif /* #ifndef DSML_MASTER_WRITE_DISABLE */
#elif defined(DSML_MASTER_CMD_DISABLE) && defined(DSML_MASTER_READ_DISABLE) && defined(DSML_MASTER_WRITE_DISABLE)
#error "all master functionality is off"
#endif /* #ifdef DSML_MASTER_DISABLE */
/**/
#ifdef DSML_SLAVE_DISABLE
#ifndef DSML_SLAVE_CMD_DISABLE
#define DSML_SLAVE_CMD_DISABLE
#endif /* #ifndef DSML_SLAVE_CMD_DISABLE */
#ifndef DSML_SLAVE_READ_DISABLE
#define DSML_SLAVE_READ_DISABLE
#endif /* #ifndef DSML_SLAVE_READ_DISABLE */
#ifndef DSML_SLAVE_WRITE_DISABLE
#define DSML_SLAVE_WRITE_DISABLE
#endif /* #ifndef DSML_SLAVE_WRITE_DISABLE */
#elif defined(DSML_SLAVE_CMD_DISABLE) && defined(DSML_SLAVE_READ_DISABLE) && defined(DSML_SLAVE_WRITE_DISABLE)
#error "all slave functionality is off"
#endif /* #ifdef DSML_SLAVE_DISABLE */
/**/
#if defined(DSML_MASTER_CMD_DISABLE) && defined(DSML_SLAVE_CMD_DISABLE)
#define DSML_CMD_DISABLE
#endif /* #if defined(DSML_MASTER_CMD_DISABLE) && defined(DSML_SLAVE_CMD_DISABLE) */
#if defined(DSML_MASTER_READ_DISABLE) && defined(DSML_SLAVE_READ_DISABLE)
#define DSML_READ_DISABLE
#endif /* #if defined(DSML_MASTER_READ_DISABLE) && defined(DSML_SLAVE_READ_DISABLE) */
#if defined(DSML_MASTER_WRITE_DISABLE) && defined(DSML_SLAVE_WRITE_DISABLE)
#define DSML_WRITE_DISABLE
#endif /* #if defined(DSML_MASTER_WRITE_DISABLE) && defined(DSML_SLAVE_WRITE_DISABLE) */




#ifdef __cplusplus
extern "C"
{
#endif

struct dsml_tag;

#ifdef DSML_SINGLE_INSTANCE
extern struct dsml_tag DSML_SINGLE_INSTANCE;
#ifdef __GNUC__
#define DSML_CONTEXT_ARG struct dsml_tag * const __unused_d __attribute__((unused))
#else /* #ifdef __GNUC__ */
#error "define compiler specific unused attribute here"
#endif /* #ifdef __GNUC__ */
#define DSML_CONTEXT (DSML_SINGLE_INSTANCE)
#else /* #ifdef DSML_SINGLE_INSTANCE */
#define DSML_CONTEXT_ARG struct dsml_tag * const d
#define DSML_CONTEXT (*d)
#endif /* #ifdef DSML_SINGLE_INSTANCE */

struct dsml_file_tag;

/*
	Refer to POSIX interface for type chooise.
	Asumption is that we run on a <=32bit platform.
	NOTE: We don't support large files!
*/
struct dsml_file_iface_tag
{
	int32 (*open)(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, uint16 oflag);
	int32 (*close)(DSML_CONTEXT_ARG, struct dsml_file_tag * const f);
	int32 (*read)(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, void * buff, uint32 nbyte, uint32 offset);
	int32 (*write)(DSML_CONTEXT_ARG, struct dsml_file_tag * const f, const void * buff, uint32 nbyte, uint32 offset);
	int32 (*size)(DSML_CONTEXT_ARG, const struct dsml_file_tag * const f);
};

struct dsml_file_tag
{
	uint16 id;	/*!< set code and type ID here! */
	uint16 pid;
#define DSML_FILE_PID_NONE				UINT16_C(0)
#define DSML_FILE_PID_INTERNAL			UINT16_C(1)
#define DSML_FILE_PID_REMOTE			UINT16_C(2)
/**/
#define DSML_FILE_PID_USER_FIRST		UINT16_C(16)

	uint16 attributes;
#define DSML_FILE_ATTRIBUTE_NONE				UINT16_C(0x0000)
/**/
#define DSML_FILE_ATTRIBUTE_LOCAL_LOCK_ALLOW	UINT16_C(0x0001)
#define DSML_FILE_ATTRIBUTE_LOCAL_LOCK			UINT16_C(0x0002)
#define DSML_FILE_ATTRIBUTE_LOCAL_READ			UINT16_C(0x0004)
#define DSML_FILE_ATTRIBUTE_LOCAL_WRITE			UINT16_C(0x0008)
#define DSML_FILE_ATTRIBUTE_REMOTE_LOCK_ALLOW	UINT16_C(0x0010)
#define DSML_FILE_ATTRIBUTE_REMOTE_LOCK			UINT16_C(0x0020)
#define DSML_FILE_ATTRIBUTE_REMOTE_READ			UINT16_C(0x0040)
#define DSML_FILE_ATTRIBUTE_REMOTE_WRITE		UINT16_C(0x0080)
/**/
#define DSML_FILE_ATTRIBUTE_OPEN				UINT16_C(0x0100)
#define DSML_FILE_ATTRIBUTE_CORRUPT				UINT16_C(0x0200)
#define DSML_FILE_ATTRIBUTE_MODIFIED			UINT16_C(0x0400)
#define DSML_FILE_ATTRIBUTE_RESERVED_0			UINT16_C(0x0800)
/**/
#ifndef DSML_FILE_USER_ATTRIBUTES_DISABLE
#define DSML_FILE_ATTRIBUTE_USER_0				UINT16_C(0x1000)
#define DSML_FILE_ATTRIBUTE_USER_1				UINT16_C(0x2000)
#define DSML_FILE_ATTRIBUTE_USER_2				UINT16_C(0x4000)
#define DSML_FILE_ATTRIBUTE_USER_3				UINT16_C(0x8000)
#endif /* #ifndef DSML_FILE_USER_ATTRIBUTES_DISABLE */
/**/
#define DSML_FILE_ATTRIBUTE_MASK				UINT16_C(0x0fff)
#define DSML_FILE_ATTRIBUTE_MASK_USER			UINT16_C(0xf000)
/**/
#define DSML_FILE_OFLAG_READ					UINT16_C(0x0001)
#define DSML_FILE_OFLAG_WRITE					UINT16_C(0x0002)
#define DSML_FILE_OFLAG_RW						(DSML_FILE_OFLAG_READ | DSML_FILE_OFLAG_WRITE)
#define DSML_FILE_OFLAG_MASK					(DSML_FILE_OFLAG_READ | DSML_FILE_OFLAG_WRITE)

	int32 fd;

	const struct dsml_file_iface_tag * iface;

	void * userdata;	/*!< hide custom iface here (link to 'iface')! */
};

#define DSML_FRAME_TYPE_NONE		UINT8_C(0)
#define DSML_FRAME_TYPE_IDLE		UINT8_C(1)
#define DSML_FRAME_TYPE_CMD			UINT8_C(2)
#define DSML_FRAME_TYPE_CMD_END		UINT8_C(3)
#ifndef DSML_READ_DISABLE
#define DSML_FRAME_TYPE_READ_INIT	UINT8_C(4)
#define DSML_FRAME_TYPE_READ_DATA	UINT8_C(5)
#define DSML_FRAME_TYPE_READ_END	UINT8_C(6)
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
#define DSML_FRAME_TYPE_WRITE_INIT	UINT8_C(7)
#define DSML_FRAME_TYPE_WRITE_DATA	UINT8_C(8)
#define DSML_FRAME_TYPE_WRITE_END	UINT8_C(9)
#endif /* #ifndef DSML_WRITE_DISABLE */
#define DSML_FRAME_TYPE_ACK			UINT8_C(10)
#define DSML_FRAME_TYPE_NACK		UINT8_C(11)
#define DSML_FRAME_TYPE_ABORT		UINT8_C(12)
/**/
#define DSML_FRAME_TYPE_RESERVED_0	UINT8_C(13)
#define DSML_FRAME_TYPE_RESERVED_1	UINT8_C(14)
#define DSML_FRAME_TYPE_RESERVED_2	UINT8_C(15)
#define DSML_FRAME_TYPE_RESERVED_3	UINT8_C(16)
/**/
#define DSML_FRAME_TYPE_LAST		DSML_FRAME_TYPE_RESERVED_3

#define DSML_SEMICOLON_ ;

#define DSML_FRAME_LIST_ITEM_idle(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(type_data.idle, rx_tx, src, uint16, dir_magic) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.idle, rx_tx, src, uint16, master_priority) DSML_SEMICOLON_

#define DSML_FRAME_LIST_ITEM_cmd(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(type_data.cmd, rx_tx, src, uint8, cmd_type)DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.cmd, rx_tx, src, uint16, file) DSML_SEMICOLON_

#define DSML_FRAME_LIST_ITEM_cmd_end(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(type_data.cmd_end, rx_tx, src, uint8, cmd_type) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.cmd_end, rx_tx, src, uint16, file) DSML_SEMICOLON_

#define DSML_FRAME_LIST_ITEM_file_init(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(type_data.file_init, rx_tx, src, uint16, file) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.file_init, rx_tx, src, uint32, nbyte) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.file_init, rx_tx, src, uint32, offset) DSML_SEMICOLON_

#define DSML_FRAME_LIST_ITEM_file_data(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(type_data.file_data, rx_tx, src, uint16, file) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.file_data, rx_tx, src, uint32, nbyte) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.file_data, rx_tx, src, uint32, offset) DSML_SEMICOLON_
	
#define DSML_FRAME_LIST_ITEM_file_end(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(type_data.file_end, rx_tx, src, uint16, file) DSML_SEMICOLON_

#define DSML_FRAME_LIST_ITEM_ack(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(type_data.ack, rx_tx, src, uint8, type) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.ack, rx_tx, src, uint8, cmd_type) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.ack, rx_tx, src, uint16, file) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.ack, rx_tx, src, uint16, file_attrifutes) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.ack, rx_tx, src, int32, return_code) DSML_SEMICOLON_

#define DSML_FRAME_LIST_ITEM_nack(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(type_data.nack, rx_tx, src, uint8, type) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.nack, rx_tx, src, uint8, cmd_type) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.nack, rx_tx, src, uint16, file) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.nack, rx_tx, src, uint16, file_attrifutes) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(type_data.nack, rx_tx, src, int32, return_code) DSML_SEMICOLON_

#define DSML_FRAME_LIST_ITEM_abort(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(type_data.abort, rx_tx, src, int32, return_code) DSML_SEMICOLON_

#define DSML_FRAME_LIST_ITEM_header(rx_tx, src) \
	DSML_FRAME_ITEM_TOOL(header, rx_tx, src, uint16, checksum) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(header, rx_tx, src, uint8, protocol_version) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(header, rx_tx, src, uint8, session) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(header, rx_tx, src, uint8, sequence_number) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(header, rx_tx, src, uint8, type) DSML_SEMICOLON_ \
	DSML_FRAME_ITEM_TOOL(header, rx_tx, src, uint16, len) DSML_SEMICOLON_

#define DSML_FRAME_LIST_ITEM_TOOL(x, rx_tx, src) \
	DSML_FRAME_LIST_ITEM_##x(rx_tx, src)

#define DSML_FRAME_ITEM_TOOL(x, rx_tx, src, type, name) \
	type name

#define DSML_FRAME_NAME_TOOL(x) \
	dsml_frame_type_##x##_tag

#define DSML_FRAME_TOOL(frame_type, item_list) \
DSML_FRAME_NAME_TOOL(frame_type) \
{ \
	item_list \
}

struct DSML_FRAME_TOOL(idle,
	DSML_FRAME_LIST_ITEM_TOOL(idle, XXX, XXX)
);
struct DSML_FRAME_TOOL(cmd,
	DSML_FRAME_LIST_ITEM_TOOL(cmd, XXX, XXX)
);
struct DSML_FRAME_TOOL(cmd_end,
	DSML_FRAME_LIST_ITEM_TOOL(cmd_end, XXX, XXX)
);
struct DSML_FRAME_TOOL(file_init,
	DSML_FRAME_LIST_ITEM_TOOL(file_init, XXX, XXX)
);
struct DSML_FRAME_TOOL(file_data,
	DSML_FRAME_LIST_ITEM_TOOL(file_data, XXX, XXX)
);
struct DSML_FRAME_TOOL(file_end,
	DSML_FRAME_LIST_ITEM_TOOL(file_end, XXX, XXX)
);
struct DSML_FRAME_TOOL(ack,
	DSML_FRAME_LIST_ITEM_TOOL(ack, XXX, XXX)
);
struct DSML_FRAME_TOOL(nack,
	DSML_FRAME_LIST_ITEM_TOOL(nack, XXX, XXX)
);
struct DSML_FRAME_TOOL(abort,
	DSML_FRAME_LIST_ITEM_TOOL(abort, XXX, XXX)
);
struct DSML_FRAME_TOOL(header,
	DSML_FRAME_LIST_ITEM_TOOL(header, XXX, XXX)
);

union dsml_frame_type_data_tag
{
	struct DSML_FRAME_NAME_TOOL(idle)		idle;
	struct DSML_FRAME_NAME_TOOL(cmd)		cmd;
	struct DSML_FRAME_NAME_TOOL(cmd_end)	cmd_end;
	struct DSML_FRAME_NAME_TOOL(file_init)	file_init;
	struct DSML_FRAME_NAME_TOOL(file_data)	file_data;
	struct DSML_FRAME_NAME_TOOL(file_end)	file_end;
	struct DSML_FRAME_NAME_TOOL(ack)		ack;
	struct DSML_FRAME_NAME_TOOL(nack)		nack;
	struct DSML_FRAME_NAME_TOOL(abort)		abort;
};

struct dsml_frame_data_tag
{
	struct DSML_FRAME_NAME_TOOL(header) header;

	union dsml_frame_type_data_tag type_data;

	uint16 buff_size;
	uint16 buff_bytes;
	void * buff;

	uint16 user_bytes;
	void * user_buff;

	reg is_valid;
	uint32 time_us; /* TODO maybe */
};

struct dsml_session_data_tag
{
	uint8 session;
	uint8 type;
	uint8 cmd_type;
	uint16 file;

	uint32 nbyte;
	uint32 offset;

	uint32 nbyte_remaining;
	uint32 offset_current;

	uint8 retry_count;
	uint8 sequence_number;
};

struct dsml_tag
{
	reg id;

	/* NOTE: try to think about modules! */
	reg (*load)(DSML_CONTEXT_ARG);
	void (*unload)(DSML_CONTEXT_ARG);

	/* TODO: try to think about modules! - maybe hide in L0!? */
	reg (*send)(DSML_CONTEXT_ARG, const struct dsml_frame_data_tag * const f);
	reg (*receive)(DSML_CONTEXT_ARG, struct dsml_frame_data_tag * const f);

	uint16 (*checksum)(const void * buff, uint16 len);

	uint16 (*rand)(void);

	/* TODO: force application implementation!!! */
	reg (*callback)(DSML_CONTEXT_ARG, reg event);
#define DSML_CALLBACK(d, x) \
	do { \
		DSML_ASSERT_POINTER_CHECK((d)); \
		DSML_ASSERT_POINTER_CHECK((d)->callback); \
		DSML_DEBUG_PRINT("CALLBACK: "#x); \
		(*(d)->callback)((d), DSML_CALLBACK_##x); \
	} while(0)
#define DSML_CALLBACK_NONE					REG_C(0)
#define DSML_CALLBACK_LOAD					REG_C(1)
#define DSML_CALLBACK_UNLOAD				REG_C(2)
#define DSML_CALLBACK_LOAD_DONE				REG_C(3)
#define DSML_CALLBACK_RELOAD				REG_C(4)
#define DSML_CALLBACK_EXEC					REG_C(5)
#define DSML_CALLBACK_ERROR					REG_C(6)
#define DSML_CALLBACK_ERROR_SET				REG_C(7)
#define DSML_CALLBACK_FATAL					REG_C(8)
#define DSML_CALLBACK_IDLE					REG_C(9)
#define DSML_CALLBACK_PEER_IDLE				REG_C(10)
#define DSML_CALLBACK_ABORT					REG_C(11)
#define DSML_CALLBACK_PEER_ABORT			REG_C(12)
#define DSML_CALLBACK_PROTOCOL_ERROR		REG_C(13)
#define DSML_CALLBACK_INVALID_USER_CMD		REG_C(14)
#define DSML_CALLBACK_USER_CMD				REG_C(15)
#define DSML_CALLBACK_CMD_END				REG_C(16)
#define DSML_CALLBACK_CMD_INIT				REG_C(17)
#define DSML_CALLBACK_READ_INIT				REG_C(18)
#define DSML_CALLBACK_READ_END				REG_C(19)
#define DSML_CALLBACK_WRITE_INIT			REG_C(20)
#define DSML_CALLBACK_WRITE_END				REG_C(21)
#define DSML_CALLBACK_ARBITRATION_LOST		REG_C(22)
#define DSML_CALLBACK_ARBITRATION_WIN		REG_C(23)
#define DSML_CALLBACK_SESSION_END			REG_C(24)
#define DSML_CALLBACK_CONNECTION_LOST		REG_C(25)
#define DSML_CALLBACK_TIMEOUT				REG_C(26)
#define DSML_CALLBACK_BAD_DIR_MAGIC			REG_C(27)
#define DSML_CALLBACK_NACK					REG_C(28)
/**/
#define DSML_CALLBACK_USER_FIRST			REG_C(256) /*TODO*/
#define DSML_CALLBACK_USER_LAST				REG_C(1023) /*TODO*/

#ifndef DSML_ERRNO_DISABLE
	int32 errcode;
#define DSML_ERRNO_NONE					INT16_C(0)
#define DSML_ERRNO_EINVAL				INT16_C(1)
#define DSML_ERRNO_EACCES				INT16_C(2)
#define DSML_ERRNO_ETXTBSY				INT16_C(3)
#define DSML_ERRNO_EBADF				INT16_C(4)
#define DSML_ERRNO_EMFILE				INT16_C(5)
/*TODO*/
#define DSML_ERRNO_WRONG_FRAME			INT16_C(16)
#define DSML_ERRNO_BAD_ARBITRATION		INT16_C(17)
#define DSML_ERRNO_TIMEOUT				INT16_C(18)
#define DSML_ERRNO_CONNECTION_LOST		INT16_C(19)
/*TODO refine*/
/**/
#define DSML_LAST_ERROR_SET(d, err) \
	do { \
		DSML_ASSERT(__LINE__ < INT32_C(0x00007fff), "really!"); \
		DSML_ASSERT((int32)(err) < INT32_C(0x00007fff), "really!"); \
		(d)->errcode = (((int32)__LINE__) << 16) \
			| ((int32)(err)); \
		DSML_CALLBACK((d), ERROR_SET); \
	} while(0)
#define DSML_LAST_ERROR_CLEAR(d) \
	do { (d)->errcode = INT32_C(0); } while(0)
#define DSML_LAST_ERROR_GET(d)			((d)->errcode)
#define DSML_LAST_ERROR_LINE_GET(d)		(((d)->errcode >> 16))
#define DSML_LAST_ERROR_CODE_GET(d)		(((d)->errcode & INT32_C(0x0000ffff)))
#else /* #ifndef DSML_ERRNO_DISABLE */
#define DSML_LAST_ERROR_SET(d, err)		do { } while(0)
#define DSML_LAST_ERROR_CLEAR(d)		do { } while(0)
#define DSML_LAST_ERROR_GET(d)			INT32_C(0)
#define DSML_LAST_ERROR_LINE_GET(d)		INT32_C(0)
#define DSML_LAST_ERROR_CODE_GET(d)		INT32_C(0)
#endif /* #ifndef DSML_ERRNO_DISABLE */

	/* TODO: abstract time keeping!!! */
	uint32 (*gettime_us)(void);
	uint32 timeout_us; /*!< TODO: define (and use) connection timeout!!! */

	uint16 state;
#define DSML_STATE_NONE					DSML_FRAME_TYPE_NONE
#define DSML_STATE_IDLE					DSML_FRAME_TYPE_IDLE
#define DSML_STATE_CMD					DSML_FRAME_TYPE_CMD
#define DSML_STATE_CMD_END				DSML_FRAME_TYPE_CMD_END
/**/
#define DSML_STATE_CMD_SUB_TYPE_NONE	UINT8_C(0)
#define DSML_STATE_CMD_SUB_TYPE_RELOAD	UINT8_C(1)
#define DSML_STATE_CMD_SUB_TYPE_EXEC	UINT8_C(2)
#define DSML_STATE_CMD_SUB_TYPE_CORRUPT	UINT8_C(3)
#define DSML_STATE_CMD_SUB_TYPE_LOCK	UINT8_C(4)
#define DSML_STATE_CMD_SUB_TYPE_UNLOCK	UINT8_C(5)
/**/
#define DSML_STATE_CMD_TYPE_USER_FIRST	UINT8_C(16)
#define DSML_STATE_CMD_TYPE_USER_LAST	UINT8_C(255)
/**/
#ifndef DSML_READ_DISABLE
#define DSML_STATE_READ_INIT			DSML_FRAME_TYPE_READ_INIT
#define DSML_STATE_READ_DATA			DSML_FRAME_TYPE_READ_DATA
#define DSML_STATE_READ_END				DSML_FRAME_TYPE_READ_END
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
#define DSML_STATE_WRITE_INIT			DSML_FRAME_TYPE_WRITE_INIT
#define DSML_STATE_WRITE_DATA			DSML_FRAME_TYPE_WRITE_DATA
#define DSML_STATE_WRITE_END			DSML_FRAME_TYPE_WRITE_END
#endif /* #ifndef DSML_WRITE_DISABLE */
/**/
#define DSML_STATE_WAIT_FOR_IDLE		(DSML_FRAME_TYPE_LAST + UINT8_C(1))

	uint16 status;
#define DSML_STATUS_NONE			UINT16_C(0x0000)
#define DSML_STATUS_INIT			UINT16_C(0x0001)
#define DSML_STATUS_FATAL			UINT16_C(0x0002)
#define DSML_STATUS_IDLE			UINT16_C(0x0004)
#define DSML_STATUS_BUSY			UINT16_C(0x0008)
/**/
#define DSML_STATUS_CMD				UINT16_C(0x0100)
#define DSML_STATUS_READ			UINT16_C(0x0200)
#define DSML_STATUS_WRITE			UINT16_C(0x0400)
/**/
#define DSML_STATUS_MASTER			UINT16_C(0x1000)
#define DSML_STATUS_SLAVE			UINT16_C(0x2000)

	uint16 master_priority;
	uint16 peer_master_priority;

	uint8 session; /*!< overall network session!!! (we want a multi master network!!!) */
	struct dsml_session_data_tag session_data;
	uint8 retry_max;

	uint16 dir_magic;
	uint16 peer_dir_magic;
	struct dsml_file_tag ** dir; /*!< single level directory srtucure definition!!! */
	uint16 dir_size;

	struct dsml_frame_data_tag frame_tx;
	struct dsml_frame_data_tag frame_rx;

	void * userdata;
};

#define DSML_CMD_FILE_INVALID	UINT16_C(0xffff) /*TODO config*/
#ifndef DSML_MASTER_CMD_DISABLE
extern reg dsml_remote_cmd(DSML_CONTEXT_ARG, uint16 file, uint8 cmd, const void * buff, uint16 nbyte);
#define dsml_remote_std_cmd(d, file, cmd) \
	dsml_remote_cmd((d), (file), (cmd), DSML_NULL, UINT16_C(0))
#define dsml_remote_user_cmd(d, file, cmd, buff, nbyte) \
	dsml_remote_cmd((d), (file), (cmd), (buff), (nbyte))
#endif /* #ifndef DSML_MASTER_CMD_DISABLE */
extern reg dsml_local_cmd(DSML_CONTEXT_ARG, uint16 file, uint8 cmd, const void * buff, uint16 nbyte, uint16 pid);
#define dsml_local_std_cmd(d, file, cmd, pid) \
	dsml_local_cmd((d), (file), (cmd), DSML_NULL, UINT16_C(0), (pid))
#define dsml_local_user_cmd(d, file, cmd, buff, nbyte, pid) \
	dsml_local_cmd((d), (file), (cmd), (buff), (nbyte), (pid))

extern uint16 dsml_local_file_attributes(DSML_CONTEXT_ARG, uint16 file);
#ifndef DSML_FILE_USER_ATTRIBUTES_DISABLE
#define dsml_local_file_user_attributes(d, file) \
	(dsml_local_file_attributes((d), (file)) & DSML_FILE_ATTRIBUTE_MASK_USER)
extern reg dsml_local_file_user_attributes_set(DSML_CONTEXT_ARG,
	uint16 file, uint16 user_attributes);
extern reg dsml_local_file_user_attributes_clear(DSML_CONTEXT_ARG,
	uint16 file, uint16 user_attributes);
#endif /* #ifndef DSML_FILE_USER_ATTRIBUTES_DISABLE */

extern int32 dsml_local_file_open(DSML_CONTEXT_ARG, uint16 file, uint16 oflag, uint16 pid);
extern int32 dsml_local_file_close(DSML_CONTEXT_ARG, uint16 file, uint16 pid);
extern int32 dsml_local_file_read(DSML_CONTEXT_ARG, uint16 file, void * buff, uint32 nbyte, uint32 offset, uint16 pid);
extern int32 dsml_local_file_write(DSML_CONTEXT_ARG, uint16 file, const void * buff, uint32 nbyte, uint32 offset, uint16 pid);
extern int32 dsml_local_file_size(DSML_CONTEXT_ARG, uint16 file);

#ifndef DSML_MASTER_READ_DISABLE
extern reg dsml_remote_read(DSML_CONTEXT_ARG, uint16 file, uint32 nbyte, uint32 offset);
extern reg dsml_remote_read_file(DSML_CONTEXT_ARG, uint16 file);
#endif /* #ifndef DSML_MASTER_READ_DISABLE */
#ifndef DSML_MASTER_WRITE_DISABLE
extern reg dsml_remote_write(DSML_CONTEXT_ARG, uint16 file, uint32 nbyte, uint32 offset);
extern reg dsml_remote_write_file(DSML_CONTEXT_ARG, uint16 file);
#endif /* #ifndef DSML_MASTER_WRITE_DISABLE */

extern reg dsml_callback(DSML_CONTEXT_ARG, reg event);

extern reg dsml_force_abort(DSML_CONTEXT_ARG);

extern void dsml_task(DSML_CONTEXT_ARG);

/* NOTE: try to think about modules! */
extern reg dsml_load(DSML_CONTEXT_ARG);
extern void dsml_unload(DSML_CONTEXT_ARG);

#define DSML_RESULT_OK		REG_C(0)
#define DSML_RESULT_ERROR	(!DSML_RESULT_OK)

#define DSML_FALSE			REG_C(0)
#define DSML_TRUE			(!DSML_FALSE)

#ifdef __cplusplus
}
#endif

#endif /* #ifndef STDSML_SCORE_CORE_H */
