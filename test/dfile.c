#include "c89spec/c89spec.h"
#include "../src/dfile.h"
#include <stdio.h>
#include <string.h>
describe (dfile_module) {

   struct dfile * pptr = 0;

   it (should create a storage file) { 
      assert(dfile_create("/tmp/data.dfile")==0);
   }

   it (should open an existing storage file) { 
      pptr = dfile_open("/tmp/data.dfile");
      assert(pptr!=0);
   }

   it (should fail to open an invalid file) { 
      struct dfile * err_pptr = 0;
      err_pptr = dfile_open("/tmp/invalid.dfile");
      assert(err_pptr==0);
   }

   it (should close an opened file) { 
      assert(dfile_close(pptr)==0);
   }

   it (should err trying to close invalid file) {
      assert(dfile_close(pptr)!=0); /* pptr was already closed */
   }

   it (should store records) { 
      dfile_create("/tmp/data.dfile");
      pptr = dfile_open("/tmp/data.dfile");
      long pos = dfile_store(pptr,"just a bunch of data",20);
      assert(pos!=-1);
      dfile_close(pptr);
   }

   it (should restore records) { 
      pptr = dfile_open("/tmp/data.dfile");
      char buf[21];
      int nread = dfile_restore(pptr,0,buf,20);
      buf[20] = 0;
      assert(strcmp(buf,"just a bunch of data")==0 & nread==1);
      dfile_close(pptr);
   }

}
