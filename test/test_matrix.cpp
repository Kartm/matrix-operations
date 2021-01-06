#include "gtest/gtest.h"

#include "CMatrix.h"
#include "CMatrixIdentity.h"
#include "CVector.h"

TEST(CMatrixTest, creates_with_size
) {
    CMatrix<int> intMatrix(9, 4);

    EXPECT_EQ(intMatrix
                      .

                              getWidth(),

              9);
    EXPECT_EQ(intMatrix
                      .

                              getHeight(),

              4);
}

TEST(CMatrixTest, setValueGetValue
) {
    CMatrix<int> intMatrix(3, 3);

    for (
            int x = 0;
            x < 3; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            intMatrix.
                    setValue(x, y, x
                                   + y * 10);
        }
    }

    intMatrix.setValue(2, 2, 120);

    for (
            int x = 0;
            x < 3; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            if (x == 2 && y == 2) {
                EXPECT_EQ(intMatrix
                                  .
                                          getValue(x, y
                                  ), 120);
            } else {
                EXPECT_EQ(intMatrix
                                  .
                                          getValue(x, y
                                  ), x + y * 10);
            }
        }
    }

}


TEST(CMatrixTest, adds
) {
    CMatrix<int> intMatrix(3, 3);

    for (
            int x = 0;
            x < 3; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            intMatrix.
                    setValue(x, y, x
                                   + y * 10);
        }
    }

    intMatrix.setValue(2, 2, 120);

    CMatrix<int> addedMatrix = intMatrix + intMatrix;

    for (
            int x = 0;
            x < 3; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            if (x == 2 && y == 2) {
                EXPECT_EQ(addedMatrix
                                  .
                                          getValue(x, y
                                  ), 2 * 120);
            } else {
                EXPECT_EQ(addedMatrix
                                  .
                                          getValue(x, y
                                  ), 2 * (x + y * 10));
            }
        }
    }

}

TEST(CMatrixTest, subtracts
) {
    CMatrix<int> intMatrix(3, 3);

    for (
            int x = 0;
            x < 3; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            intMatrix.
                    setValue(x, y, x
                                   + y * 10);
        }
    }

    CMatrix<int> intMatrixOther(3, 3);

    for (
            int x = 0;
            x < 3; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            int value = (x + y * 10) + 5;
            intMatrixOther.
                    setValue(x, y, value
            );
        }
    }

    CMatrix<int> resultMatrix = intMatrix - intMatrixOther;

    for (
            int x = 0;
            x < 3; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            int expectedValue = (x + y * 10) - ((x + y * 10) + 5);
            EXPECT_EQ(resultMatrix
                              .
                                      getValue(x, y
                              ), expectedValue);
        }
    }
}

TEST(CMatrixTest, transposition
) {
    CMatrix<int> intMatrix(4, 3);

    for (
            int x = 0;
            x < 4; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            intMatrix.
                    setValue(x, y, x
                                   + y * 10);
        }
    }

    CMatrix<int> intMatrixOther = intMatrix.transposition();

    EXPECT_EQ(intMatrixOther
                      .

                              getWidth(), intMatrix

                      .

                              getHeight()

    );
    EXPECT_EQ(intMatrixOther
                      .

                              getHeight(), intMatrix

                      .

                              getWidth()

    );

    for (
            int x = 0;
            x < 4; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            EXPECT_EQ(intMatrix
                              .
                                      getValue(x, y
                              ), intMatrixOther.
                    getValue(y, x
            ));
        }
    }
}

TEST(CMatrixTest, multiplies_by_scalar
) {
    CMatrix<int> intMatrix(3, 3);

    for (
            int x = 0;
            x < 3; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            intMatrix.
                    setValue(x, y, x
                                   + y * 10);
        }
    }

    CMatrix<int> intMatrixOther = intMatrix * 4;

    for (
            int x = 0;
            x < 3; x++) {
        for (
                int y = 0;
                y < 3; y++) {
            int expectedValue = 4 * (x + y * 10);
            EXPECT_EQ(intMatrixOther
                              .
                                      getValue(x, y
                              ), expectedValue);
        }
    }
}

TEST(CMatrixTest, multiplies_by_matrix
) {
    CMatrix<int> intMatrix(3, 2);
    intMatrix.setValue(0, 0, 1);
    intMatrix.setValue(1, 0, 2);
    intMatrix.setValue(2, 0, 3);
    intMatrix.setValue(0, 1, 4);
    intMatrix.setValue(1, 1, 5);
    intMatrix.setValue(2, 1, 6);

    CMatrix<int> intMatrixOther(2, 3);
    intMatrixOther.setValue(0, 0, 7);
    intMatrixOther.setValue(1, 0, 8);
    intMatrixOther.setValue(0, 1, 9);
    intMatrixOther.setValue(1, 1, 10);
    intMatrixOther.setValue(0, 2, 11);
    intMatrixOther.setValue(1, 2, 12);

    CMatrix<int> matrixMultipliedResult = intMatrix * intMatrixOther;

    EXPECT_EQ(matrixMultipliedResult
                      .getValue(0, 0), 58);
    EXPECT_EQ(matrixMultipliedResult
                      .getValue(1, 0), 64);
    EXPECT_EQ(matrixMultipliedResult
                      .getValue(0, 1), 139);
    EXPECT_EQ(matrixMultipliedResult
                      .getValue(1, 1), 154);
}

