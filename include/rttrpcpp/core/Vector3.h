#pragma once
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <rttrpcpp/core/Serializable.h>

namespace RTTrPCpp {

template<class T>
class Vector3 : public Serializable
{
public:
    Vector3() = default;
    Vector3(T X, T Y, T Z) : x(X), y(Y), z(Z) {}
    T x = 0;
    T y = 0;
    T z = 0;

    virtual size_t toBytes(uint8_t * const buffer) override
    {
        constexpr size_t datasize = sizeof(T);
        memcpy(&buffer[datasize * 0], &x, sizeof(T));
        memcpy(&buffer[datasize * 1], &y, sizeof(T));
        memcpy(&buffer[datasize * 2], &z, sizeof(T));

        return sizeof(T) * 3;
    }

    virtual size_t fromBytes(uint8_t * const buffer) override
    {
        constexpr size_t datasize = sizeof(T);
        memcpy(&x, &buffer[datasize * 0], sizeof(T));
        memcpy(&y, &buffer[datasize * 1], sizeof(T));
        memcpy(&z, &buffer[datasize * 2], sizeof(T));

        return sizeof(T) * 3;
    }

    bool operator==(const class Vector3<T> &other) const
    {
        return x == other.x
            && y == other.y
            && z == other.z;
    }

    static Vector3<T> generateRandom()
    {
        struct timespec tv;
        clock_gettime(CLOCK_MONOTONIC, &tv);
        srand(tv.tv_nsec);
        Vector3<T> ret;

        if (std::is_integral<T>::value)
        {
            ret.x = static_cast<T>(rand());
            ret.y = static_cast<T>(rand());
            ret.z = static_cast<T>(rand());
        }
        else
        {
            ret.x = static_cast<T>(rand()) / RAND_MAX;
            ret.y = static_cast<T>(rand()) / RAND_MAX;
            ret.z = static_cast<T>(rand()) / RAND_MAX;
        }

        return ret;
    }
};

} // namespace RTTrPCpp
