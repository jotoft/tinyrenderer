#include <geometry/geometry.h>
#include <cmath>

namespace geometry
{
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
}