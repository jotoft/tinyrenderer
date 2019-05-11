#include <geometry/geometry.h>
#include <cmath>
#include <algorithm>



namespace geometry
{
    namespace
    {
        float z_component_cross_product(const Vec2f& v1, const Vec2f& v2)
        {
            return v1.x*v2.y - v2.x*v1.y;
        }
    }
    Line generate_line(const Point &p1, const Point &p2)
    {
        const int numpoints = std::max(std::fabs(p1.x-p2.x), std::fabs(p1.y-p2.y)) + 1;

        std::vector<Point> points(numpoints);

        float x_step = (p2.x - p1.x)/(numpoints);
        float y_step = (p2.y - p1.y)/(numpoints);

        Point p = p1;
        for(int i = 0; i < numpoints; i++)
        {
            Point result = {std::round(p.x), std::round(p.y)};
            points.push_back(result);
            p.x += x_step;
            p.y += y_step;
        }
        return points;
    }
    BoundingBox boundingbox(const Triangle& triangle)
    {
        BoundingBox box;
        std::vector<Point> corners{triangle.p1, triangle.p2, triangle.p3};

        auto minmax_x = std::minmax({triangle.p1, triangle.p2, triangle.p3},
                 [](Point p1, Point p2){return p1.x < p2.x;});
        auto minmax_y = std::minmax({triangle.p1, triangle.p2, triangle.p3},
                        [](Point p1, Point p2){return p1.y < p2.y;});

        box.left = minmax_x.first.x;
        box.right = minmax_x.second.x;
        box.top = minmax_y.second.y;
        box.bottom = minmax_y.first.y;
        return box;
    }

    float signum(float in)
    {
        return in >= 0.0 ? 1.0F : -1.0F;
    }

    bool is_inside_triangle(const Point& point, const Triangle& triangle)
    {
        Vec2f p1p2 = triangle.p2 - triangle.p1;
        Vec2f p1point = point - triangle.p1;
        float z1 = z_component_cross_product(p1p2, p1point);


        Vec2f p2p3 = triangle.p3 - triangle.p2;
        Vec2f p2point = point - triangle.p2;
        float z2 = z_component_cross_product(p2p3, p2point);

        Vec2f p3p1 = triangle.p1 - triangle.p3;
        Vec2f p3point = point - triangle.p3;
        float z3 = z_component_cross_product(p3p1, p3point);

        return (signum(z1) == signum(z2)) && (signum(z2) == signum(z3));
    }
}