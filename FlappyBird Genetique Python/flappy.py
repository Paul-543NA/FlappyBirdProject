#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 29 16:31:52 2018

@author: Paul Festor
"""

import tkinter as tk
from objects import Bird, Pipe, isCollision

width = 300 #300 Largeur de la fenêtre de jeu
height = 400 #400 Hauteur de la fenêtre de jeu
pipewidth = 30 #30 Largeur des tuyaux
holeheight = 100 #100 Taille des trous dans lesquels doit passer l'oiseau 
pipeFrequency = 150 #150 Fréquence à laquelle des tuyaux apparaisssent

framecount = 0

def lanceVisualisation(bird):
    """
    Lance une partie avec une interface graphique.
    L'oiseau passé en argument prendra la désision de battre de l'aile ou non à chaque instant.
    """
    global framecount
    main = tk.Tk()
    
    can = tk.Canvas(main, width=width, height=height) # Canevas dans leqiuel on dessine le jeu
        
    bird.show(can) # Affichage de l'oiseau
    pipes = list() # Liste de tous les tuyaux à l'écran
    can.pack()
    
    framecount = 0 # Compte le nombre d'images affichées
    
    def update():
        """
        Fonction de mise à jour du jeu et de l'image affichée.
        """
        global framecount
        if framecount%pipeFrequency == 0:
            # Toutes les pipeFrequency images, on rajouye un tuyau
            pipes.append(Pipe(height, width, pipewidth, holeheight))
        can.delete("all") # On efface l'anvienne imahe de la fenêtre
        
        # On supprime de la liste des tuyaux ceux qui ne sont sortis de l'écran
        for itr in range(len(pipes)-1, -1, -1):
            if pipes[itr].x + pipes[itr].width < 0:
                pipes.pop(itr)
                
        # Pour toue les tuyaux:
        for pipe in pipes:
            isCollision(bird, pipe) # On regarde si il y a collision avec l'oiseau
            pipe.moveLeft() # On déplace le tuyau vers la gauche
            pipe.show(can) # On affiche le tuyau à sa nouvelle position
            
        # Une fois que les tuyaux ont bougé ...
        bird.takeDecision(pipes) # On demande à l'oiseau de prendre une décision
        bird.update()            # On met à jour les caractéristiques de l'oiseau (vitesse, position) en fonction de la décision prise
        bird.show(can)           # On affiche l'oiseau à sa nouvelle position
        framecount += 1          # On inréments le nombre d'images de 1
        print(bird.isAlive)
        main.after(10, update)   # On réexécute cette fonction toutes les 10 ms
    
    main.bind("<KeyPress-space>", bird.birdUp) # Si un joueur humain veut avoir un impact, appuyer sur la barre espace fera monter l'oiseau
    
    update() # On lance les mises à jour successives du jeu
    main.mainloop()

#lanceVisualisation(Bird(400))