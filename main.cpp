#include <iostream>
#include "CMatrix.h"

using namespace std;

int main() {
    CMatrix<int> intMatrix(9, 4);

    for(int x = 0; x < 9; x++) {
        for(int y = 0; y < 4; y++) {
            intMatrix.setValue(x, y, x + y * 10);
        }
    }

    intMatrix.print();
//    intMatrix.transposition().print();

    (intMatrix + intMatrix).print();

    return 0;
}
