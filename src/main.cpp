#include <iostream>

#include <tgaimage/tgaimage.h>
#include <geometry/geometry.h>

#include <vector>
#include <cmath>



const TGAColor red = TGAColor(255, 0, 0, 255);


void draw_line(const geometry::Line& line, TGAImage &image)
{
    for(auto& point : line)
    {
        image.set(static_cast<int>(std::roundf(point.x)), static_cast<int>(std::roundf(point.y)), red);
        //std::cout << point.x << " " << point.y << "\n";
    }
}

int main(int argc, char **argv)
{
    TGAImage image(100, 100, TGAImage::RGB);

    auto line = geometry::generate_line({10.0F, 49.0F}, {30.0F, 40.0F});

    auto line2 = geometry::generate_line({10.0F, 10.0F}, {10.0F, 40.0F});
    draw_line(line, image);
    draw_line(line2, image);

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}