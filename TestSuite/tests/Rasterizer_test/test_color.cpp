//
// Created by Llikdowk on 11-Nov-16.
//

#include <gtest/gtest.h>
#define private public // TODO change this hack
#include <Color.h>
#include <iostream>
#include "../Utils/Format.h"


TEST(check, constructor) {
    Color c = Color::ColorNormalized(1, 0, 0);
    EXPECT_EQ(c, Color::Red);
    EXPECT_NE(c, Color::White);

    Color c2 = Color::ColorNormalized(1.0f, 0.0f, 0.0f);
    EXPECT_EQ(c2, Color::Red);

    Color c3 = Color::ColorNormalized(0.5f, 0, 0);
    EXPECT_NE(c3, Color::Red);
}

TEST(check, code) {
	Color c = Color::Color256(255, 0, 255);//Color::Magenta;
	std::cout << std::endl;
    std::cout << Hex(c.data[0]) << std::endl;
	std::cout << Hex(c.data[1]) << std::endl;
	std::cout << Hex(c.data[2]) << std::endl;
	std::cout << Hex(c.data[3]) << std::endl;
	std::cout << Hex(*(uint32_t*)c.data) << std::endl;
	std::cout << Hex(c.encode(c)) << std::endl;
}
