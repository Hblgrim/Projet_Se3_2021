#include "header.h"

void print_airlines(void *item) {
  if (item != NULL) {
    printf("%s", ((t_airline *)item)->to_string((t_airline *)item));
  }
}
void free_airline(void *item) {
  if (item != NULL) {
    t_airline *airline = (t_airline *)item;
    free(airline->iata_code);
    free(airline->airline);
    free(airline);
  }
}

char *airline_to_string(t_airline *this) {
  char *str;
  t_string_builder *sb;

  if (this == NULL)
    return NULL;
  sb = new_string_builder_formated("%s, ", this->iata_code);
  if (sb == NULL)
    return NULL;
  sb->append_formated(sb, "%s", this->airline);
  str = sb->to_string(sb);
  sb->free(sb);
  return str;
}

t_airline *new_airline(char *line) {
  t_airline *airline;
  t_array_list *data;
  char *str;
  char *ptr;

  if (line == NULL)
    return NULL;
  airline = (t_airline *)malloc(sizeof(t_airline));
  if (airline != NULL) {
    data = split(line, ',');

    if (data == NULL)
      return NULL;
    for (int i = 0; i < data->index; i++)
      if (data->get(data, i) == NULL)
        return NULL;
    if (data->index == 2) {

      str = data->get(data, 0);
      airline->iata_code = strdup(str);
      str = data->get(data, 1);
      airline->airline = strdup(str);
      airline->retard_moyen = 0;
      airline->nb_flights = 0;
      airline->to_string = &airline_to_string;
      data->free(data, &free);
      free(data);
    } else
      return NULL;
  }
  return airline;
}