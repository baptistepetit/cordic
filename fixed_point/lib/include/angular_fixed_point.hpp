#pragma once

#include <cstdint>
#include <iostream>
#include <limits>
#include <type_traits>

#include "types.hpp"
#include "utils.hpp"

template<int B>
class AngularFixedPoint {
public:
    AngularFixedPoint();
    explicit AngularFixedPoint(float _data);
    explicit AngularFixedPoint(int32_t _data);
    ~AngularFixedPoint() {}

    static constexpr float resolution = 2.f * m_pi / powf(2, B);
    static constexpr AngularFixedPoint<B> max() {
        const int32_t maxData = std::numeric_limits<int32_t>::max() >> (32 - B);
        return AngularFixedPoint<B>(maxData);
    }
    static constexpr AngularFixedPoint<B> lowest() {
        const int32_t lowestData = std::numeric_limits<int32_t>::lowest() >> (32 - B);
        return AngularFixedPoint<B>(lowestData);
    }

    AngularFixedPoint<B>& operator+= (const AngularFixedPoint<B>& rhs);
    AngularFixedPoint<B>& operator-= (const AngularFixedPoint<B>& rhs);

    float toFloat() const;
    int32_t getRaw() const{ return data; }

private:
    int32_t data;
};

template<int B>
AngularFixedPoint<B>::AngularFixedPoint():
data(0)
{
    static_assert(B <= 32, "Up to 32 bits can be used for this AngularFixedPoint implementation.");
}

template<int B>
AngularFixedPoint<B>::AngularFixedPoint(float _data)
{
    static_assert(B <= 32, "Up to 32 bits can be used for this AngularFixedPoint implementation.");

    data = static_cast<int32_t>((_data) / AngularFixedPoint<B>::resolution);
    data <<= (32 - B);
    data >>= (32 - B);
}

template<int B>
AngularFixedPoint<B>::AngularFixedPoint(int32_t _data)
{
    static_assert(B <= 32, "Up to 32 bits can be used for this AngularFixedPoint implementation.");

    data = _data;
    data <<= (32 - B);
    data >>= (32 - B);
}

template<int B>
AngularFixedPoint<B>& AngularFixedPoint<B>::operator-= (const AngularFixedPoint<B>& rhs)
{
    int32_t rhsData = rhs.getRaw();

    rhsData <<= (32 - B);
    data <<= (32 - B);

    data -= rhsData;

    data >>= (32 - B);

    return *this;
}

template<int B>
AngularFixedPoint<B>& AngularFixedPoint<B>::operator+= (const AngularFixedPoint<B>& rhs)
{
    int32_t rhsData = rhs.getRaw();

    rhsData <<= (32 - B);
    data <<= (32 - B);

    data += rhsData;

    data >>= (32 - B);

    return *this;
}

template<int B>
float AngularFixedPoint<B>::toFloat() const
{
    return static_cast<float>(data) * AngularFixedPoint<B>::resolution;
}

template<int B>
inline AngularFixedPoint<B> operator+ (AngularFixedPoint<B> lhs, const AngularFixedPoint<B>& rhs)
{
    return lhs += rhs;
}

template<int B>
inline AngularFixedPoint<B> operator+ (AngularFixedPoint<B> lhs, const float& rhs)
{
    AngularFixedPoint<B> rhsFixed = AngularFixedPoint<B>(rhs);
    return lhs += rhsFixed;
}

template<int B>
inline AngularFixedPoint<B> operator- (AngularFixedPoint<B> lhs, const AngularFixedPoint<B>& rhs)
{
    return lhs -= rhs;
}

template<int B>
inline AngularFixedPoint<B> operator- (AngularFixedPoint<B> lhs, const float& rhs)
{
    AngularFixedPoint<B> rhsFixed = AngularFixedPoint<B>(rhs);
    return lhs -= rhsFixed;
}

template<int B>
inline AngularFixedPoint<B> operator- (const AngularFixedPoint<B>& rhs)
{
    return AngularFixedPoint<B>() - rhs;
}

template<int B>
inline bool operator== (AngularFixedPoint<B> lhs, const AngularFixedPoint<B>& rhs)
{
    return lhs.getRaw() == rhs.getRaw();
}

template<int B>
inline bool operator<= (AngularFixedPoint<B> lhs, const AngularFixedPoint<B>& rhs)
{
    return lhs.getRaw() <= rhs.getRaw();
}

template<int B>
inline bool operator<= (AngularFixedPoint<B> lhs, const float& rhs)
{
    AngularFixedPoint<B> rhsFixed = AngularFixedPoint<B>(rhs);
    return lhs <= rhsFixed;
}

template<int B>
inline bool operator>= (AngularFixedPoint<B> lhs, const AngularFixedPoint<B>& rhs)
{
    return lhs.getRaw() >= rhs.getRaw();
}

template<int B>
inline bool operator>= (AngularFixedPoint<B> lhs, const float& rhs)
{
    AngularFixedPoint<B> rhsFixed = AngularFixedPoint<B>(rhs);
    return lhs >= rhsFixed;
}

template<int B>
inline std::ostream& operator<< (std::ostream& os, const AngularFixedPoint<B> &rhs)
{
    os << "16#" << toHexString<B>(rhs.getRaw()) << "#";
    return os;
}