TEST(CMatrixTest, identity
) {
    CMatrixIdentity<int> identityMatrix(5);

    for (
            int x = 0;
            x < 5; x++) {
        for (
                int y = 0;
                y < 5; y++) {
            int expected = 0;
            if (x == y) {
                expected = 1;
            }

            EXPECT_EQ(identityMatrix
                              .
                                      getValue(x, y
                              ), expected);
        }
    }
}

TEST(CMatrixTest, determinant_zero
) {
    CMatrixSquare<int> intMatrix(3);
    intMatrix.setValue(0, 0, 1);
    intMatrix.setValue(1, 0, 2);
    intMatrix.setValue(2, 0, 3);
    intMatrix.setValue(0, 1, 4);
    intMatrix.setValue(1, 1, 5);
    intMatrix.setValue(2, 1, 6);
    intMatrix.setValue(0, 2, 7);
    intMatrix.setValue(1, 2, 8);
    intMatrix.setValue(2, 2, 9);

    EXPECT_EQ(intMatrix.getDeterminant(),
              0);
}

TEST(CMatrixTest, determinant_non_zero
) {
    CMatrixSquare<int> intMatrix(3);
    intMatrix.setValue(0, 0, 1);
    intMatrix.setValue(1, 0, 4);
    intMatrix.setValue(2, 0, 9);
    intMatrix.setValue(0, 1, 8);
    intMatrix.setValue(1, 1, 4);
    intMatrix.setValue(2, 1, 2);
    intMatrix.setValue(0, 2, 7);
    intMatrix.setValue(1, 2, 8);
    intMatrix.setValue(2, 2, 9);

    EXPECT_EQ(intMatrix.getDeterminant(),
              112);
}

TEST(CMatrixTest, read_from_file_int
) {
    CMatrix<int> intMatrix(6, 3, "../example-data-1.txt");

    EXPECT_EQ(intMatrix.getValue(0, 0), 1);
    EXPECT_EQ(intMatrix.getValue(1, 0), 2);
    EXPECT_EQ(intMatrix.getValue(2, 0), 3123);
    EXPECT_EQ(intMatrix.getValue(3, 0), 4);
    EXPECT_EQ(intMatrix.getValue(4, 0), 5);
    EXPECT_EQ(intMatrix.getValue(5, 0), 6);
    EXPECT_EQ(intMatrix.getValue(0, 1), 9);
    EXPECT_EQ(intMatrix.getValue(1, 1), 11231);
    EXPECT_EQ(intMatrix.getValue(2, 1), 2);
    EXPECT_EQ(intMatrix.getValue(3, 1), 3);
    EXPECT_EQ(intMatrix.getValue(4, 1), 4123);
    EXPECT_EQ(intMatrix.getValue(5, 1), 6);
    EXPECT_EQ(intMatrix.getValue(0, 2), 5);
    EXPECT_EQ(intMatrix.getValue(1, 2), 6);
    EXPECT_EQ(intMatrix.getValue(2, 2), 723);
    EXPECT_EQ(intMatrix.getValue(3, 2), 8);
    EXPECT_EQ(intMatrix.getValue(4, 2), 9);
    EXPECT_EQ(intMatrix.getValue(5, 2), 9900);
}

TEST(CMatrixTest, read_from_file_double
) {
    CMatrix<double> doubleMatrix(6, 3, "../example-data-2.txt");

    EXPECT_EQ(doubleMatrix.getValue(0, 0), 1.0);
    EXPECT_EQ(doubleMatrix.getValue(1, 0), 2.123);
    EXPECT_EQ(doubleMatrix.getValue(2, 0), 3123.34);
    EXPECT_EQ(doubleMatrix.getValue(3, 0), 4.34);
    EXPECT_EQ(doubleMatrix.getValue(4, 0), 5.1);
    EXPECT_EQ(doubleMatrix.getValue(5, 0), 6.0);
    EXPECT_EQ(doubleMatrix.getValue(0, 1), 9);
    EXPECT_EQ(doubleMatrix.getValue(1, 1), 11231.2323);
    EXPECT_EQ(doubleMatrix.getValue(2, 1), 2);
    EXPECT_EQ(doubleMatrix.getValue(3, 1), 3);
    EXPECT_EQ(doubleMatrix.getValue(4, 1), 4123);
    EXPECT_EQ(doubleMatrix.getValue(5, 1), 6.123);
    EXPECT_EQ(doubleMatrix.getValue(0, 2), 5);
    EXPECT_EQ(doubleMatrix.getValue(1, 2), 6);
    EXPECT_EQ(doubleMatrix.getValue(2, 2), 723);
    EXPECT_EQ(doubleMatrix.getValue(3, 2), 8);
    EXPECT_EQ(doubleMatrix.getValue(4, 2), 9);
    EXPECT_EQ(doubleMatrix.getValue(5, 2), 9900.3434);
}

