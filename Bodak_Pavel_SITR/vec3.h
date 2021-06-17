#pragma once

#include <cmath>

class vec3
{
	double _m_x, _m_y, _m_z;
    
public:
	vec3(double x = 0., double y = 0., double z = 0.) :_m_x(x), _m_y(y), _m_z(z) {}
    vec3(const vec3& other):
        _m_x(other._m_x),
        _m_y(other._m_y),
        _m_z(other._m_z)
    {
    }

    vec3& operator=(const vec3& other)
    {
        _m_x = other._m_x;
        _m_y = other._m_y;
        _m_z = other._m_z;

        return *this;
    }
	
    static vec3 crossProduct(const vec3& vec1, const vec3& vec2)
    {
        return vec3(vec1._m_y * vec2._m_z - vec1._m_z * vec2._m_y,
            vec1._m_z * vec2._m_x - vec1._m_x * vec2._m_z,
            vec1._m_x * vec2._m_y - vec1._m_y * vec2._m_x);
    }

    double length() const
    {
        return std::sqrt(_m_x * _m_x + _m_y * _m_y + _m_z * _m_z);
    }

    void normalize()
    {
        if (isNull()) return;
        const double inv_Len = 1.0 / length();
        _m_x *= inv_Len;
        _m_y *= inv_Len;
        _m_z *= inv_Len;

    }

    bool isNull() const
    {
        return (_m_x == 0. && _m_y == 0. && _m_z == 0.);
    }

    vec3& operator -=(const vec3& other)
    {
        _m_x -= other._m_x;
        _m_y -= other._m_y;
        _m_z -= other._m_z;

        return *this;
    }

    vec3& operator +=(const vec3& other)
    {
        _m_x += other._m_x;
        _m_y += other._m_y;
        _m_z += other._m_z;

        return *this;
    }


    friend inline const vec3 operator -(const vec3& v1, const vec3& v2);
};

inline const vec3 operator -(const vec3& v1, const vec3& v2)
{
    return vec3(v1._m_x - v2._m_x, v1._m_y - v2._m_y, v1._m_z - v2._m_z);
}


//
// Calculate smooth (average) per-vertex normals
//
// [out] normals - output per-vertex normals
// [in] verts - input per-vertex positions
// [in] faces - triangles (triplets of vertex indices)
// [in] nverts - total number of vertices (# of elements in verts and normals arrays)
// [in] nfaces - total number of faces (# of elements in faces array)
//
void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces);
