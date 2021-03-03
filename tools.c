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
	register uint8 * s;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(dest);
	DSML_ASSERT_POINTER_CHECK(src);
	DSML_ASSERT_POINTER_CHECK(src[0]);
	s = src[0];
	*((uint8*)dest) = UINT8_C(0)
		| ((uint8)s[0]) << 0;
	*src += sizeof(uint8);
	DSML_FUNCTION_END();
}

void dsml_tools_tx_uint8(void * const dest, uint8 ** src)
{
	register uint8 * s;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(dest);
	DSML_ASSERT_POINTER_CHECK(src);
	DSML_ASSERT_POINTER_CHECK(src[0]);
	s = src[0];
	*s = *((uint8*)dest);
	*src += sizeof(uint8);
	DSML_FUNCTION_END();
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
	uint16 c, crc, crcta[16], crctb[16];
	const uint8 * d;

	DSML_FUNCTION_BEGIN();

	DSML_ASSERT_POINTER_CHECK(buff);

	d = buff;

	/* source: http://www.columbia.edu/kermit/ek.html */
	crcta[ 0] =       0;	/* CRC generation table A */
	crcta[ 1] =  010201;
	crcta[ 2] =  020402;
	crcta[ 3] =  030603;
	crcta[ 4] =  041004;
	crcta[ 5] =  051205;
	crcta[ 6] =  061406;
	crcta[ 7] =  071607;
	crcta[ 8] = 0102010;
	crcta[ 9] = 0112211;
	crcta[10] = 0122412;
	crcta[11] = 0132613;
	crcta[12] = 0143014,
	crcta[13] = 0153215;
	crcta[14] = 0163416;
	crcta[15] = 0173617;

	crctb[ 0] =       0;	/* CRC generation table B */
	crctb[ 1] =  010611;
	crctb[ 2] =  021422;
	crctb[ 3] =  031233;
	crctb[ 4] =  043044;
	crctb[ 5] =  053655;
	crctb[ 6] =  062466;
	crctb[ 7] =  072277;
	crctb[ 8] = 0106110;
	crctb[ 9] = 0116701;
	crctb[10] = 0127532;
	crctb[11] = 0137323;
	crctb[12] = 0145154;
	crctb[13] = 0155745;
	crctb[14] = 0164576;
	crctb[15] = 0174367;

	crc = 0;
    while(len--)
	{
		c = crc ^ (*d++);
		crc = (crc >> 8) ^ ((crcta[(c & UINT16_C(0x00f0)) >> 4]) ^ (crctb[c & UINT16_C(0x000f)]));
    }

	DSML_FUNCTION_END();

    return crc;
}
