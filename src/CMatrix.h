//
// Created by arach on 29.12.2020.
//

#ifndef MINI_PROJECT_CMATRIX_H
#define MINI_PROJECT_CMATRIX_H

template<class T>
class CMatrix {
public:
    CMatrix<T>(int width, int height) {
        std::string exceptionMsg = "invalid size: ";
        if (width < 0) {
            exceptionMsg += "width = ";
            exceptionMsg += std::to_string(width);
            throw std::invalid_argument(exceptionMsg);
        } else if (height < 0) {
            exceptionMsg += "height = ";
            exceptionMsg += std::to_string(height);
            throw std::invalid_argument(exceptionMsg);
        }

        this->width = width;
        this->height = height;

        T **array = new T *[height];
        for (int y = 0; y < height; y++) {
            array[y] = new T[width];
        }

        this->array = array;
    }

    // copy constructor
    CMatrix<T>(const CMatrix<T> &N) {
        width = N.width;
        height = N.height;

        if (N.array) {
            array = new T *[height];

            for (int y = 0; y < height; y++)
                array[y] = new int[width];

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    array[y][x] = N.array[y][x];
                }
            }
        }
    }

    ~CMatrix<T>() {
        this->width = width;
        this->height = height;

        if (height > 0 && width > 0) {
            for (int i = 0; i < height; i++) {
                delete[] array[i];
            }
            delete[] array;

        }


    }

    void setValue(int x, int y, T value) {
        std::string exceptionMsg = "setting out of bounds: ";
        if (x >= width || x < 0) {
            exceptionMsg += "x = ";
            exceptionMsg += std::to_string(x);
            throw std::invalid_argument(exceptionMsg);
        } else if (y >= height || y < 0) {
            exceptionMsg += "y = ";
            exceptionMsg += std::to_string(y);
            throw std::invalid_argument(exceptionMsg);
        }

        array[y][x] = value;
    }

    T getValue(int x, int y) const {
        std::string exceptionMsg = "getting out of bounds: ";
        if (x >= width || x < 0) {
            exceptionMsg += "x = ";
            exceptionMsg += std::to_string(x);
            throw std::invalid_argument(exceptionMsg);
        } else if (y >= height || y < 0) {
            exceptionMsg += "y = ";
            exceptionMsg += std::to_string(y);
            throw std::invalid_argument(exceptionMsg);
        }

        return array[y][x];
    }

    CMatrix<T> transposition() {
        CMatrix<T> newMatrix(getHeight(), getWidth());

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                newMatrix.setValue(y, x, getValue(x, y));
            }
        }

        return newMatrix;
    }

    CMatrix<T> operator+(const CMatrix<T> &other) {
        if (width != other.width || height != other.height) {
            throw std::invalid_argument("matrices differ in size");
        }

        CMatrix<T> newMatrix(width, height);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                T newValue = this->getValue(x, y) + other.getValue(x, y);
                newMatrix.setValue(x, y, newValue);
            }
        }

        return newMatrix;
    }

    CMatrix<T> operator-(const CMatrix<T> &other) {
        if (width != other.width || height != other.height) {
            throw std::invalid_argument("matrices differ in size");
        }

        CMatrix<T> newMatrix(width, height);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                T newValue = this->getValue(x, y) - other.getValue(x, y);
                newMatrix.setValue(x, y, newValue);
            }
        }

        return newMatrix;
    }

    CMatrix<T> operator*(const int &scalar) {
        CMatrix<T> newMatrix(width, height);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                T newValue = this->getValue(x, y) * scalar;
                newMatrix.setValue(x, y, newValue);
            }
        }

        return newMatrix;
    }

    CMatrix<T> operator*(const CMatrix<T> &other) {
        if (width != other.height) {
            throw std::invalid_argument(
                    "number of columns in the first matrix is not equal to the number of rows in the second matrix");
        }

        CMatrix<T> newMatrix(height, other.width);

        for (int y1 = 0; y1 < height; y1++) {
            for (int x2 = 0; x2 < other.width; x2++) {
                T sum = 0;
                for (int offset = 0; offset < width; offset++) {
                    sum += getValue(offset, y1) * other.getValue(x2, offset);
                }
                std::cout << std::endl;
                newMatrix.setValue(x2, y1, sum);
            }
        }

        return newMatrix;
    }

    int getWidth() {
        return width;
    }

    int getHeight() {
        return height;
    }

    void print() {
        std::cout << this->width << " by " << this->height << std::endl;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                std::cout << getValue(x, y) << " ";

            }
            std::cout << std::endl;

        }
    }

private:
    int width;
    int height;
    T **array;
};

#endif //MINI_PROJECT_CMATRIX_H
