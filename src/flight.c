#include "header.h"

void print_flights(void *item) {
  if (item != NULL) {
    printf("%s", ((t_flight *)item)->to_string((t_flight *)item));
  }
}

char *flight_to_string(t_flight *this) {
  char *str;
  t_string_builder *sb;

  if (this == NULL)
    return NULL;
  sb = new_string_builder_formated("%d, ", this->month);
  if (sb == NULL)
    return NULL;
  sb->append_formated(sb, "%d, ", this->day);
  sb->append_formated(sb, "%d, ", this->weekday);
  sb->append_formated(sb, "%s, ", this->airline);
  sb->append_formated(sb, "%s, ", this->org_air);
  sb->append_formated(sb, "%s, ", this->dest_air);
  sb->append_formated(sb, "%.2f, ", this->sched_dep);
  sb->append_formated(sb, "%.2f, ", this->dep_delay);
  sb->append_formated(sb, "%.2f, ", this->air_time);
  sb->append_formated(sb, "%.2f, ", this->dist);
  sb->append_formated(sb, "%.2f, ", this->sched_arr);
  sb->append_formated(sb, "%.2f, ", this->arr_delay);
  sb->append_formated(sb, "%d, ", this->diverted);
  sb->append_formated(sb, "%d", this->cancelled);
  str = sb->to_string(sb);
  sb->free(sb);
  return str;
}

t_flight *new_flight(char *line) {
  t_flight *flight;
  t_array_list *data;
  char *str;
  char *ptr;

  if (line == NULL)
    return NULL;
  flight = (t_flight *)malloc(sizeof(t_flight));
  if (flight != NULL) {
    data = split(line, ',');

    if (data == NULL)
      return NULL;
    for (int i = 0; i < data->index; i++)
      if (data->get(data, i) == NULL)
        return NULL;
    if (data->index == 14) {
      str = data->get(data, 0);
      flight->month = atoi(str);

      str = data->get(data, 1);
      flight->day = atoi(str);

      str = data->get(data, 2);
      flight->weekday = atoi(str);

      str = data->get(data, 3);
      flight->airline = strdup(str);

      str = data->get(data, 4);
      flight->org_air = strdup(str);

      str = data->get(data, 5);
      flight->dest_air = strdup(str);

      str = data->get(data, 6);
      flight->sched_dep = atof(str);
      str = data->get(data, 7);
      flight->dep_delay = atof(str);
      str = data->get(data, 8);
      flight->air_time = atof(str);
      str = data->get(data, 9);
      flight->dist = atof(str);
      str = data->get(data, 10);
      flight->sched_arr = atof(str);
      str = data->get(data, 11);
      flight->arr_delay = atof(str);
      str = data->get(data, 12);
      flight->diverted = atoi(str);
      str = data->get(data, 13);
      flight->cancelled = atoi(str);
      flight->to_string = &flight_to_string;
    } else
      return NULL;
  }
  return flight;
}