#include "matrix.h"
#include <iostream>

float floatRand() {
    return float(rand()) / (float(RAND_MAX) + 1.0);
}

Matrix::Matrix(int m, int n){ // avec deux entiers
    m_m = m;
    m_n = n;
    m_values = new float*[m];
    for (int itr=0; itr < m; itr ++) {
        m_values[itr] = new float[n];
    }
    srand(static_cast<unsigned int>(clock()));
    int* shape = this->shape();
    for (int itr=0; itr<shape[0]; itr++) {
        for (int jtr=0; jtr<shape[1]; jtr++) {
            m_values[itr][jtr] = floatRand();
        }
    }
}

Matrix::Matrix(const Matrix &M){ // avec deux entiers
    m_m = M.m_m;
    m_n = M.m_n;
    m_values = new float*[m_m];
    for (int itr=0; itr < m_m; itr ++) {
        m_values[itr] = new float[m_n];
    }
    int* shape = this->shape();
    for (int itr=0; itr<shape[0]; itr++) {
        for (int jtr=0; jtr<shape[1]; jtr++) {
            m_values[itr][jtr] = M.m_values[itr][jtr];
        }
    }
}

Matrix::Matrix(){ // avec deux entiers
    int m = 2;
    int n = 2;
    m_m = m;
    m_n = n;
    m_values = new float*[m];
    for (int itr=0; itr < m; itr ++) {
        m_values[itr] = new float[n];
    }
    srand(static_cast<unsigned int>(clock()));
    int* shape = this->shape();
    for (int itr=0; itr<shape[0]; itr++) {
        for (int jtr=0; jtr<shape[1]; jtr++) {
            m_values[itr][jtr] = floatRand();
        }
    }
}

Matrix::~Matrix(){
    for (int itr=0; itr<this->m_m; itr++) {
        delete m_values[itr];
    }
    delete m_values;
}

int* Matrix::shape() const{
    auto shape = new int[2];
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

Matrix Matrix::dot(const Matrix& B) const{
    int* A_shape = this->shape();
    int* B_shape = B.shape();
    Matrix C = Matrix(A_shape[0], B_shape[1]);
    int sum = 0;
    if (A_shape[1] == B_shape[0]) {
        for (int itr=0; itr<A_shape[0]; itr++) {
            for (int jtr=0; jtr<B_shape[1]; jtr++) {
                for (int ktr = 0; ktr<A_shape[1]; ktr++) {
                    sum += this->val(itr, ktr)*B.val(ktr, jtr);
                }
                C.m_values[itr][jtr] = sum;
                sum = 0;
            }
        }
    }
    return C;
}

Matrix Matrix::T() const{
    int* c_shape = this->shape();
    Matrix C = Matrix(c_shape[1], c_shape[0]);
    for (int itr=0; itr<c_shape[0]; itr++) {
        for (int jtr=0; jtr<c_shape[1]; jtr++) {
            C.m_values[jtr][itr] = this->val(itr,jtr);
        }
    }
    return C;
}

void Matrix::print() const{
    std::cout << "--- Matrix objsct ---" << std::endl
    ;
    std::cout << "Shape: (" << this->shape()[0] << ", " << this->shape()[1] << ")" << std::endl
    ;
    std::cout << "[";
    int* shape = this->shape();
    for (int itr=0; itr<shape[0]; itr++) {
        for (int jtr=0; jtr<shape[1]; jtr++) {
            std::cout << this->val(itr, jtr) << ", ";
        } std::cout << "||" << std::endl;
    }std::cout << "]" << std::endl;
}

void Matrix::operator=(const Matrix& A){
    for (int itr=0; itr<this->m_m; itr++) {
        delete m_values[itr];
    }
    delete m_values;

    this->m_m = A.shape()[0];
    this->m_n = A.shape()[1];

    m_values = new float*[this->m_m];
    for (int itr=0; itr < this->m_m; itr ++) {
        m_values[itr] = new float[this->m_n];
    }

    for (int itr=0; itr<this->m_m; itr++) {
        for (int jtr=0; jtr<this->m_n; jtr++) {
            this->set_val(itr, jtr, A.val(itr, jtr));
        }
    }
}
