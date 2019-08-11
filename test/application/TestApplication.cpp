#include <gtest/gtest.h>
#include "processing/ImageTests.h"
 
TEST(SquareTest, NegativeNos) {
    ASSERT_EQ(1.0, -1*-1);
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

