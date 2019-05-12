#include <geometry/geometry.h>
#include <cmath>
#include <algorithm>



namespace geometry
{
    namespace
    {
        template<typename T>
        float z_component_cross_product(const T& v1, const T& v2)
        {
            return v1.x*v2.y - v2.x*v1.y;
        }
    }
    Line generate_line(const Point2D &p1, const Point2D &p2)
    {
        const int numpoints = std::max(std::fabs(p1.x-p2.x), std::fabs(p1.y-p2.y)) + 1;

        std::vector<Point2D> points(numpoints);

        float x_step = (p2.x - p1.x)/(numpoints);
        float y_step = (p2.y - p1.y)/(numpoints);

        Point2D p = p1;
        for(int i = 0; i < numpoints; i++)
        {
            Point2D result = {std::round(p.x), std::round(p.y)};
            points.push_back(result);
            p.x += x_step;
            p.y += y_step;
        }
        return points;
    }
    BoundingBox bounding_box(const Triangle &triangle)
    {
        BoundingBox box;
        std::vector<Point2D> corners{triangle.p1, triangle.p2, triangle.p3};

        auto minmax_x = std::minmax({triangle.p1, triangle.p2, triangle.p3},
                 [](Point2D p1, Point2D p2){return p1.x < p2.x;});
        auto minmax_y = std::minmax({triangle.p1, triangle.p2, triangle.p3},
                        [](Point2D p1, Point2D p2){return p1.y < p2.y;});

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

    bool is_inside_triangle(const Point2D& point, const Triangle& triangle)
    {

        Vector2D p1p2 = triangle.p2 - triangle.p1;
        Vector2D p1point = point - triangle.p1;
        float z1 = z_component_cross_product(p1p2, p1point);


        Vector2D p2p3 = triangle.p3 - triangle.p2;
        Vector2D p2point = point - triangle.p2;
        float z2 = z_component_cross_product(p2p3, p2point);

        Vector2D p3p1 = triangle.p1 - triangle.p3;
        Vector2D p3point = point - triangle.p3;
        float z3 = z_component_cross_product(p3p1, p3point);

        return (signum(z1) == signum(z2)) && (signum(z2) == signum(z3));
    }

    std::ostream &operator<<(std::ostream &stream, const Point3D point) {
        stream << point.x << " " << point.y << " " << point.z;
        return stream;
    }

    std::ostream &operator<<(std::ostream &stream, const Point2D point) {
        stream << point.x << " " << point.y;
        return stream;
    }

    bool is_inside_triangle_barycentric(const Point2D &p, const Triangle &triangle) {
        auto barycentric_coords = barycentric(triangle, p);
        return (barycentric_coords.x >=0.0F) && (barycentric_coords.y >= 0.0F) && (barycentric_coords.z >= 0.0F);
    }
}