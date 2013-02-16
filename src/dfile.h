#ifndef DFILE_H_48FDK2D1
#define DFILE_H_48FDK2D1

#include <stdio.h>

extern struct dfile dfile;

/* CREATE
 * ---------------------------------------------------------------------------
 * Create a new dfile file, ready to work with.
 * If the file exists it will be overwritten!
 * returns:
 *    0 - all went okay, file is created
 *    1 - was unable to create the new file
 *    2 - was unable to initialize the file
 */
int dfile_create(const char *filename);

/* VERSION
 * ---------------------------------------------------------------------------
 * Query the version of a dfile file.
 * returns:
 *   -1 - unable to open file
 *    0 - file is invalid
 *    * - version number
 */
int dfile_version(const char *filename);

/* OPEN
 * ---------------------------------------------------------------------------
 * Open an existing dfile file.
 * returns:
 *    dfile* - a valid dfile handle
 *    0 - an error occured while opening the file
 */
struct dfile * dfile_open(const char *filename);

/* CLOSE
 * ---------------------------------------------------------------------------
 * Close an open dfile file. You should
 * provide a valid dfile handle for a
 * created and opened dfile file.
 * returns:
 *    0 - file is closed
 *    1 - invalid dfile handle
 *    2 - was unable to close file
 */
int dfile_close(struct dfile * t);

/* STORE
 * ---------------------------------------------------------------------------
 * Store a buffer in the dfile. Buffer is appended to
 * the file and the position of the new record is
 * returned.
 * returns:
 *    -1 - an error occured
 *     * - valid position in the file
 */
long dfile_store(struct dfile * file, void * buf, size_t size);

/* RESTORE
 * ---------------------------------------------------------------------------
 * Retrieve a buffer from the dfile, using the size and
 * position.
 * returns:
 *    n - number of records read - should be 1
 *   -1 - an error occured
 */
int dfile_restore(struct dfile * file,long pos, void * buf, size_t size);

#endif /* end of include guard: DFILE_H_48FDK2D1 */
