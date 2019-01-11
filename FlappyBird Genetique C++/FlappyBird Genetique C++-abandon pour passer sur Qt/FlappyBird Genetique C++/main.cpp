#include "tests.h"
#include "matrix.h"

Matrix puissance(Matrix A, int n){
    Matrix res = A;
    A.print();
    res.print();
    for (int itr = 0; itr<n; itr++) {
        std::cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&" << std::endl;
        res = A.dot(res);
        A.dot(res).print();
        /*for (int j=0; j<res.shape()[0]; j++) {
            for (int k=0; k<res.shape()[1]; k++) {
                res.set_val(j, k, m.val(j, k));
            }
        }*/
        res.print();
    }
    return res;
}

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();*/

    //testMatrix();
    //testBird();
    testPerceptron();
    
    Matrix A = Matrix(2, 2);
    A.set_val(0, 0, 2);
    A.set_val(1, 1, 2);
    A.set_val(0, 1, 0);
    A.set_val(1, 0, 0);
    //Matrix B = puissance(A, 5);
    
    return 0;
}
