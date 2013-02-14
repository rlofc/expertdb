#include "petri.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>

#define N_VALID_KEY_CHARS 16

struct petri
{
   FILE * f;
};

struct petri_node_t
{
   long next_offset[N_VALID_KEY_CHARS];
   long data_offset;
};

/* CREATE
 * ------------------------------------------------------------------------- */
int petri_create(const char *filename) {
   struct petri_node_t root_node;
   FILE * f;
   memset(&root_node,0,sizeof(struct petri_node_t));
   f = fopen(filename,"w+b");
   if (f == 0) goto error;
   if (fwrite(&root_node,sizeof(struct petri_node_t),1,f) == 0)
      goto close_and_error;
   return 0;

close_and_error:
   fclose(f);
   return 2;
error:
   return 1;
}

/* OPEN
 * ------------------------------------------------------------------------- */
struct petri * petri_open(const char *filename) {
   struct petri * p;
   FILE * f = fopen(filename,"r+b");
   if (f == 0) goto error;
   p = malloc(sizeof(struct petri));
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
int petri_close(struct petri * t) {
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

