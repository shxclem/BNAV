# PROJET BNAV ING1-GI2

![alt_text](https://github.com/shxclem/BNAV/blob/ressources/BNAV.jpg)


## Table des matières
1. [DESCRIPTION](#description)
2. [UTILISATION](#utilisation)
3. [DEROULEMENT](#deroulement)

## DESCRIPTION

BNAV est un projet visant à permettre à l'utilisateur de jouer au jeu de la bataille navale depuis le terminal.
Ce programme a été programmé dans le langage C.
La documentation du projet se trouve dans le dossier "html" dans le fichier "index.html".

## UTILISATION

Pour commencer, il faut compiler le programme en veillant à avoir les fichiers dans un même répertoire puis utiliser la commande suivant :
```c
  $ make
```
Une fois compilé, on peut lancer le programme avec la commande suivante :
```c
  $ ./bnav
```
## DEROULEMENT

Le déroulement d'une partie de bataille navale se fait en plusieurs phases :
  - Une phase de préparation où chaque joueur place plusieurs bateaux sur son plateau
  - Une phase de jeu où chacun leur tour, les joueurs vont lancer une bombe sur une case en espérant toucher un bateau ennemi
  - La partie se terminera donc quand un des deux joueurs n'aura plus de bateau en vie sur son plateau

Plusieurs modes de jeu sont disnonibles :
  - Jouer contre un vrai adversaire en local
  - Jouer contre un bot en mode normal
  - Jouer contre un bot en mode impossible

En ce qui concerne les commandes à utiliser lors du déroulement de la partie, il suffira simplement de suivre les indications.

#### CREATEUR

Ce projet a été par programmé par Clément DURECU (shxclem), élève en ING1 groupe GI2.
