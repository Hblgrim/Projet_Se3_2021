#include "stringbuilder.h"

size_t sb_append_va_args(t_string_builder *this, char *format, va_list args) {
  size_t len = 0;
  char *buf;

  if (this == NULL || format == NULL)
    return -1;
  buf = malloc(SB_MAX_LENGTH);

  len = vsnprintf(buf, SB_MAX_LENGTH, format, args);
  if (len < 0)
    return SB_FAILURE;
  len = this->append(this, buf);
  free(buf);
  return len;
}

t_string_builder *new_string_builder(char *str) {
  t_string_builder *sb;

  if (str == NULL)
    return NULL;
  sb = new_empty_string_builder();
  if (sb == NULL)
    return NULL;
  sb->append(sb, str);
  return sb;
}

t_string_builder *new_string_builder_formated(char *format, ...) {
  t_string_builder *sb;
  va_list args;

  if (format == NULL)
    return NULL;
  sb = new_empty_string_builder();
  if (sb == NULL)
    return NULL;
  va_start(args, format);
  sb_append_va_args(sb, format, args);
  va_end(args);
  return sb;
}

t_string_builder *new_empty_string_builder() {
  t_string_builder *sb;

  sb = (t_string_builder *)malloc(sizeof(t_string_builder));
  if (sb == NULL)
    return NULL;
  new_array_list(&sb->fragments, 2, sizeof(t_fragment));
  if (sb->fragments.arr == NULL) {
    free(sb);
    return NULL;
  }
  sb->append = &sb_append;
  sb->append_formated = &sb_append_formated;
  sb->length = 0;
  sb->to_string = &sb_to_string;
  sb->free = &sb_free;
  sb->empty = &sb_empty;
  return sb;
}

size_t sb_append(t_string_builder *this, char *str) {
  t_fragment *fragment;

  if (this == NULL || str == NULL)
    return -1;
  fragment = new_fragment(str, strlen(str), this->length);
  if (fragment == NULL)
    return SB_FAILURE;
  this->length += fragment->length;
  if (!this->fragments.push(&this->fragments, fragment, sizeof(t_fragment)))
    return SB_FAILURE;
  return fragment->length;
}

size_t sb_append_formated(t_string_builder *this, char *format, ...) {
  va_list args;
  size_t len = 0;
  if (this == NULL || format == NULL)
    return -1;
  va_start(args, format);
  len = sb_append_va_args(this, format, args);
  va_end(args);
  return len;
}

char *sb_to_string(t_string_builder *this) {
  char *ret;
  t_fragment *fragment;

  if (this == NULL)
    return strdup("");
  ret = (char *)malloc(this->length + 1);
  for (int i = 0; i < this->fragments.index; i++) {
    fragment = this->fragments.get(&this->fragments, i);

    if (fragment != NULL)
      memcpy(ret + fragment->lenght_before, fragment->str, fragment->length);
  }

  ret[this->length] = '\0';
  return ret;
}

void sb_empty(t_string_builder *this) {
  if (this == NULL)
    return;
  this->fragments.empty(&this->fragments, &fragment_free);
  this->length = 0;
}

void sb_free(t_string_builder *this) {
  if (this == NULL)
    return;
  this->fragments.free(&this->fragments, &fragment_free);
  free(this);
}
