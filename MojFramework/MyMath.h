#pragma once
#include <cmath>

constexpr float PI = 3.14159265f;
constexpr double PI_D = 3.1415926535897932;

template <typename T>
inline auto sq(const T& x)
{
    return x * x;
}

template<typename T>
inline T wrap_angle(T theta)
{
    const T two_pi = T(2.0) * T(PI_D);
    const T modded = std::fmod(theta, two_pi);
    return (modded > T(PI_D)) ? (modded - two_pi) : modded;
}