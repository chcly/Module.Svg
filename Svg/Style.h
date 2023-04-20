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
#pragma once
#include "Definitions.h"
#include "Utils/HashMap.h"
#include "Utils/Stack.h"
#include "Utils/String.h"

namespace Rt2::Svg
{
    class Style
    {
    private:
        StringMap _style;
        String    _id{};

    public:
        Style() = default;
        explicit Style(String id);
        ~Style();

        const String& id();

        void clear();

        bool empty() const;

        void fill(const Color& c);

        void stroke(const Color& c, Real w);

        String toString();

        String toStyleSheet(const String& id);


        void set(const String& str, const String& val);
    };

    inline const String& Style::id()
    {
        return _id;
    }

    inline bool Style::empty() const
    {
        return _style.empty();
    }

    using StyleStack = Stack<Style>;
    using StyleTable = HashTable<String, Style*>;
}  // namespace Rt2::Svg
