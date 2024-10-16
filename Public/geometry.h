#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <array>
#include <complex>
#include <initializer_list>
#include <ostream>

template <typename T>
struct Vec2{
    union{
        struct{T x, y;};
        struct{T u, v;};
    };
    Vec2(): x(0), y(0) {}
    Vec2(T _x, T _y): x(_x), y(_y) {}
    T operator[](const int i) const{
        return i == 0 ? x : y;
    }
};


typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;

template<typename T>
Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b){
    return Vec2<T>{a.x + b.x, a.y + b.y};
}

template <typename T>
Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b){
    return Vec2<T>{a.x - b.x, a.y - b.y};
}

template <typename T,typename U>
Vec2<T> operator*(const Vec2<T>& a, const U& b){
    return Vec2<T>{static_cast<T>(a.x * b), static_cast<T>(a.y * b)};
}

template <typename T, typename U>
Vec2<T> operator/(const Vec2<T>& a, const U& b) {
    return Vec2<T>{static_cast<T>(a.x / b), static_cast<T>(a.y / b)};
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec2<T>& v){
    os <<'{'<< v.x << ',' << v.y << '}';
    return os;
}

template <typename T>
T dot(const Vec2<T>& a, const Vec2<T>& b){
    return a.x * b.x + a.y * b.y;
}

template <typename T>
T cross(const Vec2<T>& a, const Vec2<T>& b){
    return a.x * b.y - a.y * b.x;
}


template <typename T>
struct Vec3{
    union {
        struct {T x, y, z;};
        struct {T u, v, w;};
    };
    void normalize() {
        *this=*this/std::sqrt(x*x + y*y + z*z);
    };
    /*
     *Vec3 normalize() const{
     *   return *this / std::sqrt(x*x + y*y + z*z);
     *   }
     *
     */
};

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

template <typename T>
Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b){
    return Vec3<T>{a.x + b.x, a.y + b.y, a.z + b.z};
}

template <typename T>
Vec3<T> operator-(const Vec3<T>& a, const Vec3<T>& b){
    return Vec3<T>{a.x - b.x, a.y - b.y, a.z - b.z};
}

template <typename T, typename U>
Vec3<T> operator*(const Vec3<T>& a, const U& b){
    return Vec3<T>{a.x * b, a.y * b, a.z * b};
}

template <typename T, typename U>
Vec3<T> operator/(const Vec3<T>& a, const U& b){
    return Vec3<T>{a.x / b, a.y / b, a.z / b};
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec3<T>& v){
    os <<'{'<< v.x << ',' << v.y << ',' << v.z << '}';
    return os;
}

template <typename T>
T dot(const Vec3<T>& a, const Vec3<T>& b){
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b){
    return Vec3<T>{a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

template <typename T>
struct Vec4{
    T x, y, z, w;
    T r, g, b, a;
};

typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i; 

template <typename T>
Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b){
    return Vec4<T>{a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

template <typename T>
Vec4<T> operator-(const Vec4<T>& a, const Vec4<T>& b){
    return Vec4<T>{a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

template <typename T, typename U>
Vec4<T> operator*(const Vec4<T>& a, const U& b){
    return Vec4<T>{a.x * b, a.y * b, a.z * b, a.w * b};
}

template <typename T>
T dot(Vec4<T>& a, Vec4<T>& b){
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vec4<T>& v){
    os <<'{'<< v.x << ',' << v.y << ',' << v.z << ',' << v.w << '}';
    return os;
}

template <typename T>
struct Matrix4{
    std::array<T,16> data;
    Matrix4():data({0}){}
    T get_index(int i, int j) const{
        return data[i * 4 + j];
    }    
    Matrix4(std::initializer_list<T> list) requires requires{list.size() == 16;}{
        int i = 0;
        for(auto it = list.begin(); it != list.end(); it++){
            data[i++] = *it;
        }
    }
};

typedef Matrix4<float> Matrix4f;
typedef Matrix4<int> Matrix4i;

template <typename T>
Matrix4<T> operator*(const Matrix4<T>& a, const Matrix4<T>& b){
    Matrix4<T> result;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            T sum = 0;
            for(int k = 0; k < 4; k++){
                sum += a.get_index(i, k) * b.get_index(k, j);
            }
            result.data[i * 4 + j] = sum;
        }
    }
    return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix4<T>& m){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            os << m.get_index(i, j) << ' ';
        }
        os << std::endl;
    }
    return os;
}

#endif