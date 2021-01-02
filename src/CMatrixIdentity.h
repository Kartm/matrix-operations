//
// Created by arach on 29.12.2020.
//

#ifndef MINI_PROJECT_CMATRIX_IDENTITY_H
#define MINI_PROJECT_CMATRIX_IDENTITY_H

#include "CMatrixSquare.h"

template<class T>
class CMatrixIdentity: public CMatrixSquare<T> {
public:
    CMatrixIdentity<T>(int size): CMatrixSquare<T>(size) {
        for(int x = 0; x < size; x++) {
            for(int y = 0; y < size; y++) {
                T value = 0;
                if(x == y) {
                    value = 1.0;
                }

                CMatrix<T>::setValue(x, y, value);
            }
        }
    }
};

#endif //MINI_PROJECT_CMATRIX_IDENTITY_H
