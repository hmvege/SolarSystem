#ifndef VEC3_H
#define VEC3_H

#include <iostream>

class vec3
{
private:
    double vec[3];
public:
    // Default constructor, uninitialized values
    vec3();

    // Parametetrized constructor, allows vec3(0) -> {0,0,0}
    vec3(double val);

    // Parametetrized constructor, allows vec3(1,2,3) -> {1,2,3}
    vec3(double x, double y, double z);

    // Copy constructor, allows
    vec3(vec3 const &copy);

    // Destructor
    ~vec3() {}

    // Setters
    void setXYZ(double x, double y, double z) {
        vec[0] = x;
        vec[1] = y;
        vec[2] = z;
    }

    // Getters
    double x() const { return vec[0]; }
    double y() const { return vec[1]; }
    double z() const { return vec[2]; }

    // Overloads [], makes it possible to retrieve elements by a[i].
    inline double &operator[](unsigned long i) { return vec[i]; }

    // Copy assignement constructor
    vec3 &operator=(const vec3 &other);

    // Operator overloading
    vec3 &operator*=(const vec3 other);
    vec3 &operator+=(const vec3 other);
    vec3 &operator-=(const vec3 other);
    vec3 &operator+=(const double b);
    vec3 &operator-=(const double b);
    vec3 &operator*=(const double b);
    vec3 &operator/=(const double b);

    // A cout << foo overload method.
    friend std::ostream &operator<<(std::ostream &os, const vec3 &V) {
        os << "[" << V.x() << ", " << V.y() << ", " << V.z() << "]";
        return os;
    }
    inline double length();

};

inline double vec3::length() {
    return vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
}

inline vec3 &vec3::operator=(const vec3 &other) {
    for (unsigned long i = 0; i < 3; i++) {
        vec[i] = other.vec[i];
    }
    return *this;
}

inline vec3::vec3(const vec3 &other) {
    for (unsigned long i = 0; i < 3; i++) {
        vec[i] = other.vec[i];
    }
}

inline vec3 operator*(vec3 A, const vec3 B)
{
    A *= B;
    return A;
}

inline vec3 operator+(vec3 A, const vec3 B)
{
    A += B;
    return A;
}

inline vec3 operator-(vec3 A, const vec3 B)
{
    A -= B;
    return A;
}

inline vec3 operator*(vec3 A, const double b)
{
    A *= b;
    return A;
}

inline vec3 operator/(vec3 A, const double b)
{
    A /= b;
    return A;
}

inline vec3 &vec3::operator*=(const vec3 other)
{
    for (unsigned long i = 0; i < 3; i++) {
        vec[i] *= other.vec[i];
    }
    return *this;
}

inline vec3 &vec3::operator+=(const vec3 other)
{
    for (unsigned long i = 0; i < 3; i++) {
        vec[i] += other.vec[i];
    }
    return *this;
}

inline vec3 &vec3::operator-=(const vec3 other)
{
    for (unsigned long i = 0; i < 3; i++) {
        vec[i] -= other.vec[i];
    }
    return *this;
}

inline vec3 &vec3::operator*=(const double b)
{
    for (unsigned long i = 0; i < 3; i++) {
        vec[i] *= b;
    }
    return *this;
}

inline vec3 &vec3::operator/=(const double b)
{
    for (unsigned long i = 0; i < 3; i++) {
        vec[i] /= b;
    }
    return *this;
}

inline vec3 &vec3::operator+=(const double b)
{
    for (unsigned long i = 0; i < 3; i++) {
        vec[i] += b;
    }
    return *this;
}

inline vec3 &vec3::operator-=(const double b)
{
    for (unsigned long i = 0; i < 3; i++) {
        vec[i] -= b;
    }
    return *this;
}


#endif // VEC3_H
