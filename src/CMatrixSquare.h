//
// Created by arach on 29.12.2020.
//

#ifndef MINI_PROJECT_CMATRIX_SQUARE_H
#define MINI_PROJECT_CMATRIX_SQUARE_H

#include <cmath>

template<class T>
class CMatrixSquare : public CMatrix<T> {
public:
    CMatrixSquare<T>(std::string name, int size): CMatrix<T>(name, size, size) {
    }

    CMatrixSquare<T>(int size) : CMatrix<T>(size, size) {
    }

    int getSize() const {
        return CMatrix<T>::getWidth();
    }

    static CMatrixSquare<T> generateSubArray(CMatrixSquare<T> originalArray, int size, int j1) {
        CMatrixSquare<T> m(size - 1);

        for (int i = 1; i < size; i++) {
            int j2 = 0;
            for (int j = 0; j < size; j++) {
                if (j == j1)
                    continue;
                m.setValue(i - 1, j2, originalArray.getValue(i, j));
                j2++;
            }
        }
        return m;
    }

    static double getDeterminant(CMatrixSquare<T> matrix, int size) {
        double res = 0;

        if (size == 1)
            return matrix.getValue(0, 0);
        else {
            res = 0;
            for (int j1 = 0; j1 < size; j1++) {
                CMatrixSquare<T> temporaryArray = generateSubArray(matrix, size, j1);
                double sign = pow(-1.0, 1.0 + j1 + 1.0);
                res += sign * matrix.getValue(0, j1) * getDeterminant(temporaryArray, size - 1);
            }
        }
        return res;
    }

    double getDeterminant() const {
        return getDeterminant(*this, getSize());
    }

    CMatrixSquare<T> getCofactors(int p, int q) {
        CMatrixSquare<T> cofactorsMatrix("cofactors", getSize());

        int i = 0, j = 0;

        // Looping for each element of the matrix
        for (int row = 0; row < getSize(); row++) {
            for (int col = 0; col < getSize(); col++) {
                //  Copying into temporary matrix only those element
                //  which are not in given row and column
                if (row != p && col != q) {
                    cofactorsMatrix.setValue(j++, i, this->getValue(row, col));;

                    // Row is filled, so increase row index and
                    // reset col index
                    if (j == getSize() - 1) {
                        j = 0;
                        i++;
                    }
                }
            }
        }
    }

    CMatrixSquare<T> adjoint() {
        CMatrixSquare<T> adjointMatrix("adjoint", getSize());

        if (getSize() == 1) {
            adjointMatrix.setValue(0, 0, 1);
            return adjointMatrix;
        }

        for (int i = 0; i < getSize(); i++) {
            for (int j = 0; j < getSize(); j++) {
                // Get cofactor of A[i][j]
                CMatrixSquare<T> temp = getCofactors(i, j); //@todo copy constructor

                // sign of adj[j][i] positive if sum of row
                // and column indexes is even.
                int sign = ((i + j) % 2 == 0) ? 1 : -1;

                // Interchanging rows and columns to get the
                // transpose of the cofactor matrix
                adjointMatrix.setValue(i, j, (sign) * (getDeterminant(temp, getSize() - 1)));
            }
        }

        return adjointMatrix;
    }

    CMatrix<T> inverse() {
        double det = getDeterminant();

        if (det == 0) {
            throw std::invalid_argument("matrix is non-invertible");
        }

        double factor = 1/getDeterminant();
        CMatrixSquare<T> adjointMatrix = adjoint(); // @todo copy constructor
        CMatrix<T> inverseMatrix = adjointMatrix * factor; // @todo copy constructor

        return inverseMatrix;
    }
};

#endif //MINI_PROJECT_CMATRIX_SQUARE_H
