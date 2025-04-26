#include "pch.h"
#include <iostream>
#include "boost/algorithm/test/hello_world.h"
#include "gtest/gtest.h"

using namespace boost::algorithm::test;


//∂®“Â≤‚ ‘
TEST(PrintHelloTest, BasicAssertions) {
	EXPECT_EQ(PrintHello(), "Hello World.");
}

TEST(MathTest, Addition) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(MathTest, Subtraction) {
    EXPECT_EQ(5 - 3, 2);
}

#define GOOGLE_TEST
#ifdef GOOGLE_TEST
// main∫Ø ˝
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int result =  RUN_ALL_TESTS();
    std::cin.get();
    return result;
}
#endif // GOOGLE_TEST

