#include <iostream>

#include "gtest/gtest.h"

#include "snake/Types.h"
#include "snake/utils.h"

namespace snake {

TEST(utils, incrementPointToPoint) {
    Point start = {5, 3};
    Point end = {6, 3};
    ASSERT_EQ(incrementPointTowardsPoint(start, end), end);

    start = {24, 17};
    end = {24, 0};
    ASSERT_EQ(incrementPointTowardsPoint(start, end), Point (24, 16));

    end = start;
    ASSERT_EQ(incrementPointTowardsPoint(start, end), start);

    start = {5, 3};
    end = {10, 10};
    int counter = 0;
    while (start != end){
        start = incrementPointTowardsPoint(start, end);
        ++counter;
    }
    ASSERT_EQ(counter, 12);
}  

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}