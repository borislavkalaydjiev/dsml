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
	register uint8 * s;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(dest);
	DSML_ASSERT_POINTER_CHECK(src);
	DSML_ASSERT_POINTER_CHECK(src[0]);
	s = src[0];
	*((uint16*)dest) = UINT16_C(0)
		| ((uint16)s[0]) << 8
		| ((uint16)s[1]) << 0;
	*src += sizeof(uint16);
	DSML_FUNCTION_END();
}

void dsml_tools_tx_uint16(void * const dest, uint8 ** src)
{
	register uint8 * s;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(dest);
	DSML_ASSERT_POINTER_CHECK(src);
	DSML_ASSERT_POINTER_CHECK(src[0]);
	s = src[0];
	*s++ = (*((uint16*)dest)) >> 8;
	*s = (*((uint16*)dest)) >> 0;
	*src += sizeof(uint16);
	DSML_FUNCTION_END();
}

void dsml_tools_rx_uint32(void * const dest, uint8 ** src)
{
	register uint8 * s;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(dest);
	DSML_ASSERT_POINTER_CHECK(src);
	DSML_ASSERT_POINTER_CHECK(src[0]);
	s = src[0];
	*((uint32*)dest) = UINT32_C(0)
		| ((uint32)s[0]) << 24
		| ((uint32)s[1]) << 16
		| ((uint32)s[2]) << 8
		| ((uint32)s[3]) << 0;
	*src += sizeof(uint32);
	DSML_FUNCTION_END();
}

void dsml_tools_tx_uint32(void * const dest, uint8 ** src)
{
	register uint8 * s;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(dest);
	DSML_ASSERT_POINTER_CHECK(src);
	DSML_ASSERT_POINTER_CHECK(src[0]);
	s = src[0];
	*s++ = (*((uint32*)dest)) >> 24;
	*s++ = (*((uint32*)dest)) >> 16;
	*s++ = (*((uint32*)dest)) >> 8;
	*s = (*((uint32*)dest)) >> 0;
	*src += sizeof(uint32);
	DSML_FUNCTION_END();
}
#ifndef HOST_IS_XC167
void dsml_tools_rx_uint64(void * const dest, uint8 ** src)
{
	register uint8 * s;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(dest);
	DSML_ASSERT_POINTER_CHECK(src);
	DSML_ASSERT_POINTER_CHECK(src[0]);
	s = src[0];
	*((uint64*)dest) = UINT64_C(0)
		| ((uint64)s[0]) << 56
		| ((uint64)s[1]) << 48
		| ((uint64)s[2]) << 40
		| ((uint64)s[3]) << 32
		| ((uint64)s[4]) << 24
		| ((uint64)s[5]) << 16
		| ((uint64)s[6]) << 8
		| ((uint64)s[7]) << 0;
	*src += sizeof(uint64);
	DSML_FUNCTION_END();
}

void dsml_tools_tx_uint64(void * const dest, uint8 ** src)
{
	register uint8 * s;
	DSML_FUNCTION_BEGIN();
	DSML_ASSERT_POINTER_CHECK(dest);
	DSML_ASSERT_POINTER_CHECK(src);
	DSML_ASSERT_POINTER_CHECK(src[0]);
	s = src[0];
	*s++ = (*((uint64*)dest)) >> 56;
	*s++ = (*((uint64*)dest)) >> 48;
	*s++ = (*((uint64*)dest)) >> 40;
	*s++ = (*((uint64*)dest)) >> 32;
	*s++ = (*((uint64*)dest)) >> 24;
	*s++ = (*((uint64*)dest)) >> 16;
	*s++ = (*((uint64*)dest)) >> 8;
	*s = (*((uint64*)dest)) >> 0;
	*src += sizeof(uint64);
	DSML_FUNCTION_END();
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
