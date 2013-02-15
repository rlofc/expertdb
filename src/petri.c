#include "petri.h"
#include <assert.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

#include "murmur.h"

#define ENSURE0(cmd_should_return_0) \
   if (cmd_should_return_0!=0) goto error;
#define ENSURE(cmd_should_not_return_0) \
   if (cmd_should_not_return_0==0) goto error;

#define N_VALID_KEY_CHARS 16

#define MURMUR MurmurHash3_x64_128
#define MURMURS 32

struct petri
{
   FILE * f;
};

struct petri_node_t
{
   long next_offset[N_VALID_KEY_CHARS];
   long data_offset;
};

/* turns the 32 bit key into 8x4 fragments, 
 * 4 bits per fraction, 8 levels-deep tree
 * ------------------------------------------------------------------------- */
static int get_index_part(int i,uint8_t buf[MURMURS/8]) {
   const uint8_t zeroers[16] = { 0xf0,0x0f,0xf0,0x0f,
                                 0xf0,0x0f,0xf0,0x0f,
                                 0xf0,0x0f,0xf0,0x0f,
                                 0xf0,0x0f,0xf0,0x0f};
   const int shifters[16] = { 4,0,4,0,4,0,4,0,4,0,4,0,4,0,4,0 };
   uint8_t fragment = buf[i/2];
   fragment = fragment & zeroers[i];
   fragment = fragment >> shifters[i];
   return fragment;
}


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
   fclose(f);
   return 0;

close_and_error:
   fclose(f);
   return 2;
error:
   return 1;
}

/* VERSION
 * ------------------------------------------------------------------------- */
int petri_version(const char *filename) {
   FILE * f = fopen(filename,"rb");
   if (f == 0) goto open_failed;
   fseek(f,0,SEEK_END);
   long pos = ftell(f);
   if (pos % sizeof(struct petri_node_t) !=0) goto invalid_size;
   fclose(f);
   return 1;

open_failed:
   return -1;

invalid_size:
   fclose(f);
   return 0;
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


/* SET
 * ------------------------------------------------------------------------- */
int petri_set(struct petri * t, const char * key, long data) {
   assert(fseek(t->f,0,SEEK_SET)==0);
   struct petri_node_t node;
   assert(fread(&node,sizeof(struct petri_node_t),1,t->f)>0);
   uint8_t buf[MURMURS/8];
   MURMUR(key,strlen(key),0xf1c744,buf);
   int i = 0, len = MURMURS/4;
   long fp = 0;
   for(; i < len ; i++ ) {
      int index = get_index_part(i,buf);
      if (node.next_offset[index] == 0) {
         long oldpos = ftell(t->f)-sizeof(struct petri_node_t);
         fseek(t->f,0,SEEK_END);
         long pos = ftell(t->f);
         struct petri_node_t n;
         memset(&n,0,sizeof(struct petri_node_t));
         fwrite(&n,sizeof(struct petri_node_t),1,t->f);
         fseek(t->f,oldpos,SEEK_SET);
         node.next_offset[index] = pos;
         fwrite(&node,sizeof(struct petri_node_t),1,t->f);
      }
      fp = node.next_offset[index];
      fseek(t->f,fp,SEEK_SET);
      fread(&node,sizeof(struct petri_node_t),1,t->f);
   }
   fseek(t->f,fp,SEEK_SET);
   node.data_offset = (long)data;
   fwrite(&node,sizeof(struct petri_node_t),1,t->f);
   return 0;
}

/* GET
 * ------------------------------------------------------------------------- */
int petri_get(struct petri *t, const char * key, long * data) {
   fseek(t->f,0,SEEK_SET);
   struct petri_node_t node;
   fread(&node,sizeof(struct petri_node_t),1,t->f);
   uint8_t buf[MURMURS/8];
   MURMUR(key,strlen(key),0xf1c744,buf);
   int i = 0, len = MURMURS/4;
   for(; i < len ; i++ ) {
      int index = get_index_part(i,buf);
      if (node.next_offset[index] == 0) {
         break;
      } else {
         fseek(t->f,node.next_offset[index],SEEK_SET);
         fread(&node,sizeof(struct petri_node_t),1,t->f);
      }
   }
   return (i==len) ? *data = node.data_offset,0 : 1;
}
