# Jeu de la vie

Voici le jeu de la vie codé en C

### Installation sous linux

Ce programme requiert les librairies :

1. SDL2
2. SDL2_ttf
3. assert
4. time
5. string
6. unistd
7. ctype

Les 5 dernières librairies sont probablement déjà dans votre système.

une fois installé la commande 
```
make
```
lancera la compilation

### Lancement

Vous pouvez lancer le programme grâce à la commande 
```
./main
```

vous pouvez également utiliser 
``` 
./main < motif.txt
```

ou encore 
```
cat motif.txt | ./main
```

pour charger un motif particulier

### Utilisation

Chacun des boutons de l'interface est cliquable.

Vous avez également des raccourcis clavier a votre dispotition :

 - CTRL (gauche) : dézoomer
 - MAJ (gauche) : zoomer
 - z,q,s,d ou les flèches directionnelles : se déplacer
 - c : centrer
 - p : accélérer la génération
 - m : ralentir la génération
 - k : copier le motif actuel dans le tampon
 - l : coller le motif du tampon
 - r : nettoyer la grille
 - echap : quitter le jeu

### Notes

Le jeu peut être très lent avec des grandes grilles
en fonction de votre ordinateur
