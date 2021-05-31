
#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 100
char *ft_substr(char *s, unsigned int start, size_t len);
char *ft_strjoin(char *s1, char *s2);
char *ft_strchr(const char *s, int c);
char *search(int fd, char **rest, int *ret);
int get_next_line(int fd, char **line);
char *ft_strcpy(char *dest, char *src);
char *ft_strdup(char *src);
int find(char **line, char **rest, int retn);
size_t ft_strlen(const char *s);

#endif
