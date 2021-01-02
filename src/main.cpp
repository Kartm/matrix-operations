#include <iostream>
#include "CMatrix.h"
#include "CMatrixIdentity.h"

using namespace std;

int main() {
    CMatrix<int> intMatrix(4, 4);

    for(int x = 0; x < 4; x++) {
        for(int y = 0; y < 4; y++) {
            intMatrix.setValue(x, y, x + y * 10);
        }
    }

    intMatrix.setValue(3, 3, 69);

    intMatrix.print();

    return 0;
}
