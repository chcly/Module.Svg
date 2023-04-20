/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "Svg/Style.h"
#include "Definitions.h"
#include "Utils/Char.h"

namespace Rt2::Svg
{

    String toStyle(StringMap& pairs)
    {
        OutputStringStream oss;
        for (const auto& [key, value] : pairs)
            Ts::print(oss, key, ':', value, ';');
        pairs.clear();
        return oss.str();
    }

    String colorOp(const Color& color)
    {
        OutputStringStream oss;
        oss << color;
        return oss.str();
    }

    Style::Style(String id) :
        _id(std::move(id))
    {
    }

    Style::~Style() = default;

    void Style::clear()
    {
        _style.clear();
    }

    void Style::fill(const Color& c)
    {
        set("fill", colorOp(c));
    }

    void Style::stroke(const Color& c, Real w)
    {
        set("stroke", colorOp(c));
        set("stroke-width", Char::toString(w));
    }

    String Style::toString()
    {
        return toStyle(_style);
    }

    String Style::toStyleSheet(const String& id)
    {
        OutputStringStream oss;
        oss << "." << id << "{" << toStyle(_style) << "}";
        return oss.str();
    }

    void Style::set(const String& str, const String& val)
    {
        _style[str] = val;
    }
}  // namespace Rt2::Svg
