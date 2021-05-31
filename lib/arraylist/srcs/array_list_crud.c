#include "array_list.h"

t_bool push(t_array_list *this, void *value, size_t size_of_item) { //ajouter un element dans une liste
  if (this != NULL)
    if (this->check_data_type(this, size_of_item)) {
      if (this->check_size(this)) {
        this->arr[this->index] = value;
        this->index++;
        return TRUE;
      } else if (this->new_array_double_size(this)) {
        this->arr[this->index] = value;
        this->index++;
        return TRUE;
      }
    }
  return FALSE;
}

t_bool update_at(t_array_list *this, void *value, size_t index) {

  if (index <= this->index) {
    this->arr[index] = value;
    return TRUE;
  }
  return FALSE;
}

void *get(t_array_list *this, size_t index) { //permet de prendre un element dans à un certain index i
  if (this->index > index)
    return this->arr[index];
  return NULL;
}

void _free(t_array_list *this, void (*fe)(void *item)) {
  if (this != NULL && fe != NULL)
    this->foreach (this, fe);
  this->index = 0;

  free(this->arr);
}

t_bool push_all(t_array_list *this, t_array_list original) {

  void *item;

  if (this == NULL || this->size_of_object != original.size_of_object)
    return FALSE;
  while ((item = original.pop(&original)) != NULL)
    this->push(this, item, original.size_of_object);
  return TRUE;
}
t_bool push_clone(t_array_list *this, t_array_list original,
                  t_bool is_not_primitive, void *(*__clone)(void *item)) {
  void *item;
  void *cln;

  if (this == NULL || this->size_of_object != original.size_of_object ||
      (is_not_primitive && __clone == NULL))
    return FALSE;
  while ((item = original.pop(&original)) != NULL) {
    if (is_not_primitive)
      cln = __clone(item);
    else {
      cln = malloc(sizeof(*cln));

      cln = memcpy(cln, item, sizeof(*cln));
    }
    this->push(this, cln, sizeof(*cln));
  }
  return true;
}
