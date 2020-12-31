#pragma once

#include <cstdint>
#include <cmath>
#include <type_traits>

template<int M, int F>
class FixedPoint {
public:
    FixedPoint();
    explicit FixedPoint(float _data);
    ~FixedPoint() {}

    static constexpr float resolution = 1.f / std::pow(2.f, F);

    FixedPoint<M, F>& operator+= (const FixedPoint<M, F>& rhs);
    FixedPoint<M, F>& operator-= (const FixedPoint<M, F>& rhs);
    FixedPoint<M, F>& operator<<= (const unsigned& rhs);
    FixedPoint<M, F>& operator>>= (const unsigned& rhs);

    float toFloat();
    int32_t getRaw() const{ return data; }

private:
    int32_t data;
};

template<int M, int F>
FixedPoint<M, F>::FixedPoint():
data(0)
{
    static_assert(M + F <= 32, "Up to 32 bits can be used for this FixedPoint implementation.");
}

template<int M, int F>
FixedPoint<M, F>::FixedPoint(float _data)
{
    static_assert(M + F <= 32, "Up to 32 bits can be used for this FixedPoint implementation.");
    data = static_cast<int32_t>(_data / FixedPoint<M, F>::resolution);
}

template<int M, int F>
FixedPoint<M, F>& FixedPoint<M, F>::operator+= (const FixedPoint<M, F>& rhs)
{
    int32_t rhsData = rhs.getRaw();

    rhsData <<= (32 - (M + F));
    data <<= (32 - (M + F));

    data += rhsData;

    data >>= (32 - (M + F));

    return *this;
}

template<int M, int F>
FixedPoint<M, F>& FixedPoint<M, F>::operator-= (const FixedPoint<M, F>& rhs)
{
    int32_t rhsData = rhs.getRaw();

    rhsData <<= (32 - (M + F));
    data <<= (32 - (M + F));

    data -= rhsData;

    data >>= (32 - (M + F));
    return *this;
}

template<int M, int F>
FixedPoint<M, F>& FixedPoint<M, F>::operator<<= (const unsigned& rhs)
{
    data <<= (32 - (M + F));
    data <<= rhs;
    data >>= (32 - (M + F));

    return *this;
}

template<int M, int F>
FixedPoint<M, F>& FixedPoint<M, F>::operator>>= (const unsigned& rhs)
{
    data >>= rhs;

    return *this;
}

template<int M, int F>
float FixedPoint<M, F>::toFloat()
{
    return static_cast<float>(data) * FixedPoint<M, F>::resolution;
}

template<int M, int F>
inline FixedPoint<M, F> operator+ (FixedPoint<M, F> lhs, const FixedPoint<M, F>& rhs)
{
    return lhs += rhs;
}

template<int M, int F>
inline FixedPoint<M, F> operator- (FixedPoint<M, F> lhs, const FixedPoint<M, F>& rhs)
{
    return lhs -= rhs;
}

template<int M, int F>
inline FixedPoint<M, F> operator- (const FixedPoint<M, F>& rhs)
{
    return FixedPoint<M, F>() - rhs;
}

template<int M, int F>
inline FixedPoint<M, F> operator<< (FixedPoint<M, F> lhs, const unsigned& rhs)
{
    return lhs <<= rhs;
}

template<int M, int F>
inline FixedPoint<M, F> operator>> (FixedPoint<M, F> lhs, const unsigned& rhs)
{
    return lhs >>= rhs;
}
