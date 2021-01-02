//
// Created by arach on 29.12.2020.
//

#ifndef MINI_PROJECT_CMATRIX_H
#define MINI_PROJECT_CMATRIX_H

template <class T>
class CMatrix {
public:
    CMatrix<T>(int width, int height) {
        this -> width = width;
        this -> height = height;

        T** array = new T*[width];
        for(int x = 0; x < width; x++) {
            array[x] = new T[height];
        }

        this->array = array;
    }

    ~CMatrix<T>() {
        this -> width = width;
        this -> height = height;

        for(int i = 0; i < width; i++) {
            delete [] array[i];
        }
        delete[] array;
    }

    void setValue(int x, int y, T value) {
        if(x >= width || y >= height || x < 0 || y < 0) {
            throw std::invalid_argument("x or y out of bounds");
        }

        array[x][y] = value;
    }

    // todo return nullptr
    T getValue(int x, int y) const {
        if(x >= width || y >= height || x < 0 || y < 0) {
            throw std::invalid_argument("x or y out of bounds");
        }

        return array[x][y];
    }

    CMatrix<T> transposition() {
        CMatrix<T> newMatrix(height, width);

        for(int j = 0; j < height; j++) {
            for(int i = 0; i < width; i++) {
                newMatrix.setValue(j, i, array[i][j]);
            }
        }

        return newMatrix;
    }

    CMatrix<T> operator+(const CMatrix<T>& other) {
        if(width != other.width || height != other.height) {
            throw std::invalid_argument("matrices differ in size");
        }

        CMatrix<T> newMatrix(width, height);

        for(int j = 0; j < height; j++) {
            for(int i = 0; i < width; i++) {
                T newValue = this->getValue(i, j) + other.getValue(i, j);
                newMatrix.setValue(i, j, newValue);
            }
        }

        return newMatrix;
    }

    void print() {
        std::cout << this->width << " by " << this->height << std::endl;
        for(int j = 0; j < height; j++) {
            for(int i = 0; i < width; i++) {
                std::cout << array[i][j] << " ";

            }
            std::cout << std::endl;

        }


    }

private:
    int width;
    int height;
    T** array;
};

#endif //MINI_PROJECT_CMATRIX_H
