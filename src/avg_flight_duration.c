#include "header.h"
extern t_data *data;

char *avg_flight_duration(t_array_list *args) {
  if (args == NULL)
    return NULL;
  t_flight *flight;
  double duration = 0;
  int nb_flights = 0;
  t_string_builder *sb;
  char *ptr;

  char *airport1_id = args->get(args, 0);
  char *airport2_id = args->get(args, 1);
  if (airport1_id == NULL || airport2_id == NULL)
    return NULL;
  sb = new_string_builder("");
  for (int i = 0; i < data->flights.index; i++) {
    flight = data->flights.get(&data->flights, i);
    if (flight != NULL)
      if ((strcmp(flight->dest_air, airport1_id) == 0 ||
           strcmp(flight->org_air, airport1_id) == 0) &&
          (strcmp(flight->dest_air, airport2_id) == 0 ||
           strcmp(flight->org_air, airport2_id) == 0)) {
        nb_flights++;
        duration = flight->air_time;
      }
  }
  if (nb_flights != 0)
    duration /= (double)nb_flights;
  sb->append_formated(sb, "average: %.2f minutes (%d flights)\n", duration,
                      nb_flights);

  ptr = sb->to_string(sb);
  sb->free(sb);
  return ptr;
}