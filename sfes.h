/* DSML / Distributed Systems Messaging Layer, Borislav Kalaydjiev */
#ifndef DSML_SCORE_SFES_H
#define DSML_SCORE_SFES_H

#include <dsml/score/core.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define DSML_SFES_ALOCATE_DATA(symbol, file_count) \
	struct dsml_sfes_##symbol##_tag \
	{ \
		reg read[((file_count) + (sizeof(reg)*8) - 1)/(sizeof(reg)*8)]; \
		reg write[((file_count) + (sizeof(reg)*8) - 1)/(sizeof(reg)*8)]; \
		uint32 update_time_us_read[(file_count)]; \
		uint32 update_time_us_write[(file_count)]; \
	}; \
	DSML_STATIC struct dsml_sfes_##symbol##_tag dsml_sfes_##symbol;

#define DSML_SFES_ALOCATE_DATA_INIT(symbol, sfes) \
	do { \
		sfes->read = dsml_sfes_##symbol.read; \
		sfes->write = dsml_sfes_##symbol.write; \
		sfes->update_time_us_read = dsml_sfes_##symbol.update_time_us_read; \
		sfes->update_time_us_write = dsml_sfes_##symbol.update_time_us_write; \
	} while(0)

struct dsml_sfes_tag
{
	reg id;

	reg current_file_read;
	uint16 current_file;
	uint32 timeout_us;

	struct dsml_tag * dsml;
	reg * read;
	reg * write;

	uint32 * update_time_us_read;
	uint32 * update_time_us_write;
	reg (*timeout)(struct dsml_sfes_tag * const d, uint16 file);

	reg (*callback)(DSML_CONTEXT_ARG, reg event);

	void * userdata;
};

extern reg dsml_sfes_add(struct dsml_sfes_tag * const d,
	uint16 file, uint16 oflag);
#define dsml_sfes_add_read(d, file) \
	dsml_sfes_add((d), (file), DSML_FILE_OFLAG_READ)
#define dsml_sfes_add_write(d, file) \
	dsml_sfes_add((d), (file), DSML_FILE_OFLAG_WRITE)
#define dsml_sfes_add_rw(d, file) \
	dsml_sfes_add((d), (file), DSML_FILE_OFLAG_RW)

extern reg dsml_sfes_remove(struct dsml_sfes_tag * const d,
	uint16 file, uint16 oflag);
#define dsml_sfes_remove_read(d, file) \
	dsml_sfes_remove((d), (file), DSML_FILE_OFLAG_READ)
#define dsml_sfes_remove_write(d, file) \
	dsml_sfes_remove((d), (file), DSML_FILE_OFLAG_WRITE)
#define dsml_sfes_remove_rw(d, file) \
	dsml_sfes_remove((d), (file), DSML_FILE_OFLAG_RW)

extern void dsml_sfes_task(struct dsml_sfes_tag * const d);

extern reg dsml_sfes_load(struct dsml_sfes_tag * const d);
extern void dsml_sfes_unload(struct dsml_sfes_tag * const d);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef DSML_SCORE_SFES_H */
