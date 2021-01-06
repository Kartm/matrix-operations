#include "gtest/gtest.h"

#include "CVector.h"

TEST(CVectorTest, creates_with_size
) {
    CVector<int> vector(4);

    EXPECT_EQ(4, vector.getSize());
}

TEST(CVectorTest, get_set_value
) {
    CVector<int> vector(2);
    vector.setValue(0, 1);
    vector.setValue(1, 10);

    EXPECT_EQ(1, vector.getValue(0));
    EXPECT_EQ(10, vector.getValue(1));
}

TEST(CVectorTest, dot_product
) {
    CVector<int> vectorA(3);
    vectorA.setValue(0, 1);
    vectorA.setValue(1, 10);
    vectorA.setValue(2, 20);

    CVector<int> vectorB(3);
    vectorB.setValue(0, 2);
    vectorB.setValue(1, 1);
    vectorB.setValue(2, 1);

    EXPECT_EQ(32, vectorA.dotProduct(vectorB));
}

TEST(CVectorTest, copy
) {
    CVector<int> vectorA(3);
    vectorA.setValue(0, 1);
    vectorA.setValue(1, 10);
    vectorA.setValue(2, 20);

    CVector<int> vectorB = vectorA;

    EXPECT_EQ(1, vectorB.getValue(0));
    EXPECT_EQ(10, vectorB.getValue(1));
    EXPECT_EQ(20, vectorB.getValue(2));

    EXPECT_EQ(1, vectorA.getValue(0));
    EXPECT_EQ(10, vectorA.getValue(1));
    EXPECT_EQ(20, vectorA.getValue(2));
}

TEST(CVectorTest, from_dynamic_array
) {
    int* vectorArray = new int[3];
    vectorArray[0] = 111;
    vectorArray[1] = 222;
    vectorArray[2] = 333;

    CVector<int> vector(3, vectorArray);

    EXPECT_EQ(111, vector.getValue(0));
    EXPECT_EQ(222, vector.getValue(1));
    EXPECT_EQ(333, vector.getValue(2));
}
