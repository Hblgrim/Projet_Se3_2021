#include "header.h"
extern t_data *data;

void parse_air_lines() {
  int fd;
  char *line;
  t_airline *airline;

  fd = open("./data/airlines.csv", O_RDONLY);  //lire fichier
  if (fd < 0)
    data->errors.push(&data->errors, "file : airlines.csv not found",    //push qu'il ya un erreur
                      sizeof(char *));
  else {
    get_next_line(fd, &line);  //saut de la premiere ligne celle contenant les titres
    free(line);
    while (get_next_line(fd, &line) > 0) {  //lire ligne par ligne
      if (line != NULL) {
        airline = new_airline(line); //alloue la place à un airline apres split data par (,) apres charge data 
        if (airline == NULL)
          data->errors.push(&data->errors, ft_strjoin("invalid line = >", line), 
                            sizeof(char *));                                      //push l'existence d'un erreur dans une ligne
        else                                                              // si y'a pas d'erreur
          data->airlines.push(&(data->airlines), airline, sizeof(t_airline)); //push airline càd la ligne lu dans data airlines (la liste des airlines)
        free(line);
      }
      
    }
    free(line);
  }
}

void parse_flights() {
  int fd;
  char *line;
  t_flight *flight;

  fd = open("./data/flights.csv", O_RDONLY);    //lire fichier
  if (fd < 0)
    data->errors.push(&data->errors, "file : flights.csv not found", 
                      sizeof(char *));                                     //push qu'il ya un erreur
  else {
    get_next_line(fd, &line);     //saut de la premiere ligne celle contenant les titres
    free(line);
    while (get_next_line(fd, &line) > 0) {   //lire ligne par ligne
      if (line != NULL) {
        flight = new_flight(line);  //alloue la place à un flight apres split data par (,) apres charge data 
        if (flight == NULL)
          data->errors.push(&data->errors, ft_strjoin("invalid line = >", line),
                            sizeof(char *));                     //push l'existence d'un erreur dans une ligne
        else                                                           // si y'a pas d'erreur
          data->flights.push(&(data->flights), flight, sizeof(t_flight)); //push flight( càd la ligne lu) dans data flights (la liste des flights)
      free(line);
      }
    }
    free(line);
  }
}

void parse_air_ports() {
  int fd;
  char *line;
  t_airport *airport;

  fd = open("./data/airports.csv", O_RDONLY);    //lire fichier
  if (fd < 0)
    data->errors.push(&data->errors, "file : airports.csv not found",
                      sizeof(char *));                                       //push qu'il ya un erreur 
  else {
    get_next_line(fd, &line);  //saut de la premiere ligne celle contenant les titres
    free(line);
    while (get_next_line(fd, &line) > 0) {  //lire ligne par ligne
      if (line != NULL) {
        airport = new_airport(line);   //alloue la place à un airport apres split data par (,) apres charge data 
        if (airport == NULL)
          data->errors.push(&data->errors, ft_strjoin("invalid line = >", line),
                            sizeof(char *));                                             //push l'existence d'un erreur dans une ligne
        else                                                                   // si y'a pas d'erreur
          data->airports.push(&(data->airports), airport, sizeof(t_airport)); //push airport (càd la ligne lu) dans data airports (la liste des airlines
        free(line);
      }
    }
    free(line);
  }
}

void parse_files() {
  parse_air_lines();
  parse_air_ports();
  parse_flights();
}
