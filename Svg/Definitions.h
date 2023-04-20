#pragma once
#include "Utils/Definitions.h"
#include "Utils/StreamConverters/Hex.h"
#include "Utils/String.h"
#include "Utils/TextStreamWriter.h"

namespace Rt2::Svg
{
    using Real = double;

    struct Rect
    {
        Real x{0}, y{0};
        Real w{0}, h{0};

        friend OStream& operator<<(
            OStream&    out,
            const Rect& r)
        {
            Ts::print(out, r.x, ' ', r.y, ' ', r.w, ' ', r.h);
            return out;
        }
    };

    struct Color
    {
        uint8_t r{0x00}, g{0x00}, b{0x00}, a{0x00};

        friend OStream& operator<<(
            OStream&     out,
            const Color& c)
        {
            Ts::print(out,
                      '#',
                      Hex((uint8_t)c.r),
                      Hex((uint8_t)c.g),
                      Hex((uint8_t)c.b),
                      Hex((uint8_t)c.a));
            return out;
        }
    };
}  // namespace Rt2::Svg
