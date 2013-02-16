#include "dfile.h"
#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#define ENSURE0(cmd_should_return_0) \
   if (cmd_should_return_0!=0) goto error;
#define ENSURE(cmd_should_not_return_0) \
   if (cmd_should_not_return_0==0) goto error;

struct dfile
{
   FILE * f;
};

/* CREATE
 * ------------------------------------------------------------------------- */
int dfile_create(const char *filename) {
   FILE * f;
   f = fopen(filename,"w+b");
   if (f == 0) goto error;
   fclose(f);
   return 0;

error:
   return 1;
}

/* VERSION
 * ------------------------------------------------------------------------- */
int dfile_version(const char *filename) {
   FILE * f = fopen(filename,"rb");
   if (f == 0) goto open_failed;
   fclose(f);
   return 1;

open_failed:
   return -1;
}

/* OPEN
 * ------------------------------------------------------------------------- */
struct dfile * dfile_open(const char *filename) {
   struct dfile * p;
   FILE * f = fopen(filename,"r+b");
   if (f == 0) goto error;
   p = malloc(sizeof(struct dfile));
   if (p == 0) goto close_and_error;
   p->f = f;
   return p;

close_and_error:
   fclose(f);
error:
   return 0;
}

/* CLOSE
 * ------------------------------------------------------------------------- */
int dfile_close(struct dfile * t) {
   if (t==0) goto error_invalid_input;
   if (fcntl((intptr_t)t->f,F_GETFD)==0) goto error_invalid_input;
   if (fclose(t->f)!=0) goto error_close_failed;
   free(t);
   return 0;

error_invalid_input:
   return 1;
error_close_failed:
   return 2;
}
