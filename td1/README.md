# CMaze

Ce dossier contient l'exemple fait en TD du labyrinthe résolu avec les différentes méthodes de qlearning.

## Lancement du répertoire

- `make start` pour lancer le projet principal (q-learning simple)
- `make` pour compiler les différentes versions
- `make clean_objects` pour supprimer les fichiers objects et `make clean` pour supprimer en plus les fichiers binaires
- Les différents fichiers exécutables résultant de la compilation renvoient vers les différentes méthodes de qlearning : `solveur` qui utilise la méthode de Q-learning classique, `solveur2` qui utilise la méthode de double Q-learning et enfin `sarsa` qui utilise la méthode du SARSA.

- Ces différents fichiers peuvent résoudre les labyrinthes contenus dans le dossier _/src_.
- Pour sélectionner le labyrinthe, il faut modifier la source du fichier dans chaque main associé à la méthode souhaitée.
