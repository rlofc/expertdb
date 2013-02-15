#include "c89spec/c89spec.h"
#include "../src/petri.h"
#include <stdio.h>
describe (petri_module) {
   struct petri * pptr = 0;
   it (should create a petri file) {
      assert(petri_create("/tmp/index.petri")==0);
   }

   it ( should properly bootstrap a petri file ) {
      assert(petri_version("/tmp/index.petri")>0);
   }

   it (should open a precreated petri file) {
      pptr = petri_open("/tmp/index.petri");
      assert(pptr!=0);
   }

   it (should not open a non-petri file) {
      struct petri * err_pptr = 0;
      err_pptr = petri_open("/tmp/invalid.petri");
      assert(err_pptr==0);
   }

   it (should close an opened petri file) {
      assert(petri_close(pptr)==0);
   }

   it (should err trying to close invalid file) {
      assert(petri_close(pptr)!=0); /* pptr was already closed */
   }

   it (should index a value in a petri file) {
      petri_create("./index.petri");
      pptr = petri_open("./index.petri");
      petri_set(pptr, "key1",1000);
      petri_set(pptr, "key2",2000);
      petri_set(pptr, "key12",3000);
      long data = 0;
      assert ( petri_get(pptr, "key12",&data) == 0 && data == 3000 );
      petri_close(pptr);
   }

   it (should replace an indexed value in a petri file) {

   }

   it (should deal with hash collisions gracefully) {

   }

   it (should remove an index from a petri file) {

   }
}

