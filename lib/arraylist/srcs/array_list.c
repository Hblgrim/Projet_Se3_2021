#include "array_list.h"

t_array_list *new_array_list(t_array_list *this, size_t first_size,
                             size_t __sizeofit) { //alloue une place pour une new_arraylist càd nouvelle liste
  this->arr = malloc(first_size * __sizeofit);
  if (this->arr != NULL) {
    this->index = 0;
    this->length = first_size;
    this->size_of_object = __sizeofit;
    this->push = &push;

    this->get = &get;
    this->check_size = &check_size;
    this->check_data_type = &check_data_type;
    this->new_array_double_size = &new_array_double_size;
    this->foreach = &foreach;

    this->sort = &sort;
    this->free = &_free;
    this->update_at = &update_at;
    this->swap = &ft_swap;
    this->pop = &pop;

    this->empty = &al_empty;
    this->filter = &filter_list;
    return this;
  }
  return NULL;
}

void foreach (t_array_list *this, void (*f)(void *item)) { //repeter la meme operation pour tous les elements
  size_t i;

  i = 0;
  while (i < this->index) {
    if (this->arr[i] != NULL)
      f(this->arr[i]);
    i++;
  }
}

void ft_swap(void **a, void **b) { //swap 2 elements
  void *temp;
  temp = *a;
  *a = *b;
  *b = temp;
}
