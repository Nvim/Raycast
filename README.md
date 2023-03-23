# Raycast

## Moteur de rendu pseudo-3D C++/SDL2

### Description

Le but de ce projet est d'utiliser la technique du Raycasting pour afficher à l'écran une scène 3D à partir d'un "jeu" 2D, pour pouvoir créer des
jeux et rendus dans le style de Woflenstein 3D.

Pour l'instant, le programme affiche une scène 2D (vue de haut) composée d'un point que nous pouvons déplacer et de deux lignes 
superposées représentant son orientation dans l'espace. Le programme détecte la présence de murs dans le "champ de vision" du point et stoppe
le tracé des rayons (lignes) lorsqu'ils en atteignent un. L'un détecte les murs verticaux, et l'autre les murs horizontaux.
L'objectif est de tracer plusieurs rayons face au joueur pour créer un champ de vision, puis de calculer leurs longueurs et d'afficher
une colonne de pixels plus ou moins haute pour chaque rayon.

### Contrôles

Z,Q,S,D pour se déplacer, et les flèches gauche et droite pour tourer sur soi même.

### Compilation et Éxécution

Le programme fonctionne sous Linux et doit être compilé avec GCC. Il faut également avoir installé les bibliothèques ***SDL2***
et ***SDL2 Image***.

Pour compiler et éxécuter le programme: 

    make release && bin/release/main
    
Par défaut, le dossier 'obj' n'est pas traqué par Git.
