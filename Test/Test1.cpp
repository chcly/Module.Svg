#include <cstdio>
#include "Svg/Context.h"
#include "gtest/gtest.h"

using namespace Rt2::Svg;

GTEST_TEST(SVG, Test_001)
{
    Rt2::OutputFileStream ofs;
    ofs.open("Test_001.svg");

    Context ctx(&ofs);
    ctx.open(512, 512);
    ctx.strokeColor(Color{0xFF, 0x00, 0xFF, 0xFF}, 5);
    ctx.fillColor(Color{0xFF, 0xFF, 0xFF, 0xFF});
    ctx.ellipse(20, 20, 200, 200);

    ctx.close();
}
