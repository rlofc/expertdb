#include "c89spec/c89spec.h"

void petri_module();
void dfile_module();

int main(int argc, char const *argv[])
{
   test(petri_module);
   test(dfile_module);
   return summary();
}
