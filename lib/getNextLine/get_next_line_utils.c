
#include "get_next_line.h"

char *ft_strjoin(char *s1, char *s2) {
  int l1;
  int i;
  char *p;

  if (!s1 || !s2)
    return (NULL);
  l1 = strlen(s1);
  i = 0;
  p = malloc(sizeof(char *) * (l1 + strlen(s2)));
  if (p == 0)
    return (NULL);
  while (s1[i] != '\0') {
    p[i] = s1[i];
    i++;
  }
  i = 0;
  while (s2[i] != '\0') {
    p[i + l1] = s2[i];
    i++;
  }
  p[i + l1] = '\0';
  return (p);
}

char *search(int fd, char **rest, int *ret) {
  char *tmp;
  char *ptr;

  ptr = malloc(BUFFER_SIZE + 1);
  while (strchr(*rest, '\n') == NULL) {
    *ret = read(fd, ptr, BUFFER_SIZE);
    ptr[*ret] = '\0';
    tmp = ft_strjoin(*rest, ptr);
    free(*rest);
    *rest = strdup(tmp);
    free(tmp);
    if (*ret == 0)
      break;
  }
  free(ptr);
  return (*rest);
}
