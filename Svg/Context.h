#pragma once
#include "Definitions.h"
#include "Style.h"
#include "Utils/StackStream.h"

namespace Rt2::Svg
{

    class Context
    {
    private:
        OutputStreamStack _out;
        StyleStack        _stack;

    public:
        explicit Context(OStream* stream);
        ~Context();

        void save();
        void restore();
        void copy();

        void open(Real w, Real h);

        void close();

        void fillColor(const Color& color);

        void strokeColor(const Color& color, Real width = 1, Real opacity = 1);

        void rect(Real x, Real y, Real w, Real h);
        void ellipse(Real x, Real y, Real w, Real h);

    private:
        StyleData& top();

        void set(const String& str, const String& val);
    };
}  // namespace Rt2::Svg
