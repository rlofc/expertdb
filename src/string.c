#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "string.h"

/* CREATE
 * ------------------------------------------------------------------------- */
string_t string_concat(const char * base, ...) {
   string_t ret = { .value = 0 };
   va_list ap;
   va_start(ap,base);
   size_t sum=0;
   for (const char *s = base ; s != 0 ; s = va_arg(ap,const char *)) {
      size_t len = strlen(s);
      sum = sum + len;
      ret.value = realloc(ret.value, sum + 1);
      memcpy(&ret.value[sum-len],s,len);
      ret.value[sum]=0;
   }
   ret.length = sum;
   va_end(ap);
   return ret;
}

/* TO CHAR
 * ------------------------------------------------------------------------- */
const char * string_tochar(string_t str) {
   return str.value;
}

/* DESTROY
 * ------------------------------------------------------------------------- */
void string_destroy(string_t str) {
   free(str.value);
}
