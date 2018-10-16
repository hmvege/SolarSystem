#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

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

    // Copy constructor
    vec3(vec3 const &copy);

    // Copy assignement constructor
    vec3 &operator=(const vec3 &copy);

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
    inline double lengthSquared();

};

inline double vec3::length() {
    return sqrt(lengthSquared());
}

inline double vec3::lengthSquared() {
    return vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
}

inline vec3 &vec3::operator=(const vec3 &other) {
    // Copy assignement constructor
    vec[0] = other.vec[0];
    vec[1] = other.vec[1];
    vec[2] = other.vec[2];
    return *this;
}

inline vec3::vec3(const vec3 &other) {
    // Copy constructor
    vec[0] = other.vec[0];
    vec[1] = other.vec[1];
    vec[2] = other.vec[2];
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

inline double dot(const vec3 &a, const vec3 &b)
{
    return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
}

inline vec3 cross(const vec3 &a, const vec3 &b)
{
    return vec3(a.y()*b.z() - b.y()*a.z(), a.x()*b.z() - a.z()*b.x(), a.x()*b.y() - b.x()*a.y());
}

#endif // VEC3_H
