#include <gtest/gtest.h>

#include <vector>
#include "vector.hpp"


namespace{
TEST(VectorTest, VectorInitStd) {
    std::vector<double> v = {1., 2., 3., 4., 5.};
    Vector<5> w(v);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(w[i], v[i]);
    }
}

TEST(VectorTest, VectorSize) {
    Vector<8> v(0);
    EXPECT_EQ(v.to_std_vector().size(), 8);
    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(v[i], 0);
    }
}

TEST(VectorTest, VectorPlus){
    Vector<5> v = std::vector<double>{1., 2., 3., 4., 5.};
    Vector<5> w = std::vector<double>{5., 4., 3., 2., 1.};
    Vector<5> u = v + w;
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(u[i], 6);
    }
}

TEST(VectorTest, VectorMinus){
    Vector<5> v = std::vector<double>{1., 2., 3., 4., 5.};
    Vector<5> w = std::vector<double>{5., 4., 3., 2., 1.};
    Vector<5> u = v - w;
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(u[i], 2*i - 4);
    }
}

TEST(VectorTest, VectorTimes){
    Vector<5> v = std::vector<double>{1., 2., 3., 4., 5.};
    Vector<5> u = v * 2;
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(u[i], 2 * v[i]);
    }
}

TEST(VectorTest, VectorDivide){
    Vector<5> v = std::vector<double>{1., 2., 3., 4., 5.};
    Vector<5> u = v / 2;
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(u[i], v[i] / 2);
    }
}

TEST(VectorTest, VectorDot){
    Vector<5> v = std::vector<double>{1., 2., 3., 4., 5.};
    Vector<5> w = std::vector<double>{5., 4., 3., 2., 1.};
    Vector<5> u = v*w;
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(u[i], v[i] * w[i]);
    }
}

}  // namespace