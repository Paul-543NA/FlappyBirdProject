//
//  Matrix.hpp
//  FlappyBird Genetique C++
//
//  Created by Paul on 31/12/2018.
//  Copyright © 2018 Paul. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>

#endif /* Matrix_hpp */

class Matrix{
    
/*
 TODOLIST:
  - Initialisations particulieres (0, 1, random)
  - Corriger les bugs avec les operateurs
  - Faire le constructeur par copie
  - Faire un fichier test pour la classe
 */
    
public:
    
    // Constructeur
    Matrix(int m, int n);
    
    // Destrusteur
    ~Matrix();
    
    // Taille de la matrice
    int* shape() const;
    
    // Affichage
    void print() const;
    
    // Acces a une valeur de la matrice
    float val(int m, int n) const{return m_values[m][n];}
    // Modification d'une valeur de la matrice
    void set_val(int m, int n, float a){m_values[m][n] = a;}

    
    // Operations sur les matrices
    friend Matrix operator+(const Matrix& A, const Matrix& B);  // Somme
    friend Matrix operator*(const Matrix& A, const Matrix& B);  // Multiplication terme à terme
    Matrix dot(Matrix& B) const;        // Produit
    Matrix T() const;                   // Transposée
    
private:
    int m_n;
    int m_m;
    float** m_values;
};
