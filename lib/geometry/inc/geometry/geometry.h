#ifndef TINYRENDERER_GEOMETRY_H
#define TINYRENDERER_GEOMETRY_H

#include <vector>

namespace geometry
{

    struct Vec2f
    {
        float x;
        float y;
    };

    struct Vec3f
    {
        float x;
        float y;
        float z;
    };

    struct Point2D
    {
        float x;
        float y;

        Vec2f operator-(Point2D other) const
        {
            return Vec2f{x-other.x, y-other.y};
        }
    };

    struct Point3D
    {
        float x;
        float y;
        float z;
        Vec3f operator-(Point3D other) const
        {
            return Vec3f{x-other.x, y-other.y, z-other.z};
        }
    };

    typedef std::vector<Point2D> Line;

    struct Triangle
    {
        Point2D p1;
        Point2D p2;
        Point2D p3;
    };

    struct BoundingBox
    {
        float left;
        float right;
        float top;
        float bottom;
    };

    Line generate_line(const Point2D &p1, const Point2D &p2);

    BoundingBox boundingbox(const Triangle& triangle);

    bool is_inside_triangle(const Point2D& point, const Triangle& triangle);

template <typename T>
float dotproduct(const T& vec)
{
    return vec.x*vec.x + vec.y*vec.y;
}
}

#endif //TINYRENDERER_GEOMETRY_H
