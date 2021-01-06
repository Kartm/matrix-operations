//
// Created by arach on 06.01.2021.
//

#ifndef MINI_PROJECT_CVECTOR_H
#define MINI_PROJECT_CVECTOR_H


template<class T>
class CVector {
public:
    CVector<T>(int size) {
        this->size = size;
        array = new T[size];
    }

    CVector<T>(int size, T* array) {
        this->size = size;
        this->array = array;
    }

    // copy constructor
    CVector<T> (const CVector<T> &other) {
        v_copy(other);
    }

    // copy assignment
    CVector<T> operator=(const CVector<T> &other)
    {
        freeArrayMemory();
        v_copy(other);
        return(*this);
    }

    void v_copy(const CVector<T> &other)
    {
        size = other.size;

        array = new T[size];
        for (int i = 0; i < size; i++) {
            array[i] = other.getValue(i);
        }
    }

    ~CVector<T>() {
        freeArrayMemory();
        size = 0;
    }

    void freeArrayMemory() {
        if (array != NULL) {
            delete[] array;
        }
    }

    void setValue(int index, T value) {
        if (index >= size || index < 0) {
            throw std::invalid_argument("setting out of bounds: index = " + std::to_string(index));
        }

        array[index] = value;
    }

    T getValue(int index) const {
        if (index >= size || index < 0) {
            throw std::invalid_argument("getting out of bounds: index = " + std::to_string(index));
        }

        return array[index];
    }

    int getSize() {
        return size;
    }

    T dotProduct(CVector<T> &other) {
        if (size != other.getSize()) {
            throw std::invalid_argument("dot product - vectors must have an equal size! " + std::to_string(size) + " != " + std::to_string(other.getSize()));
        }

        T sum = 0;
        for(int i = 0; i < size; i++) {
            sum += getValue(i) * other.getValue(i);
        }
        return sum;
    }

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << getValue(i) << " ";
        }
        std::cout << std::endl;
    }

private:
    T* array;
    int size;
};


#endif //MINI_PROJECT_CVECTOR_H
