#include "header.h"

void print_data(t_data *data) {
  data->airports.foreach (&(data->airports), &print_airports);
  data->airlines.foreach (&(data->airlines), &print_airlines);
  data->flights.foreach (&(data->flights), &print_flights);
}
void init(t_data *data) {
  new_array_list(&data->airlines, 10, sizeof(t_airline));
  new_array_list(&data->flights, 10, sizeof(t_flight));
  new_array_list(&data->airports, 10, sizeof(t_airport));
  new_array_list(&data->errors, 5, sizeof(char *));
}

t_data *new_data() {
  t_data *data;

  if ((data = (t_data *)malloc(sizeof(t_data))) == NULL)
    return NULL;
  init(data); 
  return data;
}