TEST(CMatrixTest, read_from_file_determinant
) {
    CMatrixSquare<double> matrix(7, "../data-large.txt");
    EXPECT_DOUBLE_EQ(246886212.11800003, matrix.getDeterminant());
}

TEST(CMatrixTest, inverts
) {
    CMatrixSquare<double> matrix(3);
    matrix.setValue(0, 0, 1);
    matrix.setValue(1, 0, 3);
    matrix.setValue(2, 0, 2);
    matrix.setValue(0, 1, 0);
    matrix.setValue(1, 1, -1);
    matrix.setValue(2, 1, 2);
    matrix.setValue(0, 2, 0);
    matrix.setValue(1, 2, 0);
    matrix.setValue(2, 2, 1);

    CMatrix<double> inverted = matrix.inverse();

    EXPECT_EQ(inverted
                      .getValue(0, 0), 1);
    EXPECT_EQ(inverted
                      .getValue(1, 0), 3);
    EXPECT_EQ(inverted
                      .getValue(2, 0), -8);
    EXPECT_EQ(inverted
                      .getValue(0, 1), 0);
    EXPECT_EQ(inverted
                      .getValue(1, 1), -1);
    EXPECT_EQ(inverted
                      .getValue(2, 1), 2);
    EXPECT_EQ(inverted
                      .getValue(0, 2), 0);
    EXPECT_EQ(inverted
                      .getValue(1, 2), 0);
    EXPECT_EQ(inverted
                      .getValue(2, 2), 1);
}

TEST(CVectorTest, vector_from_square_matrix
) {
    CMatrixSquare<double> matrix(3);
    matrix.setValue(0, 0, 1);
    matrix.setValue(1, 0, 3);
    matrix.setValue(2, 0, 2);
    matrix.setValue(0, 1, 0);
    matrix.setValue(1, 1, -1);
    matrix.setValue(2, 1, 2);
    matrix.setValue(0, 2, 0);
    matrix.setValue(1, 2, 0);
    matrix.setValue(2, 2, 1);

    CVector<double> horizontal1 = matrix.getVector(0, true);
    EXPECT_EQ(1, horizontal1.getValue(0));
    EXPECT_EQ(3, horizontal1.getValue(1));
    EXPECT_EQ(2, horizontal1.getValue(2));
    CVector<double> horizontal2 = matrix.getVector(1, true);
    EXPECT_EQ(0, horizontal2.getValue(0));
    EXPECT_EQ(-1, horizontal2.getValue(1));
    EXPECT_EQ(2, horizontal2.getValue(2));
    CVector<double> horizontal3 = matrix.getVector(2, true);
    EXPECT_EQ(0, horizontal3.getValue(0));
    EXPECT_EQ(0, horizontal3.getValue(1));
    EXPECT_EQ(1, horizontal3.getValue(2));

    CVector<double> vertical1 = matrix.getVector(0, false);
    EXPECT_EQ(1, vertical1.getValue(0));
    EXPECT_EQ(0, vertical1.getValue(1));
    EXPECT_EQ(0, vertical1.getValue(2));
    CVector<double> vertical2 = matrix.getVector(1, false);
    EXPECT_EQ(3, vertical2.getValue(0));
    EXPECT_EQ(-1, vertical2.getValue(1));
    EXPECT_EQ(0, vertical2.getValue(2));
    CVector<double> vertical3 = matrix.getVector(2, false);
    EXPECT_EQ(2, vertical3.getValue(0));
    EXPECT_EQ(2, vertical3.getValue(1));
    EXPECT_EQ(1, vertical3.getValue(2));
}

TEST(CVectorTest, vector_from_matrix
) {
    CMatrix<int> matrix(3, 2);
    matrix.setValue(0, 0, 1);
    matrix.setValue(1, 0, 2);
    matrix.setValue(2, 0, 3);
    matrix.setValue(0, 1, 4);
    matrix.setValue(1, 1, 5);
    matrix.setValue(2, 1, 6);

    CVector<int> horizontal1 = matrix.getVector(0, true);
    EXPECT_EQ(1, horizontal1.getValue(0));
    EXPECT_EQ(2, horizontal1.getValue(1));
    EXPECT_EQ(3, horizontal1.getValue(2));
    CVector<int> horizontal2 = matrix.getVector(1, true);
    EXPECT_EQ(4, horizontal2.getValue(0));
    EXPECT_EQ(5, horizontal2.getValue(1));
    EXPECT_EQ(6, horizontal2.getValue(2));

    CVector<int> vertical1 = matrix.getVector(0, false);
    EXPECT_EQ(1, vertical1.getValue(0));
    EXPECT_EQ(4, vertical1.getValue(1));
    CVector<int> vertical2 = matrix.getVector(1, false);
    EXPECT_EQ(2, vertical2.getValue(0));
    EXPECT_EQ(5, vertical2.getValue(1));
    CVector<int> vertical3 = matrix.getVector(2, false);
    EXPECT_EQ(3, vertical3.getValue(0));
    EXPECT_EQ(6, vertical3.getValue(1));
}
