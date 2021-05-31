#include "header.h"

extern t_data *data;
t_array_list *global_args;
t_flight *current_flight;
char *g_arg;

t_bool filter_flights_by_airport_id(void *item) {
  t_flight *flight;

  if (item == NULL)
    return FALSE;
  flight = (t_flight *)item;

  if (strcmp(flight->dest_air, g_arg) == 0)
    return TRUE;
  return FALSE;
}

t_bool show_airports_condition(void *item) {
  t_flight *flight;

  if (item == NULL)
    return FALSE;
  flight = (t_flight *)item;

  if (strcmp(flight->airline, g_arg) == 0)
    return TRUE;
  return FALSE;
}

t_bool contains(t_array_list list, char *code) {
  char *ss;

  for (int i = 0; i < list.index; i++) {
    ss = list.get(&list, i);

    if (strcmp(ss, code) == 0)
      return TRUE;
  }
  return FALSE;
}

t_array_list *filter_flights_by_dep_air(char *air_dep) {

  g_arg = air_dep;
  return data->flights.filter(data->flights, sizeof(t_flight),
                              &filter_flights_by_airport_id, NULL);
}

char *show_airports(t_array_list *args) {
  char *airline_id;
  t_array_list *flights;
  t_string_builder *sb;
  t_array_list used;
  t_airport *airport;
  t_flight *flight;
  char *ptr;
  global_args = args;

  new_array_list(&used, 10, sizeof(char *));
  airline_id = args->get(args, 0);
  g_arg = airline_id;
  sb = new_string_builder("");
  if (airline_id != NULL) {
    flights = data->flights.filter(data->flights, sizeof(t_flight),
                                   &show_airports_condition, NULL);

    while ((flight = flights->pop(flights)) != NULL) {

      for (int i = 0; i < data->airports.index; i++) {
        airport = data->airports.get(&data->airports, i);
        if (!contains(used, airport->iata_code) && airport != NULL)
          if (strcmp(airport->iata_code, flight->dest_air) == 0 ||
              strcmp(airport->iata_code, flight->org_air) == 0) {
            used.push(&used, strdup(airport->iata_code), sizeof(char *));
            ptr = airport->to_string(airport);
            if (ptr != NULL)
              sb->append_formated(sb, "%s\n", ptr);
            break;
          }
      }
    }
    flights->free(flights, &free);
    free(flights);
    used.free(&used, &free);
    ptr = sb->to_string(sb);
    sb->free(sb);
    return ptr;
  }
  global_args->free(global_args, &free);
  free(global_args);
  return NULL;
}

char *show_airlines(t_array_list *args) {
  char *airport_id;
  t_array_list *flights;
  t_string_builder *sb;
  t_array_list used;
  t_airline *airline;
  t_flight *flight;

  char *ptr;
  global_args = args;

  new_array_list(&used, 10, sizeof(char *));
  airport_id = args->get(args, 0);
  sb = new_string_builder("");
  g_arg = airport_id;
  if (airport_id != NULL) {
    flights = filter_flights_by_dep_air(airport_id);
    while ((flight = flights->pop(flights)) != NULL) {
      for (int i = 0; i < data->airlines.index; i++) {
        airline = data->airlines.get(&data->airlines, i);
        if (!contains(used, airline->iata_code) && airline != NULL)
          if (strcmp(airline->iata_code, flight->airline) == 0) {
            used.push(&used, strdup(airline->iata_code), sizeof(char *));
            ptr = airline->to_string(airline);
            if (ptr != NULL)
              sb->append_formated(sb, "%s\n", ptr);
            free(ptr);
            break;
          }
      }
    }
    flights->free(flights, &free);
    free(flights);
    used.free(&used, &free);
    ptr = sb->to_string(sb);
    sb->free(sb);
    return ptr;
  }

  global_args->free(global_args, &free);
  free(global_args);
  return NULL;
}
