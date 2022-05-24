# Super Q-Mario Bros

## Lancement du projet

- Pour lancer le projet, vous pouvez utiliser la commande
  `make start`

- Pour le compiler uniquement, la commande `make` suffit

- Pour nettoyer le dossier `make clean_objects` nettoie les fichiers objets et `make clean` nettoie en plus les fichiers binaires

### Au démarage du programme

- Sur la page d'accueil du jeu, la ou il y a marqué de presser n'importe quel bouton, si vous entrez le caractère `v`, cela activera les paramètres de Verbose avec entre autre des détails sur la matrice Q (ordre de grandeur des valeurs...).

## Details du projet

- le fichier **main.c** contient l'entrée du programme
  Tous les programmes utilisés dans le fichier `main.c`, sont regroupés dans le dossier _/src_.
- le fichier **agent.c** représente l'agent et contient les fonctions représentant l'agent et ses actions.
- le fichier **environment.c** représente l'environnement.
- le fichier **render.c** s'occupe d'afficher les différentes parties du projet, en particulier l'environnement.
- le fichier **policies.c** contient toutes les fonctions représentant les politiques que l'agent peut adopter.
- le fichier **utils.c**, contient plusieurs fonctions basiques, permmettant de calculer les maximum de listes, des conversions entre l'état et les coordonnées.

- le dossier _/levels_ contient l'ensemble des niveaux implémentés servant parfois de tests : `test.txt` est notre cas test pour pour voir l'environnement le plus simple qu'il soit, `basefree.txt` est un niveau sans trous et sans ennemis, `base.txt` est le même mais avec des ennemies et `basehole.txt` rajoute le trou. 

## Fermer le programme

- Pour fermer le programme en cours d'exécution, il suffit de rentrer la commande `qq`.
