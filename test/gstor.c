#include "c89spec/c89spec.h"
#include "../src/gstor.h"
#include <stdio.h>
#include <string.h>

describe (gstor_module) {

   struct gstor * gptr;

   it (should create a gstor data repo) {
      struct gstor_create_ret ret;
      ret = gstor_create("/tmp/gstorfile");
      assert(ret.result == GSTOR_OKAY);
   }

   it (should open a gstor data repo) {
      struct gstor_open_ret ret;
      ret = gstor_open("/tmp/gstorfile");
      assert(ret.result == GSTOR_OKAY);
      gptr = ret.gstor_h;
   }

   it (should close a gstor data repo) {
      struct gstor_close_ret ret;
      ret = gstor_close(gptr);
      assert(ret.result == GSTOR_OKAY);
   }

   it (should save a graph node in the repo) {
      struct gstor_open_ret ret;
      ret = gstor_open("/tmp/gstorfile");
      gptr = ret.gstor_h;
      gstor_store(gptr,"123456789",9,"numbers");
      char buf[10]; buf[9]=0;
      gstor_restore(gptr,"numbers",&buf,9);
      assert(strcmp(buf,"123456789")==0);
      gstor_close(gptr);
   }

   it (should find a graph node in the repo) {

   }

}
