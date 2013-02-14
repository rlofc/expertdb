#ifndef PETRI_H_6KWEJDKY
#define PETRI_H_6KWEJDKY

extern struct petri petri;

/* CREATE
 * ---------------------------------------------------------------------------
 * Create a new petri file, ready to work with.
 * If the file exists it will be overwritten!
 * returns:
 *    0 - all went okay, file is created
 *    1 - was unable to create the new file
 *    2 - was unable to initialize the file
 */
int petri_create(const char *filename);

/* OPEN
 * ---------------------------------------------------------------------------
 * Open an existing petri file.
 * returns:
 *    petri* - a valid petri handle
 *    0 - an error occured while opening the file
 */
struct petri * petri_open(const char *filename);

/* CLOSE
 * ---------------------------------------------------------------------------
 * Close an open petri file. You should
 * provide a valid petri handle for a
 * created and opened petri file.
 * returns:
 *    0 - file is closed
 *    1 - invalid petri handle
 *    2 - was unable to close file
 */
int petri_close(struct petri * t);

void petri_set(struct petri *t, const char * key, long data);
long petri_get(struct petri *t, const char * key);

#endif /* end of include guard: PETRI_H_6KWEJDKY */

