
# Application d’Analyse de vols

Ce dépôt GIT contient les documents livrés par Haitam Blgrim pour le projet de Programmation Avancée du Semestre 6 de la filière Systèmes Embarqués à Polytech Lille. Ce projet est codé en langage C , il consiste à la réalisation d’une application permettant à un utilisateur de réaliser des requêtes sur une base de données contenant des informations de 58492 vols aux Etats-Unis en 2014 .

## Contenu du dépôt :

- **README.md** : le fichier que vous êtes en train de lire .

- **Rapport.pdf** : Le rapport du projet .

- **Makefile** : permet la compilation du code métier (cible main) et des tests unitaires (cible tests) .

- **clang-format** : contient les règles de formatage de code .

- **Main.c** : contenant le programme principal .

- **Le répertoire data** : Contenant les fichiers de données CSV et la licence.

- **Le répertoire includes** : le répertoire includes contient les déclarations de fonctions dans fichier header.h

- **Le répertoire lib** : Contenant la librairie de fonctions définies , utilisé dans le programme .

- **Le répertoire src** : le répertoire src contient les fichiers sources .c du projet .


## Installation :

```
git clone https://github.com/Hblgrim/Projet_Se3_2021

cd Projet_Se3_2021
```

## Compilation

La commande **make all** compile tous les fichiers.

La commande **make clean** efface tous les fichiers objets et fichiers binaires.

La commande **make fclean** efface tous les fichiers créés par la compilation du projet.

La commande **make arraylist_re** recompile arraylist.

La commande **make stringbuilder_re** recompile stringbuilder.

la commande **make re_all** recompile tout.

## L’usage :

Pour exécuter le programme automatiquement, il suffit juste de taper la commande suivant : 
```
./projet_pa
```

### Le fonctionnement du programme :

1. Charger le fichier de données

2. Attendre une commande

3. Traiter la commande

4. Afficher le résultat de cette commande

5. Revenir à l'étape 2

### Les commandes :

- Afficher tous les aéroports depuis lesquels la compagnie aérienne <airline_id> opère des vols :
```
show-airports <airline_id>
````

- Afficher les compagnies aériens qui ont des vols qui partent de l'aéroport <port_id> :
```
show-airlines <port_id>
```

- Affiche les vols qui partent de l'aéroport à la date, avec optionnellement une heure de début, et limité à xx vols :
```
show-flights <port_id> <date> [<time>] [limit=<xx>] 
```

- Donner les 5 vols qui ont subis les plus longs retards à l'arrivée :
```
most-delayed-flights
```

- Donner les 5 compagnies aériennes qui ont, en moyenne, le plus de retards :
```
most-delayed-airlines
```

- Donner le retard moyen de la compagnie aérienne passée en paramètre :
```
delayed-airline <airline_id>
```

- Donner les 3 compagnies aériennes avec le plus de retard d'arrivée à l'aéroport passée en paramètre :
```
most-delayed-airlines-at-airport <airport_id>
```

- Trouver vols annulés ou déviés à la date (format M-D) :
```
changed-flights <date>
```

- Calculer le temps de vol moyen entre deux aéroports :
```
avg-flight-duration <port_id> <port_id>
```

- Trouver un ou plusieurs itinéraires entre deux aéroports à une date donnée (l'heure est optionnel, requête peut être limité à xx propositions, il peut y avoir des escales) :
```
find-itinerary <port_id> <port_id> <date> [<time>] [limit=<xx>]
```

- Afficher la liste des requêtes valides :
```
help
```

- Quitter le programme :
```
quit
```
