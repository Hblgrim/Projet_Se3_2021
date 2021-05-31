
#include "get_next_line.h"

char *ft_substr(char *s, unsigned int start, size_t len) {
  char *p;
  unsigned int i;

  i = 0;
  if (!s)
    return (NULL);
  if (strlen(s) < start)
    len = 0;
  p = malloc(len + 1);
  if (p == NULL)
    return (0);
  while (len--) {
    p[i] = s[start];
    i++;
    start++;
  }
  p[i] = '\0';
  return (p);
}

int find(char **line, char **rest, int retn) {
  int len;
  char *tmp;
  char *ptr;

  if (retn == 1) {
    tmp = strchr(*rest, '\n');
    len = tmp - *rest;
    *line = ft_substr(*rest, 0, len);
    ptr = strdup(*rest + (len + 1));
    free(*rest);
    *rest = strdup(ptr);
    free(ptr);
  } else {
    *line = strdup(*rest);
    free(*rest);
    *rest = NULL;
  }
  return (retn);
}

int get_next_line(int fd, char **line) {
  static char *rest[255];
  int ret;

  ret = 0;
  if (fd < 0 || line == NULL || read(fd, NULL, 0) != 0)
    return (-1);
  if (!rest[fd])
    rest[fd] = strdup("");
  search(fd, &rest[fd], &ret);
  if (strchr(rest[fd], '\n'))
    return (find(&line[0], &rest[fd], 1));
  else if (ret == 0)
    return (find(&line[0], &rest[fd], 0));
  return (0);
}
