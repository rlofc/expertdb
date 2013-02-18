#include <stdlib.h>
#include <string.h>
#include "string.h"
#include "petri.h"
#include "dfile.h"
#include "gstor.h"

struct gstor {
   struct petri * index;
   struct dfile * data;
};

/* CREATE
 * ------------------------------------------------------------------------- */
struct gstor_create_ret
gstor_create(const char * name) {
   struct gstor_create_ret ret;

   string_t petri_filename = string_concat(name,".petri",0);
   if (INVALID_STR(petri_filename)) goto error;
   string_t dfile_filename = string_concat(name,".dfile",0);
   if (INVALID_STR(dfile_filename)) goto error;

   if (petri_create(string_tochar(petri_filename))!=0) goto error;
   if (dfile_create(string_tochar(dfile_filename))!=0) goto error;

   string_destroy(petri_filename);
   string_destroy(dfile_filename);

   return ret.result = GSTOR_OKAY, ret;

error:
   return ret.result = GSTOR_ERROR, ret;
}

/* OPEN
 * ------------------------------------------------------------------------- */
struct gstor_open_ret
gstor_open(const char * name) {
   struct gstor_open_ret ret;

   string_t petri_filename = string_concat(name,".petri",0);
   if (INVALID_STR(petri_filename)) goto error;
   string_t dfile_filename = string_concat(name,".dfile",0);
   if (INVALID_STR(dfile_filename)) goto error;

   ret.gstor_h = malloc(sizeof(gstor));
   ret.gstor_h->index = petri_open(string_tochar(petri_filename));
   if (ret.gstor_h->index==0) goto error;
   ret.gstor_h->data  = dfile_open(string_tochar(dfile_filename));
   if (ret.gstor_h->data==0) goto close_and_error;

   string_destroy(petri_filename);
   string_destroy(dfile_filename);

   return ret.result = GSTOR_OKAY, ret;

close_and_error:
   petri_close(ret.gstor_h->index);
error:
   return ret.result = GSTOR_ERROR, ret;
}

/* CLOSE
 * ------------------------------------------------------------------------- */
struct gstor_close_ret
gstor_close(struct gstor * gstor_h) {

   struct gstor_close_ret ret;
   petri_close(gstor_h->index);
   dfile_close(gstor_h->data);
   free(gstor_h);
   return ret.result = GSTOR_OKAY, ret;

}

/* STORE
 * ------------------------------------------------------------------------- */
struct gstor_store_ret
gstor_store(struct gstor * gstor_h,
                    void * data,
                  size_t   size,
              const char * key) {

   struct gstor_store_ret ret;
   long pos = dfile_store(gstor_h->data,data,size);
   if (pos < 0) goto error;
   if (petri_set(gstor_h->index, key, pos)!=0) goto error;
   return ret.result = GSTOR_OKAY, ret;

error:
   return ret.result = GSTOR_ERROR, ret;
}

/* RESTORE
 * ------------------------------------------------------------------------- */
struct gstor_restore_ret
gstor_restore(struct gstor * gstor_h,
                const char * key,
                      void * container,
                    size_t   size) {

   struct gstor_restore_ret ret;
   long pos;
   if (petri_get(gstor_h->index, key,&pos)!=0) goto error;
   if (dfile_restore(gstor_h->data,pos,container,size)<0) goto error;
   return ret.result = GSTOR_OKAY, ret;

error:
   return ret.result = GSTOR_ERROR, ret;
}
