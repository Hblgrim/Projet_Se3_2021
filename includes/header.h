#ifndef HEADER_H
#define HEADER_H

#include "array_list.h"
#include "get_next_line.h"
#include "stringbuilder.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct s_airline {
  char *iata_code;
  char *airline;
  double retard_moyen;
  int nb_flights;
  char *(*to_string)(struct s_airline *this);

} t_airline;

typedef struct s_flight {
  int month;
  int day;
  int weekday;
  char *airline;
  char *org_air;
  char *dest_air;
  double sched_dep;
  double dep_delay;
  double air_time;
  double dist;
  double sched_arr;
  double arr_delay;
  int diverted;
  int cancelled;
  char *(*to_string)(struct s_flight *this);
  
} t_flight;

typedef struct s_airport {
  char *iata_code;
  char *airport_name;
  char *city;
  char *state;
  char *country;
  double latitude;
  double logitude;
  char *(*to_string)(struct s_airport *this);
 
} t_airport;

typedef struct s_data {
  t_array_list airports;
  t_array_list flights;
  t_array_list airlines;
  t_array_list errors;
} t_data;

typedef char *(*ex_cmd)(t_array_list *);

t_airline *new_airline(char *line);
t_flight *new_flight(char *line);
t_airport *new_airport(char *line);

t_data *new_data();

void put_error(char *error);
void parse_files();
// utils
t_array_list *split(char *line, char ch);
t_bool is_whitespace(char ch);

// airport
char *airport_to_string(t_airport *this);
void print_airports(void *item);
void print_airlines(void *item);
void print_flights(void *item);
void print_data(t_data *data);

char *show_airports(t_array_list *args);
char *show_airlines(t_array_list *args);
char *show_flights(t_array_list *args);
char *most_delayed_flights(t_array_list *args);
char *delayed_airline(t_array_list *args);
char *most_delayed_airlines_at_airport(t_array_list *args);
void sort_data();
char *changed_flights(t_array_list *args);
char *most_delayed_airlines(t_array_list *args);
t_bool contains(t_array_list list, char *code);
char *avg_flight_duration(t_array_list *args);

void free_airline(void *item);
void free_airport(void *item);
void free_flight(void *item);
#endif