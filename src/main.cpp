#include <iostream>

#include <tgaimage/tgaimage.h>
#include <geometry/geometry.h>
#include <wavefrontobjloader/model.h>

#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>

TGAColor random_color()
{
    auto r = rand() % 255;
    auto g = rand() % 255;
    auto b = rand() % 255;
    return TGAColor(r, g, b, 255);
}

const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);

void draw_line(const geometry::Line& line, TGAImage &image, const TGAColor& color)
{
    for(auto& point : line)
    {
        image.set(static_cast<int>(point.x), static_cast<int>(point.y), color);
    }
}

void draw_triangle(const geometry::Triangle& triangle, TGAImage& image)
{
    const int width = image.get_width();
    const int height = image.get_height();

    auto scale_to_image = [width, height](geometry::Point3D &p)
    {
        p.x += 1.0F;
        p.y += 1.0F;
        p.x *= width/2.0F;
        p.y *= height/2.0F;
    };

    geometry::Triangle triangle_scaled = triangle;

    scale_to_image(triangle_scaled.p1);
    scale_to_image(triangle_scaled.p2);
    scale_to_image(triangle_scaled.p3);

    geometry::BoundingBox bb = geometry::bounding_box(triangle_scaled);
    TGAColor color = random_color();
    for(int x = std::floor(bb.left); x < std::ceil(bb.right); x++)
    {
        for(int y = std::floor(bb.bottom); y <= std::ceil(bb.top); y++)
        {
            geometry::Point2D candidate_point{static_cast<float>(x),static_cast<float>(y)};
            if(geometry::is_inside_triangle(candidate_point, triangle_scaled))
            {
                image.set(x,y, color);
            }
        }
    }
}

int main(int argc, char **argv)
{
    const int width = 1000;
    const int height = 1000;
    TGAImage image(width, height, TGAImage::RGB);

    wfol::Model african_head("data/models/african_head.obj");

    auto triangles = african_head.getFaceTriangles();
    for(auto& triangle : triangles)
    {
        draw_triangle(triangle, image);
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}