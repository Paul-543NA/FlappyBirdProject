#include "perceptron.h"

Matrix sigmoid(Matrix M){
    int* res_shape = M.shape();
    Matrix res = Matrix(res_shape[0], res_shape[1]);
    for (int itr=0; itr<res_shape[0]; itr++) {
        for (int jtr=0; jtr<res_shape[1]; jtr++) {
            res.set_val(itr, jtr, 1.0F/(1+exp(-M.val(itr, jtr))));
        }
    }
    return res;
}

Perceptron::Perceptron(int depth, int profile[]){
    m_depth = depth;
    m_profile = profile;
    m_biaises = new Matrix*[depth];
    m_weights = new Matrix*[depth];
    std::cout << "Valide" << std::endl;
    for (int itr=0; itr<depth-1; itr++) {
        std::cout << itr << ";" << profile[itr] << "--" << profile[itr+1] << std::endl;
        m_biaises[itr] = new Matrix(profile[itr+1], 1);
        m_weights[itr] = new Matrix(profile[itr], profile[itr+1]);
    }
    std::cout << "##### Matrices review #####" << std::endl;
    m_biaises[0]->print();
    m_biaises[1]->print();
    m_weights[0]->print();
    m_weights[1]->print();
}

Perceptron::~Perceptron(){
    //delete m_weights;
    //delete m_biaises;
    //delete m_profile;
}

Matrix Perceptron::feedForward(Matrix X) const{
    Matrix res;
    for (int itr=0; itr<this->m_depth; itr++) {
        res = X.dot(*m_weights[itr]) + *m_biaises[itr];
    }
    return res;
}

// ----------------- COMPRENDRE ERREUR m_biaises[0] ----------------- //

void Perceptron::print() const{
    std::cout << "-- Perceptron object --" << std::endl;
    std::cout << "Depth: " << this->m_depth << std::endl;
    Matrix* M = m_biaises[0];
    M->print();
    std::cout << "Profile: ";
    for (int itr=0; itr<this->m_depth; itr++) {
        std::cout << this->m_profile[itr] << " ";
    }
    std::cout << std::endl;
    std::cout << "Weights shapes: ";
    for (int itr=0; itr<this->m_depth-1; itr++) {
        Matrix* M = this->m_weights[itr];
        int* shape = M->shape();
        std::cout << "(" << shape[0] << ", " << shape[1] << ")";
    }
    std::cout << std::endl;
    std::cout << "Biaises shapes: ";
    for (int itr=0; itr<this->m_depth-1; itr++) {
        std::cout << "(" << this->m_biaises[itr]->shape()[0] << ", " << this->m_biaises[itr]->shape()[1] << ")";
    }
    std::cout << std::endl;
}

