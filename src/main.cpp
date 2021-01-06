#include <iostream>
#include "CMatrix.h"
#include "CMatrixSquare.h"
#include "CMatrixIdentity.h"

using namespace std;

int main() {
    CMatrix<int> matrixA(3, 4);

    for(int x = 0; x < 3; x++) {
        for(int y = 0; y < 4; y++) {
            matrixA.setValue(x, y, x + 3 * y + 1);
        }
    }

    cout << "4x3 matrix A:" << endl;
    matrixA.print();

    cout << "transposition of A:" << endl;
    (matrixA.transposition()).print();

    CMatrixSquare<double> matrixB(4);

    for(int x = 0; x < 4; x++) {
        for(int y = 0; y < 4; y++) {
            matrixB.setValue(x, y, x + 4 * y + 1);
        }
    }

    // modify it a bit to get a non-zero determinant
    matrixB.setValue(1, 2, 25.2);
    matrixB.setValue(2, 2, -5.5);
    matrixB.setValue(1, 1, -10.4);

    cout << "4x4 matrix B:" << endl;
    matrixB.print();

    cout << "determinant of matrix B:" << endl;
    cout << matrixB.getDeterminant() << endl << endl;

    cout << "inverse of matrix B:" << endl;
    matrixB.inverse().print();

    CMatrixIdentity<double> matrixI(4);
    cout << "4x4 identity matrix I:" << endl;
    matrixI.print();

    cout << "B x I:" << endl;
    (matrixB * matrixI).print();

    cout << "B + I:" << endl;
    (matrixB + matrixI).print();

    cout << "B - I:" << endl;
    (matrixB - matrixI).print();

    cout << "5 * B:" << endl;
    ((CMatrix<double>)matrixB * 5.0).print();

    cout << "Matrix C loaded from file example-data-1.txt" << endl;
    CMatrix<int> matrixC(6, 3, "../example-data-1.txt");
    matrixC.print();

    cout << "Matrix D loaded from file example-data-2.txt" << endl;
    CMatrix<double> matrixD(6, 3, "../example-data-2.txt");
    matrixD.print();

    cout << "row 1, column 2 in matrix D: " << endl;
    cout << matrixD.getValue(1, 0) << endl << endl;

    CVector<double> vectorT = matrixD.getVector(0, true);
    cout << "vector t created from the first row of matrix D: " << endl;
    vectorT.print();

    CVector<double> vectorV = matrixD.getVector(2, true);
    cout << "vector v created from the last row of matrix D: " << endl;
    vectorV.print();

    cout << "scalar product of vectors t and v: " << endl;
    cout << vectorT.dotProduct(vectorV) << endl << endl;

    return 0;
}
