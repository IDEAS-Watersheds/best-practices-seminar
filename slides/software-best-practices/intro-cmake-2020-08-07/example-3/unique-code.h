#ifndef UNIQUE_CODE_H
#define UNIQUE_CODE_H

#include <iostream>
#include <memory>

/*
 * Example copied from https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
 */
struct Vec3
{
    int x, y, z;
    Vec3() : x(0), y(0), z(0) { }
    Vec3(int x, int y, int z) :x(x), y(y), z(z) { }
    friend std::ostream& operator<<(std::ostream& os, Vec3& v) {
        return os << '{' << "x:" << v.x << " y:" << v.y << " z:" << v.z  << '}';
    }
};

void afunction(void);

#endif // UNIQUE_CODE_H


