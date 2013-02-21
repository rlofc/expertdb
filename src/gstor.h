#ifndef GSTOR_H_PLWJO6VR
#define GSTOR_H_PLWJO6VR

#include <stdio.h>

struct gstor;

#define GSTOR_OKAY 0
#define GSTOR_ERROR -1

typedef int result_t;

/* CREATE
 * ---------------------------------------------------------------------------
 * Desc
 * returns:
 *   result: GSTOR_OKAY | GSTOR_ERROR
 */
struct gstor_create_ret {
   result_t result;
}
gstor_create(const char * name);

/* OPEN
 * ---------------------------------------------------------------------------
 * Desc
 * returns:
 *    result: GSTOR_OKAY | GSTOR_ERROR
 *   gstor_h: if GSTOR_OKAY, a valid gstor handle
 */
struct gstor_open_ret {
   result_t result;
   struct gstor    *gstor_h;
}
gstor_open(const char * name);

/* CLOSE
 * ---------------------------------------------------------------------------
 * Desc
 * returns:
 *   result: GSTOR_OKAY | GSTOR_ERROR
 */
struct gstor_close_ret {
   result_t result;
}
gstor_close(struct gstor * gstor_h);

/* STORE
 * ---------------------------------------------------------------------------
 * Desc
 * returns:
 *   result: GSTOR_OKAY | GSTOR_ERROR
 */
struct gstor_store_ret {
   result_t result;
}
gstor_store(struct gstor * gstor_h,
                    void * data,
                  size_t   size,
              const char * key);

/* RESTORE
 * ---------------------------------------------------------------------------
 * Desc
 * returns:
 *   result: GSTOR_OKAY | GSTOR_ERROR
 */
struct gstor_restore_ret {
   result_t result;
}
gstor_restore(struct gstor * gstor_h,
                const char * key,
                      void * container,
                    size_t   size);


#endif /* end of include guard: GSTOR_H_PLWJO6VR */

