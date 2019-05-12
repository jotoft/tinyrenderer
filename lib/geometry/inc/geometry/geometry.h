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

    std::ostream& operator<< (std::ostream& stream, const Point3D);
    std::ostream& operator<< (std::ostream& stream, const Point2D);

template <typename T>
float dotproduct(const T& vec)
{
    return vec.x*vec.x + vec.y*vec.y;
}
}

#endif //TINYRENDERER_GEOMETRY_H
