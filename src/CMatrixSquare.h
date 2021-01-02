//
// Created by arach on 29.12.2020.
//

#ifndef MINI_PROJECT_CMATRIX_SQUARE_H
#define MINI_PROJECT_CMATRIX_SQUARE_H

#include <cmath>

template<class T>
class CMatrixSquare : public CMatrix<T> {
public:
    CMatrixSquare<T>(int size) : CMatrix<T>(size, size) {
    }

    int getSize() {
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

    static double determinant(CMatrixSquare<T> originalArray, int size) {
        double res = 0;

        if (size == 1)
            return originalArray.getValue(0, 0);
        else {
            res = 0;
            for (int j1 = 0; j1 < size; j1++) {
                CMatrixSquare<T> temporaryArray = generateSubArray(originalArray, size, j1);
                double sign = pow(-1.0, 1.0 + j1 + 1.0);
                res += sign * originalArray.getValue(0, j1) * determinant(temporaryArray, size - 1);
            }
        }
        return res;
    }

    static double determinant(CMatrixSquare<T> array) {
        return determinant(array, array.getSize());
    }
};

#endif //MINI_PROJECT_CMATRIX_SQUARE_H
