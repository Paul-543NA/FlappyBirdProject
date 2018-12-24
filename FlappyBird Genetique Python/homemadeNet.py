#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jul 14 10:21:17 2018

@author: Paul Festor
"""
import numpy as np
from random import shuffle
import matplotlib.pyplot as plt

class Perceptron:
    
    def __init__(self, sizes, seeEpochsProgression = False, 
                  cost = "mean_squared", savePlots = False):
        """
        Sizes contient le taille de chaque couche,
        la taillle de sizes est le nombre de couches
        
        cost: "cross_entropy" ou "mean_squared""
        """
        self.num_layers = len(sizes)
        self.sizes = sizes
        # Initialisation des piods et des biais
        self.biases = [np.random.randn(y, 1) for y in sizes[1:]]
        self.weights = [np.random.randn(y, x)
                        for (x, y) in zip(sizes[:-1], sizes[1:])]
        self.cost = cost
        self.successRatio = 0
        self.seeEpochsProgression = seeEpochsProgression
        self.savePlots = savePlots
        
        if seeEpochsProgression:
            self.epochsHistory = []
            self.costHistory = []
    
    def feedforward(self, a):
        """
        Calcule la sortie du reseau pour une entree a
        """
        a = a.reshape(self.sizes[0], 1)
        for (b, w) in zip(self.biases, self.weights):
            a = sigmoid(np.dot(w, a)+b)
        return a
    
    def SGD(self, training_data, epochs, mini_batch_size, eta,
            test_data=None, saveMistakes=False, saveSize=20, saveName="saves/mistake"):
        """
            training_data: liste de tuples de la forme (entree, sortie souhailee)
            
            Entraine le réseau de neurones en utilisant le descente de gradient
        """
        if test_data:
            n_test = len(test_data)
        n = len(training_data)
        # On itère autant de fois qu'il n'y a d'epoque
        for j in range(epochs):
            # On mélange les données d'entrainement
            shuffle(training_data)
            # On cre les sous ensembles sur lesquels on va calculer le gradient
            mini_batches = [training_data[k:k+mini_batch_size]
                            for k in range(0, n, mini_batch_size)]
            # Calcul du gradient et ajustement du reseau sur tous les sous
            # ensembles des données d'entrainement
            for mini_batch in mini_batches:
                self.update_mini_batch(mini_batch, eta)
            # Affichage des performances du reseau sur l'ensemble de test
            # Si il en existe un. Ce test se fain a la fin de chaque epoque
            if test_data:
                evalu, totalCost = self.evaluate(test_data)
                #print("Epoque {0}: {1} / {2}".format(j, evalu, n_test))
                self.successRatio = evalu
                if self.seeEpochsProgression:
                    self.epochsHistory.append(evalu)
                    self.costHistory.append(totalCost)
            else:
                print("Epoque {0} Terminee".format(j+1))
        if saveMistakes:
            self.saveMistakes(saveName, saveSize, test_data)
        if self.seeEpochsProgression:
            #plt.plot(self.costHistory)
            #x = np.arange(0, 10, 0.1)
            
            fig = plt.figure()
            
            y2 = self.costHistory
            y1 = [float(elt)/float(n_test) for elt in self.epochsHistory]
            
            fig, ax1 = plt.subplots()
            
            ax2 = ax1.twinx()
            ax1.plot(y1, 'b-')
            ax2.plot(y2, 'r-')
            
            ax1.set_xlabel("Epoques")
            ax1.set_ylabel("Taux d'images bien classifiees", color='b')
            ax2.set_ylabel("Cout", color='r')
            
            plt.show()
            
            if self.savePlots:
                fig.savefig("plots/"+str(epochs)+"_epochs"+"-"+str(self.sizes)+".png")
            
            
    def saveMistakes(self, saveName, saveSize, test_data):
        mistakesCount = 0
        itr = 0
        while itr < len(test_data) and mistakesCount < saveSize:
            (x, y) = test_data[itr]
            guess = np.argmax(self.feedforward(x))
            if y.any() != guess.any():
                filename = saveName + str(mistakesCount) + ".txt"
                file = open(filename, "w")
                writeData(file, x)
                file.close()
                mistakesCount += 1
            itr += 1
    
    def update_mini_batch(self, mini_batch, eta):
        """
        Met a jour le reseau de neurones en calculant ne gradient de la fonction
        cout sur l'ensemble mini_batch. Met ensuite le reseau a jour en retropropagant
        le gradient calcule
        """
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        # On iterre sur tout le sous ensemble
        for x, y in mini_batch:
            # Retropropagation
            delta_nabla_b, delta_nabla_w = self.backprop(x, y)
            nabla_b = [nb+dnb for (nb, dnb) in zip(nabla_b, delta_nabla_b)]
            nabla_w = [nw+dnw for (nw, dnw) in zip(nabla_w, delta_nabla_w)]
        # Apres avoir parcouru tout le sous ensemblen on met a jour les
        # parametres du reseau.
        self.weights = [w-(eta/len(mini_batch))*nw
                        for (w, nw) in zip(self.weights, nabla_w)]
        self.biases = [b-(eta/len(mini_batch))*nb
                         for (b, nb) in zip(self.biases, nabla_b)]
                                                   
    def backprop(self, x, y):
        """
        Algoeithme de retropropagation du gradient
        x, y: entrees de l'ensemble d'entrainement
        nabla_b, nabla_w:
        """
        # Creation des vecteurs
        nabla_b = [np.zeros(b.shape) for b in self.biases]
        nabla_w = [np.zeros(w.shape) for w in self.weights]
        # Liste qui stocke les acrivations a chaque couche du reseau
        liste_activations = [x]
        # Activation de la premiere couche
        activation = x
        # Liste des vecteurs z = w.a+b a chaque couche
        liste_z = []
        for (b, w) in zip(self.biases, self.weights):
            z = np.dot(w, activation)+b
            liste_z.append(z)
            activation = sigmoid(z)
            liste_activations.append(activation)
        # Debut de la retropropagation
        # Implemantation des formules demontrees dans le rapport
        delta = self.cost_derivative(liste_activations[-1], y) * \
        sigmoid_prime(liste_z[-1])
        nabla_b[-1] = delta
        nabla_w[-1] = np.dot(delta, liste_activations[-2].transpose())
        # Suite de la retropropagation
        # *Ici, l'indice l est pris en descendant
        for l in range(2, self.num_layers):
            z = liste_z[-l]
            sp = sigmoid_prime(z)
            delta = np.dot(self.weights[-l+1].transpose(), delta) * sp
            nabla_b[-l] = delta
            nabla_w[-l] = np.dot(delta, liste_activations[-l-1].transpose())
        return (nabla_b, nabla_w)
                                                                   
    def evaluate(self, test_data):
        """
        Renvoie le nombre de solutions correctement devinees par
        le reseau sur les donnees test. Le digit devine cirrespond
        a l'induce du neurone de la couche de sortie avec la plus
        grande activation.
        """
        score = 0
        totalCost = 0
        for (x, y) in test_data:
            a = self.feedforward(x)
            index_a = np.unravel_index(np.argmax(a, axis=None), a.shape)
            index_y = np.unravel_index(np.argmax(y, axis=None), y.shape)
            #print(index)
            totalCost += self.costFunction(a, y)
            if index_a == index_y:
                score += 1
        return score, totalCost
    
    def costFunction(self, output_activations, y):
        if self.cost == "mean_squared":
            return mean_squared_error(output_activations, y)
        elif self.cost == "cross_entropy":
            return cross_entropy_error_derviative(output_activations, y)
    
    def cost_derivative(self, output_activations, y):
        if self.cost == "mean_squared":
            return mean_squared_error_derviative(output_activations, y)
        elif self.cost == "cross_entropy":
            return cross_entropy_error_derviative(output_activations, y)
            


#### Fonction appliquée par un neurone, toutes les deux vectorielles
def sigmoid(z):
    return 1.0/(1.0+np.exp(-z))

def sigmoid_prime(z):
    return sigmoid(z)*(1-sigmoid(z))

def softmax(X):
    """
    Fonction softmax stabilisee numeriquement
    """
    exps = np.exp(X - np.max(X))
    return exps / np.sum(exps)

def softmax_prime(z):
    return sigmoid(z)*(1-sigmoid(z))

# Cost functions
def mean_squared_error(output_activations, y):
    return 0.5*sum((output_activations-y)**2)
    
def mean_squared_error_derviative(output_activations, y):
    """
    Calcule la derivee de la fonction cout quadratique
    """
    return (output_activations-y)
    
def cross_entropy_error_derviative(output_activations, y):
    """
    Calcule la derivee du cout cross_entropy
    """
#    m = y.shape[0]
#    grad = softmax(output_activations) - y
#    grad[range(m),y] -= 1
#    grad = grad/m
    return softmax(output_activations) - y

def writeData(file, data):
    dataStr = ';'.join([str(elt[0]) for elt in data])
    file.write(dataStr)

