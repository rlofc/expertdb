#include "c89spec/c89spec.h"
#include "../src/dfile.h"
#include <stdio.h>
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
       
   }

   it (should restore records) { 
       
   }

}
