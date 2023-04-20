#include "Svg/Context.h"
#include "Svg/Writers.h"
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

    Context::Context(OStream* stream)
    {
        _out.bind(&std::cout);
        _out._push(stream);
    }

    Context::~Context()
    {
        _out.flush();
    }

    StyleData& Context::top()
    {
        if (_stack.empty())
            save();
        return _stack.top();
    }

    void Context::set(const String& str, const String& val)
    {
        StyleData& data = top();
        data.attrs[str] = val;
    }

    void Context::save()
    {
        _stack.push({});
    }

    void Context::restore()
    {
        if (!_stack.empty())
            _stack.pop();
        if (_stack.empty())
            save();
    }

    void Context::copy()
    {
        _stack.push(top());
    }

    void Context::open(Real w, Real h)
    {
        _out.print("<svg ",
                   AttrF("width", Rp(w)),
                   AttrF("height", Rp(w)),
                   AttrR("viewbox", {0, 0, w, h}, false),
                   ">");
    }

    void Context::close()
    {
        _out.print("</svg>");
    }

    void Context::fillColor(const Color& color)
    {
        set("fill", colorOp(color));
    }

    void Context::strokeColor(const Color& color, Real width, Real opacity)
    {
        set("stroke", colorOp(color));
        set("stroke-opacity", Char::toString(opacity));
        set("stroke-width", Char::toString(width));
    }

    void Context::rect(Real x, Real y, Real w, Real h)
    {
        StyleData& data = top();
        save();

        if (data.attrs.empty())
        {
            _out.print("<rect ",
                       AttrF("x", Rp(x)),
                       AttrF("y", Rp(y)),
                       AttrF("width", Rp(w)),
                       AttrF("height", Rp(h), false),
                       '/',
                       '>');
        }
        else
        {
            _out.print("<rect ",
                       AttrF("x", Rp(x)),
                       AttrF("y", Rp(y)),
                       AttrF("width", Rp(w)),
                       AttrF("height", Rp(h)),
                       AttrS("style", toStyle(data.attrs), false),
                       '/',
                       '>');
        }
        restore();
    }

    void Context::ellipse(Real x, Real y, Real w, Real h)
    {
        StyleData& data = top();
        save();

        Real rx = w / 2;
        Real ry = h / 2;
        Real cx = x + rx;
        Real cy = y + ry;
        _out.print("<ellipse ",
                   AttrF("rx", Rp(rx)),
                   AttrF("ry", Rp(ry)),
                   AttrF("cx", Rp(cx)),
                   AttrF("cy", Rp(cy), !data.attrs.empty()));

        if (!data.attrs.empty())
            _out.print(AttrS("style", toStyle(data.attrs), false));
        _out.print('/', '>');
        restore();
    }
}  // namespace Rt2::Svg
