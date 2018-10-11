#ifndef VEC3_H
#define VEC3_H

class vec3
{
private:
    double vec[3];
public:
    vec3();
    vec3(double val);
    vec3(double x, double y, double z);
    vec3(const vec3 &obj);
    ~vec3() {}

    inline double &operator[](unsigned long i) { return vec[i]; }

//    vec3 &operator=(const vec3 &B);
    vec3 &operator=(const vec3 &other);

    // Operations
    vec3 &operator*=(const vec3 other);
    vec3 &operator+=(const vec3 other);
    vec3 &operator-=(const vec3 other);
    vec3 &operator+=(const double b);
    vec3 &operator-=(const double b);
    vec3 &operator*=(const double b);
    vec3 &operator/=(const double b);

    // Prient operator
//    friend std::ostream& operator<<(std::ostream& os, const vec3& v);

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

//std::ostream& operator<<(std::ostream& os, const vec3& v)
//{
//    os << v.vec[0] << " " << v.vec[1] << " " << v.vec[2];
//    return os;
//}

#endif // VEC3_H
