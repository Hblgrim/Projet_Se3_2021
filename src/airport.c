#include "header.h"

void print_airports(void *item) {
  if (item != NULL) {
    printf("%s", ((t_airport *)item)->to_string((t_airport *)item));
  }
}
void free_airport(void *item) {
  if (item != NULL) {
    t_airport *airport = (t_airport *)item;
    free(airport->airport_name);
    free(airport->city);
    free(airport->iata_code);
    free(airport->state);
    free(airport->country);
    free(airport);
  }
}

t_airport *new_airport(char *line) {
  t_airport *airport;
  t_array_list *data;
  char *str;
  char *ptr;

  if (line == NULL)
    return NULL;
  airport = (t_airport *)malloc(sizeof(t_airport));
  if (airport != NULL) {
    data = split(line, ',');

    if (data == NULL)
      return NULL;
    for (int i = 0; i < data->index; i++)
      if (data->get(data, i) == NULL)
        return NULL;
    if (data->index == 7) {
      str = data->get(data, 0);
      airport->iata_code = strdup(str);
      str = data->get(data, 1);
      airport->airport_name = strdup(str);
      str = data->get(data, 2);
      airport->city = strdup(str);
      str = data->get(data, 3);
      airport->state = strdup(str);
      str = data->get(data, 4);
      airport->country = strdup(str);
      str = data->get(data, 5);
      airport->latitude = atof(str);
      str = data->get(data, 6);
      airport->logitude = atof(str);
      airport->to_string = &airport_to_string;
      data->free(data, &free);
      free(data);
    } else
      return NULL;
  }
  return airport;
}

char *airport_to_string(t_airport *this) {
  char *str;
  t_string_builder *sb;

  if (this == NULL)
    return NULL;
  sb = new_string_builder_formated("%s, ", this->iata_code);
  if (sb == NULL)
    return NULL;
  sb->append_formated(sb, "%s, ", this->airport_name);
  sb->append_formated(sb, "%s, ", this->city);
  sb->append_formated(sb, "%s, ", this->state);
  sb->append_formated(sb, "%s, ", this->country);
  sb->append_formated(sb, "%.2f, ", this->latitude);
  sb->append_formated(sb, "%.2f", this->logitude);
  str = sb->to_string(sb);
  sb->free(sb);
  return str;
}