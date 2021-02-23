/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifdef HAVE_CONFIG
#include <config.h>
#endif /* #ifdef HAVE_CONFIG */

#include <dsml/score/debug.h>
#include <dsml/score/tools.h>

#ifdef DSML_DEBUG
#ifndef DSML_DEBUG_TOOLS
#undef DSML_FUNCTION_BEGIN
#define DSML_FUNCTION_BEGIN()			do { } while(0)
#undef DSML_ASSERT_POINTER_CHECK
#define DSML_ASSERT_POINTER_CHECK(x)	do { } while(0)
#undef DSML_FUNCTION_END
#define DSML_FUNCTION_END()				do { } while(0)
#endif /* #ifndef DSML_DEBUG_TOOLS */
#endif /* #ifdef DSML_DEBUG */

void dsml_tools_rx_uint8(void * const dest, uint8 ** src)
{
	// TODO
}

void dsml_tools_tx_uint8(void * const dest, uint8 ** src)
{
	// TODO
}

void dsml_tools_rx_uint16(void * const dest, uint8 ** src)
{
	// TODO
}

void dsml_tools_tx_uint16(void * const dest, uint8 ** src)
{
	// TODO
}

void dsml_tools_rx_uint32(void * const dest, uint8 ** src)
{
	// TODO
}

void dsml_tools_tx_uint32(void * const dest, uint8 ** src)
{
	// TODO
}
#ifndef HOST_IS_XC167
void dsml_tools_rx_uint64(void * const dest, uint8 ** src)
{
	// TODO
}

void dsml_tools_tx_uint64(void * const dest, uint8 ** src)
{
	// TODO
}
#endif /* #ifndef HOST_IS_XC167 */

uint16 dsml_tools_checksum_default(const void * buff, uint16 len)
{
	uint16 crc;
	// TODO
	return crc;
}
