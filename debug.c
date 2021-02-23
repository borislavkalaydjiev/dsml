/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifdef HAVE_CONFIG
#include <config.h>
#endif /* #ifdef HAVE_CONFIG */

#include <dsml/score/debug.h>

#ifdef DSML_DEBUG

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

static int level;
#define _LEVEL_STR				"    "
#define _LINE_FEED				"\r\n"
#define _BUFF_BYTES_PER_LINE	8

static void dsml_debug_align(int line, const char * file)
{
	int i;
	printf("%s:%.5i:", file, line);
	printf(_LEVEL_STR);
	for(i = 0; i < level; i++) { printf(_LEVEL_STR); }
	fflush(stdout);
}

void dsml_debug_function_begin(int line, const char * file, const char * function)
{
	dsml_debug_align(line, file);
	printf("{ Entering function: %s" _LINE_FEED, function);
	level++;
	fflush(stdout);
}

void dsml_debug_function_end(int line, const char * file, const char * function)
{
	level--;
	dsml_debug_align(line, file);
	printf("} Exiting function : %s" _LINE_FEED, function);
	fflush(stdout);
}

void dsml_debug_assert(int line, const char * file, int expression, const char * str)
{
	if(!expression)
	{
		dsml_debug_print(line, file, str);
		assert(expression);
	}
	fflush(stdout);
}

void dsml_debug_print(int line, const char * file, const char * str)
{
	dsml_debug_align(line, file);
	printf("%s" _LINE_FEED, str);
	fflush(stdout);
}

