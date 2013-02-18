#ifndef STRING_H_TRYA1BAC
#define STRING_H_TRYA1BAC

#define INVALID_STR(str) str.value==0

struct string{
   char * value;
   size_t length;
} typedef string_t;

string_t     string_concat  (const char * base, ...);
void         string_destroy (string_t     str);
const char * string_tochar  (string_t     str);

#endif /* end of include guard: STRING_H_TRYA1BAC */
