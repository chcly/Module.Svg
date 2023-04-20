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

    Style* a = ctx.style("a");
    a->fill({0, 0, 0xFF, 0xFF});
    a->stroke({0x55, 0x55, 0xFF, 0x80}, 5);

    Style* b = ctx.style("b");
    b->fill({0x0, 0x0, 0x0, 0xFF});
    b->stroke({0x22, 0x22, 0xFF, 0x80}, 4);

    Style* c = ctx.style("c");
    c->fill({0xFF, 0xFF, 0xFF, 0x50});

    ctx.writeStyles();

    ctx.useStyle("");
    ctx.fillColor({0x22, 0x22, 0x22, 0xFF});
    ctx.rect(0, 0, 512, 512);

    ctx.useStyle("a");
    ctx.ellipse(128, 128, 256, 256);
    ctx.useStyle("b");
    ctx.ellipse(192, 192, 128, 128);
    ctx.useStyle("c");
    ctx.ellipse(200, 156, 64, 64);

    ctx.close();
}
