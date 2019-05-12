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
        //std::cout << point.x << " " << point.y << "\n";
    }
}

void draw_model(const wfol::Model& model, TGAImage &image)
{
    const int width = image.get_width();
    const int height = image.get_height();
    /*
    for (int i=0; i<model.nfaces(); i++) {
        std::vector<int> face = model.face(i);
        for (int j=0; j<3; j++) {
            wfol::Vec3f v0 = model.vert(face[j]);
            wfol::Vec3f v1 = model.vert(face[(j+1)%3]);
            float x0 = (v0.x+1.)*width/2.;
            float y0 = (v0.y+1.)*height/2.;
            float x1 = (v1.x+1.)*width/2.;
            float y1 = (v1.y+1.)*height/2.;

            geometry::Point2D p1 = {x0, y0};
            geometry::Point2D p2 = {x1, y1};
            geometry::Line line = geometry::generate_line(p1, p2);
            draw_line(line, image, white);
        }
    }
     */
}

void draw_triangle(const geometry::Triangle& triangle, TGAImage& image)
{
    const int width = image.get_width();
    const int height = image.get_height();

    auto scale_to_image = [width, height](geometry::Point2D &p)
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

void lesson1(TGAImage &output)
{
    wfol::Model african_head("data/models/african_head.obj");
    draw_model(african_head, output);
}

int main(int argc, char **argv)
{
    const int width = 1000;
    const int height = 1000;
    TGAImage image(width, height, TGAImage::RGB);

    //lesson1(image);

    /*
    geometry::Triangle t1 = {{10.0F, 70.0F},
                             {50.0F, 160.0F},
                             {70.0F, 80.0F}};


    geometry::Triangle t2 = {{ 180.0F, 50.0F},
                             {150.0F, 1.0F},
                             {70.0F, 180.0F}};

    geometry::Triangle t3 = {{180.0F, 150.0F}, {120.0F, 160.0F}, {130.0F, 180.0F}};

    std::vector<geometry::Triangle> triangles{t1,t2,t3};
     */
    wfol::Model african_head("data/models/african_head.obj");

    auto triangles = african_head.getFaceTriangles();
    for(auto& triangle : triangles)
    {
        draw_triangle(triangle, image);
    }

    geometry::Point2D p{10.0F, 5.0F};
    geometry::Point2D p2{2.0F, 1.0F};



    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}