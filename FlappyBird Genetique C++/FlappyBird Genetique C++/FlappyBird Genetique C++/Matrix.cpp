//
//  Matrix.cpp
//  FlappyBird Genetique C++
//
//  Created by Paul on 31/12/2018.
//  Copyright © 2018 Paul. All rights reserved.
//

#include "Matrix.hpp"
#include <iostream>

Matrix::Matrix(int m, int n){ // avec deux entiers
    m_m = m;
    m_n = n;
    m_values = new float*[m];
    for (int itr=0; itr < m; itr ++) {
        m_values[itr] = new float[n];
    }
}

Matrix::~Matrix(){
    for (int itr=0; itr<this->m_m; itr++) {
        delete m_values[itr];
    }
    delete m_values;
}

int* Matrix::shape() const{
    int* shape = new int[2];
    shape[0] = m_m;
    shape[1] = m_n;
    return shape;
}

Matrix operator+(const Matrix& A, const Matrix& B){
    int* c_shape = A.shape();
    Matrix C = Matrix(c_shape[0], c_shape[1]);
    for (int itr=0; itr<c_shape[0]; itr++) {
        for (int jtr=0; jtr<c_shape[1]; jtr++) {
            C.m_values[itr][jtr] = A.val(itr, jtr) + B.val(itr, jtr);
        }
    }
    return C;
}

Matrix operator*(const Matrix& A, const Matrix& B){
    int* c_shape = A.shape();
    Matrix C = Matrix(c_shape[0], c_shape[1]);
    for (int itr=0; itr<c_shape[0]; itr++) {
        for (int jtr=0; jtr<c_shape[1]; jtr++) {
            C.m_values[itr][jtr] = A.val(itr, jtr) * B.val(itr, jtr);
        }
    }
    return C;
}

Matrix Matrix::T() const{
    int* c_shape = this->shape();
    Matrix C = Matrix(c_shape[1], c_shape[0]);
    for (int itr=0; itr<c_shape[0]; itr++) {
        for (int jtr=0; jtr<c_shape[0]; jtr++) {
            C.m_values[jtr][itr] = this->val(itr,jtr);
        }
    }
    return C;
}

void Matrix::print() const{
    std::cout << "[";
    int* shape = this->shape();
    for (int itr=0; itr<shape[0]; itr++) {
        for (int jtr=0; jtr<shape[1]; jtr++) {
            std::cout << this->val(itr, jtr) << ", ";
        } std::cout << "||" << std::endl;
    }std::cout << "]" << std::endl;
}

