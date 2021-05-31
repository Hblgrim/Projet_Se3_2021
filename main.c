#include "header.h"

t_data *data;
char *usage;
t_array_list commands;

void init_usage() {
  t_string_builder *usage_sb;
  usage_sb = new_string_builder("usage:\n");
  if (usage_sb != NULL) {
    usage_sb->append(
        usage_sb,
        "\tshow-airports <airline_id>  :\n\t\t affiche tous les aéroports "
        "depuis lesquels la compagnie aérienne <airline_id> opère des vols\n");
    usage_sb->append(
        usage_sb,
        "\tshow-airlines <port_id>:\n\t\t affiche les compagnies aériens qui "
        "ont des vols qui partent de l'aéroport <port_id>\n");
    usage_sb->append(
        usage_sb,
        "\tshow-flights <port_id> <date> [<time>] [limit=<xx>] :\n\t\t affiche "
        "les vols qui partent de l'aéroport à la date, avec optionnellement "
        "une heure de début, et limité à xx vols\n");
    usage_sb->append(usage_sb,
                     "\tmost-delayed-flights:\n \t\t donne les 5 vols qui ont "
                     "subis les plus longs retards à l'arrivée\n");
    usage_sb->append(usage_sb,
                     "\tmost-delayed-airlines:\n\t\t donne les 5 compagnies "
                     "aériennes qui ont, en moyenne, le plus de retards\n");
    usage_sb->append(usage_sb,
                     "\tdelayed-airline <airline_id>: \n\t\t donne le retard "
                     "moyen de la compagnie aérienne passée en paramètre\n");
    usage_sb->append(usage_sb,
                     "\tmost-delayed-airlines-at-airport <airport_id> :\n \t\t "
                     "donne les 3 compagnies aériennes avec le plus de retard "
                     "d'arrivé à l'aéroport passée en paramètre\n");
    usage_sb->append(usage_sb, "\tchanged-flights <date>:\n \t\t les vols "
                               "annulés ou déviés à la date  (format M-D)\n");
    usage_sb->append(usage_sb,
                     "\tavg-flight-duration <port_id> <port_id>:\n\t\t calcule "
                     "le temps de vol moyen entre deux aéroports\n");
    usage_sb->append(
        usage_sb,
        "\tfind-itinerary <port_id> <port_id> <date> [<time>] "
        "[limit=<xx>]:\n\t\t trouve un ou plusieurs itinéraires entre deux "
        "aéroports à une date donnée (l'heure est optionnel, requête peut être "
        "limité à xx propositions, il peut y avoir des escales)\n");
    usage_sb->append(
        usage_sb, "\tfind-multicity-itinerary <port_id_depart> <port_id_dest1> "
                  "<date> [<time>] <port_id_dest2> <date> [<time>] ... "
                  "<port_id_destN> <date> [<time>]:\n\t\t trouve un itinéraire "
                  "multiville qui permet de visiter plusieurs villes (il peut "
                  "y avoir des escales pour chaque vol intermediaire)\n");
    usage_sb->append(usage_sb, "quit:\n\t quit\n");
    usage = usage_sb->to_string(usage_sb);
    usage_sb->free(usage_sb);
  }
}
void init_commands() {
  new_array_list(&commands, 7, sizeof(char *));
  commands.push(&commands, strdup("show-airports"), sizeof(char *));
  commands.push(&commands, strdup("show-airlines"), sizeof(char *));
  commands.push(&commands, strdup("show-flights"), sizeof(char *));
  commands.push(&commands, strdup("most-delayed-flights"), sizeof(char *));
  commands.push(&commands, strdup("most-delayed-airlines"), sizeof(char *));
  commands.push(&commands, strdup("delayed-airline"), sizeof(char *));
  commands.push(&commands, strdup("most-delayed-airlines-at-airport"),
                sizeof(char *));
  commands.push(&commands, strdup("changed-flights"), sizeof(char *));
  commands.push(&commands, strdup("avg-flight-duration"), sizeof(char *));
}
void print_errors(void *item) {
  if (item != NULL) {
    printf("%s\n", (char *)item);
  }
}
char *bad_command(t_array_list *c) { return strdup("error\n"); }

void print_usage(char *command) {
  printf("%s : command not found   \n", command);
  if (usage != NULL)
    printf("%s\n", usage);
}

t_bool is_empty(char *line) {
  if (line == NULL)
    return TRUE;
  if (line[0] == 0)
    return TRUE;
  return FALSE;
}

t_array_list *parse_line(char *line) {
  t_array_list *data;
  char *cmd;
  int index = -1;
  char *def_cmd;

  if (line == NULL || is_empty(line))
    return NULL;
  data = split(line, ' ');
  cmd = data->get(data, 0);
  for (int i = 0; i < commands.index; i++) {
    def_cmd = commands.get(&commands, i);
    if (strcmp(def_cmd, cmd) == 0) {
      index = i;
      break;
    }
  }
  if (index != -1)
    return data;
  if (data != NULL) {
    data->free(data, &free);
    free(data);
  }
  return NULL;
}
int get_index(char *cmd) {
  char *str;
  for (int i = 0; i < commands.index; i++) {
    str = commands.get(&commands, i);
    if (str == NULL)
      continue;
    if (strcmp(str, cmd) == 0)
      return i;
  }
  return -1;
}

ex_cmd excecute(char *cmd) {
  int index = get_index(cmd);
  switch (index) {
  case 0:
    return &show_airports;
  case 1:
    return &show_airlines;
  case 2:
    return &show_flights;
  case 3:
    return &most_delayed_flights;
  case 4:
    return &most_delayed_airlines;
  case 5:
    return &delayed_airline;
  case 6:
    return &most_delayed_airlines_at_airport;
  case 7:
    return &changed_flights;
  case 8:
    return &avg_flight_duration;
  default:
    return &bad_command;
  }
}

t_bool excecute_command(t_array_list *command) {
  char *cmd;

  if (command != NULL) {
    cmd = command->pop(command);
    if (cmd != NULL) {
      char *line = excecute(cmd)(command);
      if (line == NULL)
        return FALSE;
      printf("%s", line);
      free(line);
      return TRUE;
    }
  }
  return FALSE;
}
void free_data()
{
  if (data != NULL)
  {
    data->airlines.free(&data->airlines, &free_airline);
    data->airports.free(&data->airports, &free_airport);
    data->flights.free(&data->flights, &free_flight);
    data->errors.free(&data->errors, &free);
    free(data);
  }
}
int main() {
  char *line;
  t_array_list *command;

  init_usage();
  init_commands();
  data = new_data();
  parse_files();
  if (data->errors.index > 0)
    data->errors.foreach (&data->errors, &print_errors);
  sort_data();
  write(1, ">", 1);

  while (get_next_line(0, &line) > 0) {
    if (is_empty(line)) {
      write(1, ">", 1);
      continue;
    }
    if (strncmp(line, "quit", 4) == 0)
      break;
    if ((command = parse_line(line)) == NULL)
      print_usage(line);
    else if (!excecute_command(command))
      printf("missing args \n %s\n", usage);
    write(1, ">", 1);
    free(line);
   
  }
  free_data();
  exit(0);
}
