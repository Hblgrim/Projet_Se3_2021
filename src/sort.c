#include "header.h"

extern t_data *data;
int flights_conditions(void *item1, void *item2) {
  if (item1 == NULL || item2 == NULL)
    return 0;
  if (((t_flight *)item1)->arr_delay > ((t_flight *)item2)->arr_delay)
    return -1;
  if (((t_flight *)item1)->arr_delay < ((t_flight *)item2)->arr_delay)
    return 1;
  return 0;
}

int airlines_conditions(void *item1, void *item2) {
  t_airline *air1;
  t_airline *air2;

  if (item1 == NULL || item2 == NULL)
    return 0;
  air1 = (t_airline *)item1;
  air2 = (t_airline *)item2;
  if (air2->airline == NULL || air2->airline == NULL)
    return 0;
  if (air1->retard_moyen > air2->retard_moyen)
    return -1;
  if (air1->retard_moyen < air2->retard_moyen)
    return 1;
  return 0;
}

void sort_data() {
  t_airline *airline;
  t_flight *flight;

  // sort flights from least arr_delay to high arr-dely
  data->flights.sort(&data->flights, flights_conditions, 0,
                     data->flights.index - 1);
  // calcul dial retard moyen
  for (int i = 0; i < data->airlines.index; i++) {
    airline = data->airlines.get(&data->airlines, i);
    if (airline != NULL)
      for (int j = 0; j < data->flights.index; j++) {
        flight = data->flights.get(&data->flights, j);
        if (flight != NULL) {
          if (strcmp(flight->airline, airline->iata_code) == 0) {
            airline->nb_flights++;
            airline->retard_moyen += flight->arr_delay;
          }
        }
      }
    airline->retard_moyen = airline->retard_moyen / airline->nb_flights;
  }

  // tartib dial airlines 3la hassab retart_moyen mn lkbir l sghir

  data->airlines.sort(&data->airlines, airlines_conditions, 0,
                      data->airlines.index - 1);
}