#include "c89spec/c89spec.h"

void petri_module();

int main(int argc, char const *argv[])
{
   test(petri_module);
   return summary();
}
