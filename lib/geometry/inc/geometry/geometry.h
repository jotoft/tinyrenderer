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

    struct Point
    {
        float x;
        float y;

        Vec2f operator-(Point other) const
        {
            return Vec2f{x-other.x, y-other.y};
        }
    };

    typedef std::vector<Point> Line;

    struct Triangle
    {
        Point p1;
        Point p2;
        Point p3;
    };

    struct BoundingBox
    {
        float left;
        float right;
        float top;
        float bottom;
    };

    Line generate_line(const Point &p1, const Point &p2);

    BoundingBox boundingbox(const Triangle& triangle);

    bool is_inside_triangle(const Point& point, const Triangle& triangle);

template <typename T>
float dotproduct(const T& vec)
{
    return vec.x*vec.x + vec.y*vec.y;
}
}

#endif //TINYRENDERER_GEOMETRY_H
