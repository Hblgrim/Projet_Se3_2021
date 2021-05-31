#include "header.h"
extern t_data *data;

void parse_air_lines() {
  int fd;
  char *line;
  t_airline *airline;

  fd = open("/home/b0n3/Desktop/cTest/data/airlines.csv", O_RDONLY);
  if (fd < 0)
    data->errors.push(&data->errors, "file : airlines.csv not found",
                      sizeof(char *));
  else {
    get_next_line(fd, &line);
    while (get_next_line(fd, &line) > 0) {
      if (line != NULL) {
        airline = new_airline(line);
        if (airline == NULL)
          data->errors.push(&data->errors, ft_strjoin("invalid line = >", line),
                            sizeof(char *));
        else
          data->airlines.push(&(data->airlines), airline, sizeof(t_airline));
      }
    }
  }
}

void parse_flights() {
  int fd;
  char *line;
  t_flight *flight;

  fd = open("/home/b0n3/Desktop/cTest/data/flights.csv", O_RDONLY);
  if (fd < 0)
    data->errors.push(&data->errors, "file : flights.csv not found",
                      sizeof(char *));
  else {
    get_next_line(fd, &line);
    while (get_next_line(fd, &line) > 0) {
      if (line != NULL) {
        flight = new_flight(line);
        if (flight == NULL)
          data->errors.push(&data->errors, ft_strjoin("invalid line = >", line),
                            sizeof(char *));
        else
          data->flights.push(&(data->flights), flight, sizeof(t_flight));
      }
    }
  }
}

void parse_air_ports() {
  int fd;
  char *line;
  t_airport *airport;

  fd = open("/home/b0n3/Desktop/cTest/data/airports.csv", O_RDONLY);
  if (fd < 0)
    data->errors.push(&data->errors, "file : airports.csv not found",
                      sizeof(char *));
  else {
    get_next_line(fd, &line);
    while (get_next_line(fd, &line) > 0) {
      if (line != NULL) {
        airport = new_airport(line);
        if (airport == NULL)
          data->errors.push(&data->errors, ft_strjoin("invalid line = >", line),
                            sizeof(char *));
        else
          data->airports.push(&(data->airports), airport, sizeof(t_airport));
      }
    }
  }
}

void parse_files() {
  parse_air_lines();
  parse_air_ports();
  parse_flights();
}
