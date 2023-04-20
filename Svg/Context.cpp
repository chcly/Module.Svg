#include "Svg/Context.h"
#include "Svg/Writers.h"
#include "Utils/Char.h"

namespace Rt2::Svg
{
    Context::Context(OStream* stream)
    {
        _out.bind(&std::cout);
        _out._push(stream);
    }

    Context::~Context()
    {
        _out.flush();

        for (const auto& v : _table)
            delete v.second;
    }

    Style* Context::style(const String& id)
    {
        Style* st;
        if (const size_t loc = _table.find(id); loc != Npos)
            st = _table.at(loc);
        else
        {
            st = new Style();
            _table.insert(id, st);
        }
        return st;
    }

    Style& Context::top()
    {
        if (_stack.empty())
            save();
        return _stack.top();
    }

    void Context::set(const String& str, const String& val)
    {
        Style& data = top();
        data.set(str, val);
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
                   " xmlns=\"http://www.w3.org/2000/svg\"",
                   " xmlns:svg=\"http://www.w3.org/2000/svg\" ",
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
        top().fill(color);
    }

    void Context::strokeColor(const Color& color, const Real width)
    {
        top().stroke(color, width);
    }

    void Context::rect(Real x, Real y, Real w, Real h)
    {
        copy();
        Style& data = top();

        const bool hasStyle = !data.empty() || !_id.empty();
        _out.print("<rect ",
                   AttrF("x", Rp(x)),
                   AttrF("y", Rp(y)),
                   AttrF("width", Rp(w)),
                   AttrF("height", Rp(h), hasStyle));
        if (hasStyle)
        {
            if (!_id.empty())
                _out.print(AttrS("class", _id, false));
            else
                _out.print(AttrS("style", data.toString(), false));
        }

        _out.print('/', '>');
        restore();
    }

    void Context::ellipse(const Real x, const Real y, const Real w, const Real h)
    {
        copy();
        Style& data = top();

        const Real rx = w / 2;
        const Real ry = h / 2;
        const Real cx = x + rx;
        const Real cy = y + ry;
        const bool hasStyle = !data.empty() || !_id.empty();

        _out.print("<ellipse ",
                   AttrF("rx", Rp(rx)),
                   AttrF("ry", Rp(ry)),
                   AttrF("cx", Rp(cx)),
                   AttrF("cy", Rp(cy), hasStyle));

        if (hasStyle)
        {
            if (!_id.empty())
                _out.print(AttrS("class", _id, false));
            else
                _out.print(AttrS("style", data.toString(), false));
        }

        _out.print('/', '>');
        restore();
    }

    void Context::writeStyles()
    {
        _out.print("<style>");
        for (const auto& v : _table)
            _out.print(v.second->toStyleSheet(v.first));
        _out.print("</style>");
    }

    void Context::useStyle(const String& str)
    {
        _id = str;
    }
}  // namespace Rt2::Svg
