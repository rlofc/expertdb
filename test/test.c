#include "c89spec/c89spec.h"

void petri_module();
void dfile_module();
void gstor_module();
void trax_module();

int main(int argc, char const *argv[])
{
   test(petri_module);
   test(dfile_module);
   test(gstor_module);
   test(trax_module);
   return summary();
}
