#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Nov 29 16:21:02 2018

@author: Paul Festor
"""

from homemadeNet import Perceptron
from random import randint
import numpy as np
from random import random

class Bird():
    
    """
    Class qui représente un oiseau.
    
    Arrtibuts:
        - x, y: coordonnées dans le plan
        - canheight: hauteur du canevas dans leuel se passe le jeu
        - brain: perceptron qui prend le décisions pour l'oiseau:
            - entrées du réseau: distances verticale et horizontale entre l'oiseau et le milieu du prochain trou 
            - sorties: choix entre battre de l'aile et ne rien faire
        - gravity: intensité de la force de gravité qui n'exerce à chaque instant sur l'oiseau
        - velocity: vitesse verticae de l'oiseau
        - flapPower: piuissance d'un coup d'aile
        - radius: rayon du cercle qui représente l'oiseau sur l'interface graphique
        - isAlive: booléen "L'oiseau est-il en vie ?"
        - fitness: distance parcourrue par l'oiseau sans s'écraser dans un tuyau
    """
    
    def __init__(self, height):
        """
        Fonction d'initialisation
        """
        self.x = 50
        self.y = height//2
        self.canheight = height
        self.brain = Perceptron([2, 6, 2])
        #self.image = tk.PhotoImage(file="images/bird.gif")
        self.gravity = 1
        self.velocity = 0
        self.flapPower = 10
        self.radius = 5
        self.isAlive = True
        self.fitness = 0
        
    def show(self, can):
        """
        Affichage sur un canevas can
        """
        can.create_oval(self.x-self.radius, self.y-self.radius,\
                        self.x+self.radius, self.y+self.radius, fill="red")
        
    def update(self):
        """
        Cettte fonction est appelée à chaque instant, elle met à jour la position de
        l'oiseau en fonction de sa vitesse, de la gravité, de la résistance de l'air
        et des bordures de l'espace
        """
        self.y += self.velocity
        self.velocity += self.gravity
        self.velocity = self.velocity*0.8 # Résistance de l'air
        if self.y >= self.canheight: # Empèche l'oiseau d'aller plus bas que le sol
            self.y = self.canheight
            if self.velocity > 0:
                self.velocity = 0
        if self.isAlive: # Augmente le score tant que l'oiseau est vivant
            self.fitness += 0.1
    
    def birdUp(self, event = None):
        """
        Battre de l'aile, change la vitesse de l'oiseau
        """
        self.velocity = -self.flapPower
        
    def takeDecision(self, pipes):
        """
        Prendre une décision dans une situation donnée
        """
        for pipe in pipes: # Recherche du tuyau le plus proche
            if pipe.x > self.x:
                nextPipe = pipe
                break
        distances = distance(self.x, self.y, nextPipe.x, nextPipe.center) # Création du vecteur des distances au prochain trou
        info = self.brain.feedforward(distances) # On passe le vecteur des distances au réseau de neurones
        flap = np.argmax(info)
        # info est de taille 2 donc flap vaut 0 ou 1
        # Si flap vaut 1, l'oiseau bat de l'aile
        # Si flap vaut 0, il ne fait rien et se laisse tomber
        if flap:
            self.birdUp()
        
###############################################################################

class Pipe:
    """
    Classe qui représente les tuyaux que l'oiseau doit éviter.
    
    Attributs:
        - x: position sur l'axe horizontal
        - width: largeur du tuyau
        - holeheight: taille du trou dans lequel doit passer l'oiseau
        - center: hauteur du milieu du trou dans lequel doit passer l'oiseau
        - canheight: hauteur du canevas dans leuel se passe le jeu
        - speed: vitesse à laquelle le tuyau se déplace de la droite vers la gauche
        - color: couleur du tuyau
    """
    
    def __init__(self, height, width, pipewidth, holeheight):
        """
        Fonction d'initialisation
        """
        self.x = width
        self.width = pipewidth
        self.holeheight = holeheight
        self.center = randint(0, height-holeheight//2)
        self.canheight = height
        self.speed = 1
        self.color = "green"
        
    def show(self, can):
        """
        Affichage sur un canevas can
        """
        can.create_rectangle(self.x-self.width//2, 0,\
                             self.x+self.width//2, self.center-self.holeheight//2,\
                             fill=self.color)
        can.create_rectangle(self.x-self.width//2, self.canheight,\
                             self.x+self.width//2, self.center+self.holeheight//2,\
                             fill=self.color)
        
    def moveLeft(self):
        """
        Met à jour la position du tuyau
        """
        self.x -= self.speed
        
def isCollision(bird, pipe):
    """
    renvoie True si il ya sollision entre un oiseau et un tuyay
    """
    if ((bird.x + bird.radius > pipe.x - pipe.width//2 and bird.x - bird.radius < pipe.x + pipe.width//2)\
    and (bird.y + bird.radius > pipe.center + pipe.holeheight//2 or bird.y - bird.radius < pipe.center - pipe.holeheight//2)):
    #or bird.y + bird.radius >= bird.canheight:
        pipe.color = "blue"
        bird.isAlive = False

def distance(ax, ay, bx, by):
    """
    Crée le vecteur distaces donné au réseau de neurones d'un oiseau
    dx: distance algèbrique horizontale
    dy: distance algèbrique verticale
    """
    dx = (ax - bx)
    dy = (ay - by)
    return np.array([dx, dy])

def mixarrays(array1, array2):
    """
    Fonction appelée par le croisement de l'algorithme génétique.
    Mélange deux matrices de la manière suivante: pour chaque valeur, on choisit aléatoirement de copier un parent ou l'autre.
    """
    assert array1.shape == array2.shape
    shape = array1.shape
    mixedArray = np.zeros(shape)
    for itr in range(shape[0]):
        for jtr in range(shape[1]):
            if random() < 0.5:
                mixedArray[itr][jtr] = array1[itr][jtr]
            else:
                mixedArray[itr][jtr] = array1[itr][jtr]
    return mixedArray

def breed(bird1, bird2, height):
    """
    Fonction de croisement utilisée par l'algorithme génétique.
    """
    son = Bird(height)
    brain1_weight_matrices = bird1.brain.weights
    brain2_weight_matrices = bird2.brain.weights
    # Appelle la fonction mixarrays sur chacune des matrices de poids des réseaux de neurones
    for itr in range(len(brain1_weight_matrices)):
        son.brain.weights[itr] = mixarrays(brain1_weight_matrices[itr], brain2_weight_matrices[itr])
    return son
    

    

        