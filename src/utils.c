#include "header.h"

t_bool is_whitespace(char ch) {
  if (strchr(" \t\r", ch) != NULL)
    return TRUE;
  return FALSE;
}

t_array_list *split(char *line, char ch) {
  t_array_list *data;
  int i = 0;
  int lasti = 0;
  char *l;
  int size;

  data = (t_array_list *)malloc(sizeof(t_array_list));
  if (line == NULL || data == NULL)
    return NULL;
  size = strlen(line);
  data = new_array_list(data, 10, sizeof(char *));
  for (; line[i] != '\0' && is_whitespace(line[i]); i++)
    ;

  lasti = i;
  while (line[i] != '\0') {
    for (; line[i] != ch && line[i] != '\0'; i++)
      ;

    l = ft_substr(line, lasti, i - lasti);
    data->push(data, strdup(l), sizeof(char *));
    free(l);
    i++;
    lasti = i;
    if (i > size)
      break;
  }

  return data;
}