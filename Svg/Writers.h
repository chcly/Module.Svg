#pragma once
#include <functional>
#include "Definitions.h"
#include "Utils/Definitions.h"
#include "Utils/StreamConverters/Float.h"
#include "Utils/StreamConverters/OutOperator.h"

namespace Rt2::Svg
{
    template<typename T>
    bool isNotEmpty(const T& v)
    {
        return !v.empty();
    }

    template <typename T>
    class Attr : OutOperator<Attr<T>>
    {
    private:
        using CheckFn = std::function<bool(const T&)>;

        String        _key;
        T             _val;
        bool          _hasMore;
        const CheckFn _fn;

        bool valid() const
        {
            // conditionally write to
            // the stream if it's not empty
            return _fn ? _fn(_val) : true;
        }

        static bool isValid(const T&)
        {
            return true;
        }

    public:
        explicit Attr(String key, T val, bool hasMore = true, CheckFn cb = isValid) :
            _key(std::move(key)),
            _val(std::move(val)),
            _hasMore(hasMore),
            _fn(std::move(cb))
        {
        }

        OStream& operator()(OStream& out) const
        {
            if (!valid())
                return out;
            out << _key << '=' << '"' << _val << '"';
            if (_hasMore)
                out << ' ';
            return out;
        }
    };


    using  Rp = FPrintT<Real, 3, 3>;

    using AttrI = Attr<I32>;
    using AttrS = Attr<String>;
    using AttrF = Attr<Rp>;
    using AttrR = Attr<Rect>;

}  // namespace Rt2::Svg