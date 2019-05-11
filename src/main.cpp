#include <iostream>

#include <tgaimage/tgaimage.h>
#include <geometry/geometry.h>
#include <wavefrontobjloader/model.h>

#include <vector>
#include <cmath>



const TGAColor red = TGAColor(255, 0, 0, 255);
const TGAColor white = TGAColor(255, 255, 255, 255);

void draw_line(const geometry::Line& line, TGAImage &image, const TGAColor& color)
{
    for(auto& point : line)
    {
        image.set(static_cast<int>(point.x), static_cast<int>(point.y), color);
        //std::cout << point.x << " " << point.y << "\n";
    }
}

int main(int argc, char **argv)
{
    const int width = 3000;
    const int height = 2000;
    TGAImage image(width, height, TGAImage::RGB);
    wfol::Model african_head("data/models/african_head.obj");

    for (int i=0; i<african_head.nfaces(); i++) {
        std::vector<int> face = african_head.face(i);
        for (int j=0; j<3; j++) {
            wfol::Vec3f v0 = african_head.vert(face[j]);
            wfol::Vec3f v1 = african_head.vert(face[(j+1)%3]);
            float x0 = (v0.x+1.)*width/2.;
            float y0 = (v0.y+1.)*height/2.;
            float x1 = (v1.x+1.)*width/2.;
            float y1 = (v1.y+1.)*height/2.;

            geometry::Point p1 = {x0, y0};
            geometry::Point p2 = {x1, y1};
            geometry::Line line = geometry::generate_line(p1, p2);
            draw_line(line, image, white);
        }
    }
    /*
    auto line = geometry::generate_line({10.0F, 49.0F}, {30.0F, 40.0F});

    auto line2 = geometry::generate_line({10.0F, 10.0F}, {10.0F, 40.0F});
    draw_line(line, image);
    draw_line(line2, image);
     */



    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}