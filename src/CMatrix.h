//
// Created by arach on 29.12.2020.
//

#ifndef MINI_PROJECT_CMATRIX_H
#define MINI_PROJECT_CMATRIX_H

#include <fstream>

template<class T>
class CMatrix {
public:
    CMatrix<T>(int width, int height) {
        checkSize(width, height);

        this->width = width;
        this->height = height;

        T **array = new T *[height];
        for (int y = 0; y < height; y++) {
            array[y] = new T[width];
        }

        this->array = array;
    }

    // read from file
    CMatrix<T>(int width, int height, std::string path): CMatrix<T>(width, height) {
        std::fstream file(path, std::ios_base::in);
        if(!file.is_open()) {
            throw std::invalid_argument("file not found");
        }

        checkSize(width, height);

        int x = 0;
        int y = 0;

        T a;
        while(file >> a) {
            if(x == width) {
                x = 0;
                y++;
            }
            if(y == height) {
                throw std::invalid_argument("matrix cell out of bounds");
            }

            setValue(x, y, a);

            x++;
        }

        file.close();
    }

    CMatrix<T>(std::string name, int width, int height): CMatrix<T>(width, height) {
        this->name = name;
    }

    void checkSize(int width, int height) {
        std::string exceptionMsg = "";
        bool error = false;
        if (width <= 0) {
            exceptionMsg += "width = ";
            exceptionMsg += std::to_string(width);
            error = true;
        }
        if (height <= 0) {
            exceptionMsg += " height = ";
            exceptionMsg += std::to_string(height);
            error = true;
        }
        if(error) {
            throw std::invalid_argument("invalid size: " + exceptionMsg + name);
        }
    }

    // copy constructor
    CMatrix<T> (const CMatrix<T> &other) {
        v_copy(other);
    }

    // copy assignment
    CMatrix<T> operator=(const CMatrix<T> &other)
    {
        other.width;
        freeArrayMemory();
        v_copy(other);
        return(*this);
    }

    void v_copy(const CMatrix<T> &other)
    {
        width = other.width;
        height = other.height;
        name = other.name;

        array = new T *[height];
        for (int y = 0; y < height; y++) {
            array[y] = new T[width];

            for(int x = 0; x < width; x++) {
                array[y][x] = other.getValue(x, y);
            }
        }
    }

    ~CMatrix<T>() {
        checkSize(width, height);

        freeArrayMemory();
        width = 0;
        height = 0;
    }

    void freeArrayMemory() {
        if (array != NULL) {
            for (int i = 0; i < height; i++) {
                if(array[i] != NULL) {
                    delete[] array[i];
                }
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

    void setWidth(int width) {
        this->width = width;
    }

    void setHeight(int height) {
        this->height = height;
    }

    void setArray(T ** newArray) {
        this->array = newArray;
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

    CMatrix<T> operator*(const T scalar) {
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

    int getWidth() const {
        return width;
    }

    int getHeight() const {
        return height;
    }

    T** getArray() const {
        return array;
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
    std::string name = "";
    T **array;
};

#endif //MINI_PROJECT_CMATRIX_H
