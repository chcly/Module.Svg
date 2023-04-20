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
        StyleTable        _table;
        String            _id;

    public:
        explicit Context(OStream* stream);
        ~Context();

        Style* style(const String& id);

        void save();

        void restore();

        void copy();

        void open(Real w, Real h);

        void close();

        void fillColor(const Color& color);

        void strokeColor(const Color& color, Real width = 1);

        void rect(Real x, Real y, Real w, Real h);

        void ellipse(Real x, Real y, Real w, Real h);

        void writeStyles();


        void useStyle(Style *style);

        void useStyle(const String& str);

    private:
        Style& top();

        void set(const String& str, const String& val);
    };
}  // namespace Rt2::Svg
