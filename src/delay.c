#include "header.h"
extern t_data *data;

char *most_delayed_flights(t_array_list *args) {
  t_string_builder *sb = new_string_builder("");
  char *ptr;

  for (int i = 0; i < 5 && i < data->flights.index; i++) {
    t_flight *flight = data->flights.get(&data->flights, i);
    if (flight != NULL) {
      ptr = flight->to_string(flight);
      sb->append_formated(sb, "%s\n", ptr);
      free(ptr);
    }
  }
  ptr = sb->to_string(sb);
  sb->free(sb);
  return ptr;
}

char *most_delayed_airlines(t_array_list *args) {
  t_string_builder *sb = new_string_builder("");
  char *ptr;

  for (int i = 0; i < 5 && i < data->airlines.index; i++) {
    t_airline *airline = data->airlines.get(&data->airlines, i);
    if (airline != NULL) {
      ptr = airline->to_string(airline);
      sb->append_formated(sb, "%s\n", ptr);
      free(ptr);
    }
  }
  ptr = sb->to_string(sb);
  sb->free(sb);
  return ptr;
}

char *delayed_airline(t_array_list *args) {
  char *airline_id = args->pop(args);
  char *ptr;
  t_string_builder *sb;
  t_airline *airline;

  if (airline_id == NULL)
    return NULL;
  sb = new_string_builder("");
  for (int i = 0; i < data->airlines.index; i++) {
    airline = data->airlines.get(&data->airlines, i);
    if (airline != NULL)
      if (strcmp(airline->iata_code, airline_id) == 0) {
        ptr = airline->to_string(airline);
        sb->append_formated(sb, "%s, %.1f\n", ptr, airline->retard_moyen);
        break;
      }
  }
  free(airline_id);
  args->free(args, &free);
  free(args);
  ptr = sb->to_string(sb);
  sb->free(sb);
  return ptr;
}

char *most_delayed_airlines_at_airport(t_array_list *args) {
  char *ptr;
  char *airport_id = args->pop(args);

  t_array_list used;
  int index = data->flights.index;
  t_flight *flight;
  t_string_builder *sb;

  if (airport_id == NULL)
    return NULL;

  sb = new_string_builder("");
  new_array_list(&used, 3, sizeof(char *));

  while (index >= 0) {
    flight = data->flights.get(&data->flights, index);
    if (flight != NULL) {
      if (strcmp(flight->dest_air, airport_id) == 0) {
        if (!contains(used, flight->airline)) {
          used.push(&used, strdup(flight->airline), sizeof(char *));
          for (int i = 0; i < data->airlines.index; i++) {
            t_airline *airline = data->airlines.get(&data->airlines, i);
            if (airline != NULL) {
              if (strcmp(flight->airline, airline->iata_code) == 0) {
                sb->append_formated(sb, "%s , %.2f\n",
                                    airline->to_string(airline),
                                    airline->retard_moyen);
              }
            }
          }
        }
      }
      if (used.index == 3)
        break;
    }
    index--;
  }
  ptr = sb->to_string(sb);
  sb->free(sb);
  used.free(&used, &free);
  args->free(args, &free);
  free(args);

  return ptr;
}

char *changed_flights(t_array_list *args) {
  char *date = args->pop(args);
  t_string_builder *sb;
  char *ptr;
  t_array_list *da;
  int month;
  int day;
  if (date == NULL)
    return NULL;
  da = split(date, '-');
  if (da->index != 2) {
    da->free(da, &free);
    return NULL;
  }
  sb = new_string_builder("");
  month = atoi(da->get(da, 0));
  day = atoi(da->get(da, 1));
  for (int i = 0; i < data->flights.index; i++) {
    t_flight *flight = data->flights.get(&data->flights, i);
    if (flight != NULL) {
      if (flight->day == day && flight->month == month &&
          (flight->cancelled == 1 || flight->diverted == 1)) {
        ptr = flight->to_string(flight);
        sb->append_formated(sb, "%s \n", ptr);
        free(ptr);
      }
    }
  }
  ptr = sb->to_string(sb);
  sb->free(sb);
  return ptr;
}