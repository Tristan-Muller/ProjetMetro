# Tristan Muller 
# Merlin Fouché


# MAIN3      -       2022-2023
# Informatique générale


# ProjetMetro  


Ce dossier contient les fonctions nécessaires à la mise en place d'une simulation d'application 
    de carte de transport en communs, aidant l'utilisateur.rice à trouver son chemin entre deux stations

Le fichier Makefile permet l'exectution du programme, et contient les différentes instructions pour la compilations
    Pour compiler le programme, entrer $ make dans la ligne de commande
    Pour executer le programme, entrer $ make Do dans la ligne de commande

    Pour compiler le programme avec gdb, entre $ make debugg.o
    Pour lancer le programme avec gdb, entrer $ make Do_debugg
    Pour effacer les fichiers compilés, entrer $ make clean puis relancez les deux instructions précédentes


Les fichiers .c contiennent les fonctions permettant de réaliser le programme
Les fichiers .h contiennent les definitions des différentes structures utilisées dans le programme
Les gichiers .csv continennent les différentes informations nécéssaires comme les stations et leur positons, 
    leur nom, leur connexions, ou encore les diverses lignes du réseau considéré. 

Le fichier main.c est le fichier permettant de reunir toutes les fonctions dans le bon ordre, permettant au programme de fonctionner
