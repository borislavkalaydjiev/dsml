/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifndef SFTL_SCORE_TOOLS_H
#define SFTL_SCORE_TOOLS_H

#include <dsml/score/core.h>

#ifdef __cplusplus
extern "C"
{
#endif

extern void dsml_tools_rx_uint8(void * const dest, uint8 ** src);
extern void dsml_tools_tx_uint8(void * const dest, uint8 ** src);
extern void dsml_tools_rx_uint16(void * const dest, uint8 ** src);
extern void dsml_tools_tx_uint16(void * const dest, uint8 ** src);
extern void dsml_tools_rx_uint32(void * const dest, uint8 ** src);
extern void dsml_tools_tx_uint32(void * const dest, uint8 ** src);
#ifndef HOST_IS_XC167
extern void dsml_tools_rx_uint64(void * const dest, uint8 ** src);
extern void dsml_tools_tx_uint64(void * const dest, uint8 ** src);
#endif /* #ifndef HOST_IS_XC167 */

extern uint16 dsml_tools_checksum_default(const void * buff, uint16 len);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef SFTL_SCORE_TOOLS_H */