void dsml_debug_dump(int line, const char * file, DSML_CONTEXT_ARG)
{
	dsml_debug_print(line, file, ">>> dumping working data >>>>>>>>");
	dsml_debug_align(line, file);
	printf(".id : (%#llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.id);
	dsml_debug_align(line, file);
	printf(".load : %p" _LINE_FEED, DSML_CONTEXT.load);
	dsml_debug_align(line, file);
	printf(".unload : %p" _LINE_FEED, DSML_CONTEXT.unload);
	dsml_debug_align(line, file);
	printf(".send : %p" _LINE_FEED, DSML_CONTEXT.send);
	dsml_debug_align(line, file);
	printf(".receive : %p" _LINE_FEED, DSML_CONTEXT.receive);
	dsml_debug_align(line, file);
	printf(".checksum : %p" _LINE_FEED, DSML_CONTEXT.checksum);
	dsml_debug_align(line, file);
	printf(".rand : %p" _LINE_FEED, DSML_CONTEXT.rand);
	dsml_debug_align(line, file);
	printf(".callback : %p" _LINE_FEED, DSML_CONTEXT.callback);
	dsml_debug_align(line, file);
	printf(".error : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.errno);
	dsml_debug_align(line, file);
	printf(".gettime_us : %p" _LINE_FEED, DSML_CONTEXT.gettime_us);
	dsml_debug_align(line, file);
	printf(".timeout_us : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.timeout_us);
	dsml_debug_align(line, file);
	printf(".state : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.state);
	dsml_debug_align(line, file);
	printf(".status : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.status);
	dsml_debug_align(line, file);
	printf(".master_priority : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.master_priority);
	dsml_debug_align(line, file);
	printf(".peer_master_priority : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.peer_master_priority);
	dsml_debug_align(line, file);
	printf(".session : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session);
	dsml_debug_print(line, file, ">>>");
	dsml_debug_align(line, file);
	printf(".session_data.session : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.session);
	dsml_debug_align(line, file);
	printf(".session_data.type : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.type);
	dsml_debug_align(line, file);
	printf(".session_data.cmd_type : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.cmd_type);
	dsml_debug_align(line, file);
	printf(".session_data.file : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.file);
	dsml_debug_align(line, file);
	printf(".session_data.nbyte : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.nbyte);
	dsml_debug_align(line, file);
	printf(".session_data.offset : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.offset);
	dsml_debug_align(line, file);
	printf(".session_data.nbyte_remaining : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.nbyte_remaining);
	dsml_debug_align(line, file);
	printf(".session_data.offset_current : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.offset_current);
	dsml_debug_align(line, file);
	printf(".session_data.retry_count : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.retry_count);
	dsml_debug_align(line, file);
	printf(".session_data.sequence_number : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.session_data.sequence_number);
	dsml_debug_print(line, file, ">>>");
	dsml_debug_align(line, file);
	printf(".retry_max : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.retry_max);
	dsml_debug_align(line, file);
	printf(".dir_magic : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.dir_magic);
	dsml_debug_align(line, file);
	printf(".peer_dir_magic : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.peer_dir_magic);
	dsml_debug_align(line, file);
	printf(".dir : %p" _LINE_FEED, DSML_CONTEXT.dir);
	dsml_debug_align(line, file);
	printf(".dir_size : (0x%llx) %lli" _LINE_FEED, (int64)DSML_CONTEXT.dir_size);
	dsml_debug_print(line, file, ">>> dumping rx frame");
	dsml_debug_frame_dump(line, file, &DSML_CONTEXT, &DSML_CONTEXT.frame_rx);
	dsml_debug_print(line, file, ">>> dumping tx frame");
	dsml_debug_frame_dump(line, file, &DSML_CONTEXT, &DSML_CONTEXT.frame_tx);
	dsml_debug_align(line, file);
	printf(".userdata : %p" _LINE_FEED, DSML_CONTEXT.userdata);
	dsml_debug_print(line, file, ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	fflush(stdout);
}

void dsml_debug_frame_dump(int line, const char * file, DSML_CONTEXT_ARG, const struct dsml_frame_data_tag * const f)
{
	int i,j;

#undef DSML_SEMICOLON_
#define DSML_SEMICOLON_ ;
/**/
#undef DSML_FRAME_ITEM_TOOL
#define DSML_FRAME_ITEM_TOOL(x, rx_tx, src, type, name) \
	do { \
		dsml_debug_align(line, file); \
		printf("." #x "." #name " (" #type ") : (%#llx) %lli" _LINE_FEED, (int64)f->x.name); \
	} while(0)

	dsml_debug_print(line, file, "=== dumping frame ===============");
	DSML_FRAME_LIST_ITEM_TOOL(header, XXX, XXX);
	dsml_debug_print(line, file, "===");
	switch(f->header.type)
	{
	case DSML_FRAME_TYPE_IDLE:
		DSML_FRAME_LIST_ITEM_TOOL(idle, XXX, XXX);
		break;
#ifndef DSML_CMD_DISABLE
	case DSML_FRAME_TYPE_CMD:
		DSML_FRAME_LIST_ITEM_TOOL(cmd, XXX, XXX);
		break;
	case DSML_FRAME_TYPE_CMD_END:
		DSML_FRAME_LIST_ITEM_TOOL(cmd_end, XXX, XXX);
		break;
#endif /* #ifndef DSML_CMD_DISABLE */
#if !defined(DSML_READ_DISABLE) || !defined(DSML_WRITE_DISABLE)
#ifndef DSML_READ_DISABLE
	case DSML_FRAME_TYPE_READ_INIT:
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
	case DSML_FRAME_TYPE_WRITE_INIT:
#endif /* #ifndef DSML_WRITE_DISABLE */
		DSML_FRAME_LIST_ITEM_TOOL(file_init, XXX, XXX);
		break;
#ifndef DSML_READ_DISABLE
	case DSML_FRAME_TYPE_READ_DATA:
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
	case DSML_FRAME_TYPE_WRITE_DATA:
#endif /* #ifndef DSML_WRITE_DISABLE */
		DSML_FRAME_LIST_ITEM_TOOL(file_data, XXX, XXX);
		break;
#ifndef DSML_READ_DISABLE
	case DSML_FRAME_TYPE_READ_END:
#endif /* #ifndef DSML_READ_DISABLE */
#ifndef DSML_WRITE_DISABLE
	case DSML_FRAME_TYPE_WRITE_END:
#endif /* #ifndef DSML_WRITE_DISABLE */
		DSML_FRAME_LIST_ITEM_TOOL(file_end, XXX, XXX);
		break;
#endif /* #if !defined(DSML_READ_DISABLE) || !defined(DSML_WRITE_DISABLE) */
	case DSML_FRAME_TYPE_ACK:
		DSML_FRAME_LIST_ITEM_TOOL(ack, XXX, XXX);
		break;
	case DSML_FRAME_TYPE_NACK:
		DSML_FRAME_LIST_ITEM_TOOL(nack, XXX, XXX);
		break;
	case DSML_FRAME_TYPE_ABORT:
		DSML_FRAME_LIST_ITEM_TOOL(abort, XXX, XXX);
		break;
	default:
		dsml_debug_print(line, file, "NOTE: unknown frame type!)");
		break;
	}
	dsml_debug_print(line, file, "===");
	dsml_debug_align(line, file);
	printf(".buff_size : %i" _LINE_FEED, (int)f->buff_size);
	dsml_debug_align(line, file);
	printf(".buff_bytes : %i" _LINE_FEED, (int)f->buff_bytes);
	dsml_debug_align(line, file);
	printf(".buff : %p" _LINE_FEED, f->buff);
	if(f->buff_bytes)
	{
		for(i = 0; i < f->buff_bytes; i++)
		{
			if(!(i%_BUFF_BYTES_PER_LINE))
			{
				if(i)
				{
					printf(" : ");
					for(j = i - _BUFF_BYTES_PER_LINE; j < i; j++)
					{
						if(isprint((int)((uint8*)f->buff)[j])) { printf("%c", (int)((uint8*)f->buff)[j]); }
						else { printf("."); }
					}
					printf(_LINE_FEED);
				}
				dsml_debug_align(line, file);
				printf(_LEVEL_STR "0x%.4x: ", i);
			}
			printf("0x%.2x", (unsigned int)((uint8*)f->buff)[i]);
			if(((int)f->buff_bytes - i - 1) == (int)f->user_bytes) { printf("|"); }
			else { printf(" "); }
		}
		while(i%_BUFF_BYTES_PER_LINE)
		{
			printf("     ");
			i++;
			if(!(i%_BUFF_BYTES_PER_LINE))
			{
				if(i)
				{
					printf(" : ");
					for(j = (int)(f->buff_bytes) - (int)(f->buff_bytes)%_BUFF_BYTES_PER_LINE; j < (int)(f->buff_bytes); j++)
					{
						if(isprint((int)((uint8*)f->buff)[j])) { printf("%c", (int)((uint8*)f->buff)[j]); }
						else { printf("."); }
					}
				}
			}
		}
		printf(_LINE_FEED);
	}
	dsml_debug_align(line, file);
	printf(".user_bytes : %i" _LINE_FEED, (int)f->user_bytes);
	dsml_debug_align(line, file);
	printf(".user_buff : %p" _LINE_FEED, f->user_buff);
	if(f->user_bytes)
	{
		for(i = 0; i < f->user_bytes; i++)
		{
			if(!(i%_BUFF_BYTES_PER_LINE))
			{
				if(i)
				{
					printf(" : ");
					for(j = i - _BUFF_BYTES_PER_LINE; j < i; j++)
					{
						if(isprint((int)((uint8*)f->user_buff)[j])) { printf("%c", (int)((uint8*)f->user_buff)[j]); }
						else { printf("."); }
					}
					printf(_LINE_FEED);
				}
				dsml_debug_align(line, file);
				printf(_LEVEL_STR "0x%.4x: ", i);
			}
			printf("0x%.2x ", (unsigned int)((uint8*)f->user_buff)[i]);
		}
		while(i%_BUFF_BYTES_PER_LINE)
		{
			printf("     ");
			i++;
			if(!(i%_BUFF_BYTES_PER_LINE))
			{
				if(i)
				{
					printf(" : ");
					for(j = (int)(f->user_bytes) - (int)(f->user_bytes)%_BUFF_BYTES_PER_LINE; j < (int)(f->user_bytes); j++)
					{
						if(isprint((int)((uint8*)f->user_buff)[j])) { printf("%c", (int)((uint8*)f->user_buff)[j]); }
						else { printf("."); }
					}
				}
			}
		}
		printf(_LINE_FEED);
	}
	dsml_debug_align(line, file);
	printf(".is_valid : %i" _LINE_FEED, (int)f->is_valid);
	dsml_debug_align(line, file);
	printf(".time_us : %llu" _LINE_FEED, (uint64)f->time_us);
	dsml_debug_print(line, file, "=================================");
	fflush(stdout);
}

void dsml_debug_empty_call()
{
	/* NOTE: use for code coverage */
}

#endif /* #ifdef DSML_DEBUG */
