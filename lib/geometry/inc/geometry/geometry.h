#ifndef TINYRENDERER_GEOMETRY_H
#define TINYRENDERER_GEOMETRY_H

#include <vector>

namespace geometry
{

    struct Point
    {
        float x;
        float y;
    };
    typedef std::vector<Point> Line;

    Line generate_line(const Point &p1, const Point &p2);
}

#endif //TINYRENDERER_GEOMETRY_H
