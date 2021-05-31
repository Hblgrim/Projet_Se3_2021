#include "array_list.h"

t_bool al_empty(t_array_list *this, void (*fe)(void *item)) {
  void *ptr;

  if (this == NULL || fe == NULL)
    return FALSE;
  this->index--;
  while (this->index > 0) {
    ptr = this->get(this, this->index);
    fe(ptr);
    this->index--;
  }
  ptr = this->get(this, this->index);
  fe(ptr);
  return TRUE;
}