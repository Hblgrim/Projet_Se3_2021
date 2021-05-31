#include "header.h"

extern t_data *data;
char *airport_id = NULL;
int month = -1;
int day = -1;
int limit = -1;
int current = 0;
int time = -1;

char *map_flights(void *item) {
  t_flight *flight = (t_flight *)item;

  return flight->to_string(flight);
}
t_bool filter_flights(void *item) {
  if (item == NULL || airport_id == NULL || month == -1 || day == -1)
    return FALSE;
  if (strcmp(airport_id, ((t_flight *)item)->org_air) == 0)
    if (((t_flight *)item)->day == day && ((t_flight *)item)->month == month)
      if (time == -1 || (time == (int)((t_flight *)item)->sched_dep)) {
        current++;
        return TRUE;
      }
  return FALSE;
}
void reset() {
  airport_id = NULL;
  month = -1;
  day = -1;
  limit = -1;
  current = 0;
  time = -1;
}

t_bool fill_flights_var(t_array_list *args) {
  char *str;
  airport_id = args->pop(args);
  char *date = args->pop(args);
  if (date == NULL || airport_id == NULL)
    return FALSE;
  t_array_list *da = split(date, '-');
  if (da->index != 2)
    return FALSE;
  month = atoi(da->get(da, 0));
  day = atoi(da->get(da, 1));
  da->free(da, &free);
  while ((str = args->pop(args)) != NULL) {
    if (strncmp(str, "limit", strlen("limit")) == 0) {
      limit = atoi(str + (strlen("limit") + 1));
    } else
      time = atoi(str);
    free(str);
  }
  return TRUE;
}

char *show_flights(t_array_list *args) {
  t_string_builder *sb;
  t_flight *flight;
  char *ptr;

  reset();
  if (args != NULL && args->index > 0 && args->index < 5) {
    if (!fill_flights_var(args))
      return NULL;
    sb = new_string_builder("");
    for (int i = 0; i < data->flights.index; i++) {
      flight = data->flights.get(&data->flights, i);

      if (filter_flights(flight)) {
        ptr = map_flights(flight);
        sb->append_formated(sb, "%s", ptr);
      }
      if (limit != -1 && limit == current)
        break;
    }
    ptr = sb->to_string(sb);
    sb->free(sb);
    return ptr;
  }
  return NULL;
}