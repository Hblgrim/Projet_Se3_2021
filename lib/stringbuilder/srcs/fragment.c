#include "stringbuilder.h"
t_fragment *new_fragment(char *str, size_t length, size_t length_before) {//donne un new fragment
  t_fragment *fragment;
  if (str == NULL)
    return NULL;
  fragment = (t_fragment *)malloc(sizeof(t_fragment));
  if (fragment == NULL)
    return NULL;
  fragment->str = (char *)malloc(length);
  if (fragment->str == NULL) {
    free(fragment);
    return NULL;
  }
  memcpy(fragment->str, str, length);
  fragment->lenght_before = length_before;
  fragment->length = length;
  fragment->free = &fragment_free;
  return fragment;
}

void fragment_free(t_fragment *this) { //faire un free de fragment
  if (this == NULL)
    return;
  free(this->str);
  free(this);
}
