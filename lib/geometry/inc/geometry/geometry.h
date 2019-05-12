#ifndef TINYRENDERER_GEOMETRY_H
#define TINYRENDERER_GEOMETRY_H

#include <vector>
#include <ostream>
#include <cmath>
namespace geometry
{

    struct Vector2D
    {
        float x;
        float y;
    };

    struct Vector3D
    {
        float x;
        float y;
        float z;
        operator Vector2D() const {
            return Vector2D{x,y};
        }
        void normalize()
        {
            float length = sqrtf(x*x + y*y + z*z);
            x /= length;
            y /= length;
            z /= length;
        }

        float dot(const Vector3D& v) const
        {
            return x*v.x + y*v.y + z*v.z;
        }

        Vector3D cross(const Vector3D& v) const
        {
            float x_cross = y*v.z - z*v.y;
            float y_cross = z*v.x - x*v.z;
            float z_cross = x*v.y - y*v.x;
            return Vector3D{x_cross, y_cross, z_cross};
        }
    };

    struct Point2D
    {
        float x;
        float y;

        Vector2D operator-(Point2D other) const
        {
            return Vector2D{x-other.x, y-other.y};
        }

        void operator*=(float scale)
        {
            x*=scale;
            y*=scale;
        }
    };

    struct Point3D
    {
        float x;
        float y;
        float z;
        Vector3D operator-(Point3D other) const
        {
            return Vector3D{x-other.x, y-other.y, z-other.z};
        }

        operator Point2D() const
        {
            return Point2D{x,y};
        }
    };

    typedef std::vector<Point2D> Line;

    struct Triangle
    {
        Point3D p1;
        Point3D p2;
        Point3D p3;

        Vector3D normal() const
        {
            auto p1p2 = p2-p1;
            auto p1p3 = p3-p1;
            auto cross = p1p2.cross(p1p3);
            cross.normalize();
            return cross;
        }
    };

    struct BoundingBox
    {
        float left;
        float right;
        float top;
        float bottom;
    };

    Line generate_line(const Point2D &p1, const Point2D &p2);

    BoundingBox bounding_box(const Triangle &triangle);

    bool is_inside_triangle(const Point2D& point, const Triangle& triangle);
    bool is_inside_triangle_barycentric(const Point2D& p, const Triangle& triangle);

    inline Point3D barycentric(const Triangle& triangle, const Point2D& p)
    {
        auto p1p2 = triangle.p2 - triangle.p1;
        auto p1p3 = triangle.p3 - triangle.p1;
        Point2D p1p {triangle.p1.x-p.x, triangle.p1.y - p.y};
        Vector3D x_comp {p1p2.x, p1p3.x, p1p.x};
        Vector3D y_comp {p1p2.y, p1p3.y, p1p.y};

        Vector3D cross = x_comp.cross(y_comp);
        Point3D barycentric_coord{cross.x/cross.z, cross.y/cross.z, cross.z/cross.z};
        barycentric_coord.z = 1.0F - barycentric_coord.x - barycentric_coord.y;
        return barycentric_coord;
    }

    std::ostream& operator<< (std::ostream& stream, const Point3D);
    std::ostream& operator<< (std::ostream& stream, const Point2D);

template <typename T>
float dotproduct(const T& vec)
{
    return vec.x*vec.x + vec.y*vec.y;
}
}

#endif //TINYRENDERER_GEOMETRY_H
