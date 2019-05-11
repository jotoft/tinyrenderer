#include <iostream>

#include <tgaimage/tgaimage.h>
#include <vector>

const TGAColor red = TGAColor(255, 0, 0, 255);

struct Point
{
    float x;
    float y;
};

std::vector<Point> generate_line(const Point& start, const Point& end, int numpoints)
{
    std::vector<Point> points(numpoints);

    float k = (end.y - start.y)/(end.x - start.x);
    float m = start.y - start.x*k;
    float x = start.x;
    float step_size = (end.x - start.x)/(numpoints-1.0F);
    for(int i = 0; i < numpoints; i++)
    {
        Point result = {x, x*k + m};
        points[i] = result;
        x+= step_size;
    }
    return points;
}

int main(int argc, char **argv)
{
    TGAImage image(100, 100, TGAImage::RGB);

    auto points = generate_line({10.0F, 49.0F}, {30.0F, 40.0F}, 100);

    for(auto& point : points)
    {
        image.set(static_cast<int>(point.x), static_cast<int>(point.y), red);
        std::cout << point.x << " " << point.y << "\n";
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}