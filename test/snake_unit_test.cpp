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
    ASSERT_EQ(incrementPointTowardsPoint(start, end), Point(24, 16));

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

TEST(utils, incrementPointWithStep) {
    ASSERT_EQ(incrementPointWithStep(Point(12, 1), Direction::LEFT), Point(11, 1));
    ASSERT_EQ(incrementPointWithStep(Point(43, 12), Direction::RIGHT), Point(44, 12));
    ASSERT_EQ(incrementPointWithStep(Point(-3, -100), Direction::DOWN), Point(-3, -99));
    ASSERT_EQ(incrementPointWithStep(Point(0, 0), Direction::UP), Point(0, -1));
}

TEST(utils, directionsAreOpposite) {
    ASSERT_TRUE(directionsAreOpposite(Direction::UP, Direction::DOWN));
    ASSERT_TRUE(directionsAreOpposite(Direction::DOWN, Direction::UP));
    ASSERT_TRUE(directionsAreOpposite(Direction::LEFT, Direction::RIGHT));
    ASSERT_TRUE(directionsAreOpposite(Direction::RIGHT, Direction::LEFT));
    ASSERT_FALSE(directionsAreOpposite(Direction::UP, Direction::LEFT));
    ASSERT_FALSE(directionsAreOpposite(Direction::UP, Direction::UP));
    ASSERT_FALSE(directionsAreOpposite(Direction::UP, Direction::RIGHT));
}

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}