//
// Created by Llikdowk on 11-Nov-16.
//

#include <gtest/gtest.h>
#include <Color.h>

#define check color

TEST(check, color) {
    Color c(1, 0, 0);
    EXPECT_EQ(c, Color::Red);
    EXPECT_NE(c, Color::White);

    Color c2(1.0f, 0.0f, 0.0f);
    EXPECT_EQ(c2, Color::Red);

    Color c3(0.5f, 0, 0);
    EXPECT_NE(c3, Color::Red);
}