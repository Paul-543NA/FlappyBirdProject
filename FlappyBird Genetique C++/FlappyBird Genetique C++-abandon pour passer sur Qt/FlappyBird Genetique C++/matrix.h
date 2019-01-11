#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>


class Matrix{

private:
    int m_n = 3;
    int m_m = 2;
    float** m_values;

public:

    // Constructeur, matrices remplises par defaut par des float entre 0 et 1
    Matrix(int m, int n);
    Matrix(const Matrix &M);
    Matrix();

    // Destrusteur
    ~Matrix();

    // Taille de la matrice
    int* shape() const;

    // Affichage
    void print() const;

    // Remlpis une matrice avec des float aléatoirs entre 0 et 1
    void randomInit();
    // Acces a une valeur de la matrice
    float val(int m, int n) const{return m_values[m][n];}
    // Modification d'une valeur de la matrice
    void set_val(int m, int n, float a){m_values[m][n] = a;}


    // Operations sur les matrices
    friend Matrix operator+(const Matrix& A, const Matrix& B);  // Somme
    friend Matrix operator*(const Matrix& A, const Matrix& B);  // Multiplication terme à terme
    Matrix dot(const Matrix& B) const;        // Produit
    Matrix T() const;                         // Transposée
    void operator=(const Matrix& A);
};

#endif /* Matrix_hpp */
