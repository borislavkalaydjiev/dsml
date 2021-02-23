/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifndef DSML_SCORE_CONFIG_DEFAULT_H
#define DSML_SCORE_CONFIG_DEFAULT_H

#ifdef DSML_CONFIG_FILE
#error "config file should be defined as part of the cmd line!"
#endif /* #ifdef DSML_CONFIG_FILE */

#ifdef __cplusplus
extern "C"
{
#endif

/*#define DSML_SINGLE_INSTANCE __dsml_symbol*/

/*#define DSML_FRAME_BUFF_SIZE_MIN	UINT16_C(19)*/
/*#define DSML_ERRNO_DISABLE*/
/*#define DSML_FILE_USER_ATTRIBUTES_DISABLE*/

/*#define DSML_MASTER_DISABLE*/
/*#define DSML_SLAVE_DISABLE*/

/*#define DSML_MASTER_CMD_DISABLE*/
/*#define DSML_MASTER_READ_DISABLE*/
/*#define DSML_MASTER_WRITE_DISABLE*/

/*#define DSML_SLAVE_CMD_DISABLE*/
/*#define DSML_SLAVE_READ_DISABLE*/
/*#define DSML_SLAVE_WRITE_DISABLE*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSML_SCORE_CONFIG_DEFAULT_H */
