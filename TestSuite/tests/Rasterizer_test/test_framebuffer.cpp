//
// Created by Llikdowk on 11-Nov-16.
//

#include <gtest/gtest.h>
#include <Color.h>
#include <FrameBuffer.h>
#include "../Utils/Format.h"

#define check raster

TEST(check, color) {
    FrameBuffer fb(800, 600);
    fb.setPixel(0, 0, Color::encode(Color::Magenta));
    EXPECT_EQ(Col(fb.getPixel(0, 0)), Col(Color::encode(Color::Magenta)));
    EXPECT_NE(Col(fb.getPixel(1, 0)), Col(Color::encode(Color::Magenta)));
}

TEST(check, copy_constructor) { // fixme? exit code 0xc0000005
    FrameBuffer t(800, 600);
    FrameBuffer fb(t); // TODO
    EXPECT_EQ(fb.width, 800);
    EXPECT_EQ(fb.height, 600);
}