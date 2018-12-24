#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Dec  1 18:16:48 2018

@author: Paul Festor
"""
import tkinter as tk
from objects import Bird, Pipe, isCollision, breed
from flappy import width, height, pipewidth, holeheight, pipeFrequency, lanceVisualisation

def run(aliveBirdPopulation, prints = False):
    """
    Fait jouer une population d'oiseaux, sans interface graphique pour gagner du temps.
    La variable prints décide de l'affichage ou non d'informations utiles au déboggage
    """
    pipes = list()    
    
    framecount = 0
    deadBirdPopulation = list()
    
    while aliveBirdPopulation:
        # Tant que tous les oiseaux ne sont pas morts
        if prints: print('# Creating new pipes')
        if framecount%pipeFrequency == 0:
            pipes.append(Pipe(height, width, pipewidth, holeheight))
        if prints: print('# Removing offscreen pipes')
        for itr in range(len(pipes)-1, -1, -1):
            if pipes[itr].x + pipes[itr].width < 0:
                pipes.pop(itr)
            else:
                pipes[itr].moveLeft()
        for itr in range(len(aliveBirdPopulation)-1, -1, -1):
            if prints: print('# Bitd {} updates'.format(itr))
            bird = aliveBirdPopulation[itr]
            # Checking for collisions
            bird.takeDecision(pipes)
            bird.update()
            for pipe in pipes:
                if prints: print("Test Collision")
                isCollision(bird, pipe)
            if not bird.isAlive:
                deadBirdPopulation.append(aliveBirdPopulation.pop(itr))
        
        framecount += 1
        if prints: print(framecount)
    
    # Recherche et éventuellement affichage des meilleures performrnces
    fitnesses = sorted([bird.fitness for bird in deadBirdPopulation])
    if prints: print(max(fitnesses), sum(fitnesses)/len(fitnesses))
    if prints: print(fitnesses[:5])
    return deadBirdPopulation

def select(population, ratio):
    """
    Etape de sélection de l'algorithme génétique.
    0 < ratio < 1 est la proportion d'oiseaux conservés d'une génération à l'autre
    """
    cutindex = int(ratio * len(population))
    # Tri de la population par ordre décroissants des scores individuels
    population = sorted(population, key = lambda x: -x.fitness)
    return population[:cutindex]

def enlarge(population, desired_size):
    """
    Etage de repopulation: prend une population réduite par la sélection et
    l'ggrandit par croisements jusqu'à atteindre la taille souhaitée.
    """
    current_size = len(population)
    for itr in range(current_size):
        for jtr in range(itr, current_size):
            if current_size > desired_size:
                break
            population.append(breed(population[itr], population[jtr], height))
            current_size += 1
    return population

epochs = 10 # Nombre d'époques d'entrainement
pop_size = 5000 # Taille de la population
birdPolulation = [Bird(height) for itr in range(pop_size)] # Initialisation de la population
for itr in range(epochs):
    # Evaluation des individus dans uns simulation
    birdPolulation = run(birdPolulation)
    
    fitnesses = sorted([bird.fitness for bird in birdPolulation]) # Liste par ordre décroissant des scores
    print(itr, max(fitnesses), sum(fitnesses)/len(fitnesses)) # Affichage du meilleur score et du score moyen à chaque époque
    
    # Sélection des meileur individus
    birdPolulation = select(birdPolulation, 0.3)
    
    # Croisement et repopulation
    birdPolulation = enlarge(birdPolulation, pop_size)


# Recherche du meilleur oiseau
for bird in birdPolulation:
    if bird.fitness == max(fitnesses):
        best_bird = bird
# Pour finir, on lance une simulation du jeu aec interface graphique pour voir le comportement du meilleur individu produit    
lanceVisualisation(best_bird)
