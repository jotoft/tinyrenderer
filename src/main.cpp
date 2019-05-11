#include <iostream>

#include <tgaimage/tgaimage.h>
#include <vector>
#include <cmath>

const TGAColor red = TGAColor(255, 0, 0, 255);

struct Point
{
    float x;
    float y;
};

typedef std::vector<Point> Line;

Line generate_line(const Point &p1, const Point &p2)
{
    const int numpoints = std::max(std::fabs(p1.x-p2.x), std::fabs(p1.y-p2.y)) + 1;

    std::vector<Point> points(numpoints);

    float x_step = (p2.x - p1.x)/(numpoints - 1.0F);
    float y_step = (p2.y - p1.y)/(numpoints - 1.0F);

    Point p = p1;
    for(int i = 0; i < numpoints; i++)
    {
        Point result = {p.x, p.y};
        points[i] = result;
        p.x += x_step;
        p.y += y_step;
    }
    return points;
}

void draw_line(const Line& line, TGAImage &image)
{
    for(auto& point : line)
    {
        image.set(static_cast<int>(std::roundf(point.x)), static_cast<int>(std::roundf(point.y)), red);
        std::cout << point.x << " " << point.y << "\n";
    }
}

int main(int argc, char **argv)
{
    TGAImage image(100, 100, TGAImage::RGB);

    auto line = generate_line({10.0F, 49.0F}, {30.0F, 40.0F});

    auto line2 = generate_line({10.0F, 10.0F}, {10.0F, 40.0F});
    draw_line(line, image);
    draw_line(line2, image);

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}