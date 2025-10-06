#include <gtest/gtest.h>
#include "../include/eleven.h"

using namespace std;

TEST(test_01, defaultConstructor)
{
    Eleven zero;
    EXPECT_EQ(zero.to_str(), "0");
}

TEST(test_02, initialization)
{
    Eleven arr(5, 3);
    EXPECT_EQ(arr.to_str(), "33333");

    Eleven arr1{1, 2, 3, 4};
    EXPECT_EQ(arr1.to_str(), "4321");

    EXPECT_THROW(Eleven arr2(5, 'X'), invalid_argument);
}

TEST(test_03, stringSource)
{
    Eleven arr("15A");
    EXPECT_EQ(arr.to_str(), "15A");

    Eleven arr1("990");
    EXPECT_EQ(arr1.to_str(),"990");

    EXPECT_THROW(Eleven arr3("15B"), invalid_argument);
    
    EXPECT_THROW(Eleven arr4(""), invalid_argument);
}

TEST(test_04, copy)
{
    Eleven arr("15A");
    Eleven arr1 = arr.copy();
    EXPECT_EQ(arr1.to_str(), "15A");
}

TEST(test_05, move)
{
    Eleven arr("15A");
    Eleven moved(std::move(arr));
    EXPECT_EQ(moved.to_str(), "15A");
    EXPECT_EQ(arr.to_str(), "0");
}

TEST(test_06, summa)
{
    Eleven arr("22");
    Eleven arr1("123");
    Eleven summa = arr.add(arr1);
    EXPECT_EQ(summa.to_str(), "145");

    Eleven arr2("990");
    Eleven arr3("AA");
    Eleven summa1 = arr2.add(arr3);
    EXPECT_EQ(summa1.to_str(), "A8A");

    Eleven arr4("0");
    Eleven summa2 = arr.add(arr4);
    EXPECT_EQ(summa2.to_str(), "22");
}

TEST(test_07, minus)
{
    Eleven arr("22");
    Eleven arr1("123");
    Eleven diff = arr1.minus(arr);
    EXPECT_EQ(diff.to_str(), "101");

    Eleven arr2("990");
    Eleven arr3("AA");
    Eleven diff1 = arr2.minus(arr3);
    EXPECT_EQ(diff1.to_str(), "891");

    Eleven arr4("990");
    Eleven diff2 = arr2.minus(arr4);
    EXPECT_EQ(diff2.to_str(), "0");

    EXPECT_THROW(arr.minus(arr1), logic_error);
}

TEST(test_08, eqTest)
{
    Eleven arr("333");
    Eleven arr1("333");
    Eleven arr2("1");

    EXPECT_TRUE(arr.eq(arr1));
    EXPECT_FALSE(arr.eq(arr2));
}

TEST(test_09, lqTest)
{
    Eleven arr("333");
    Eleven arr1("333");
    Eleven arr2("1");

    EXPECT_TRUE(arr2.lq(arr));
    EXPECT_FALSE(arr.lq(arr2));
    EXPECT_FALSE(arr.lq(arr1));
}

TEST(test_10, gqTest)
{
    Eleven arr("333");
    Eleven arr1("333");
    Eleven arr2("1");

    EXPECT_TRUE(arr.gq(arr2));
    EXPECT_FALSE(arr2.gq(arr));
    EXPECT_FALSE(arr.gq(arr1));
}

TEST(test_11, remove_zero)
{
    Eleven arr("001");
    EXPECT_EQ(arr.to_str(), "1");

    Eleven arr1("000000000000000000");
    EXPECT_EQ(arr1.to_str(), "0");

    Eleven arr2{0, 3, 2, 1, 0, 0, 0};
    EXPECT_EQ(arr2.to_str(), "1230");
}

TEST(test_12, immutable)
{
    Eleven arr("777");
    EXPECT_EQ(arr.to_str(), "777");

    Eleven arr1 = arr.copy();
    Eleven arr2("1");
    Eleven arr3 = arr.add(arr2);
    Eleven arr4 = arr.minus(arr2);

    EXPECT_EQ(arr1.to_str(), "777");
    EXPECT_EQ(arr3.to_str(), "778");
    EXPECT_EQ(arr4.to_str(), "776");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
