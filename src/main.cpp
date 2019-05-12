#include <iostream>

#include <tgaimage/tgaimage.h>
#include <geometry/geometry.h>
#include <wavefrontobjloader/model.h>

#include <vector>
#include <cmath>
#include <string>
#include <cstdlib>
#include <climits>

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

void draw_triangle(const geometry::Triangle& triangle, TGAImage& image, std::vector<float>& z_buffer, TGAImage& texture)
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

    const geometry::Vector3D light_direction{0.0F, 0.0F, 1.0F};


    geometry::BoundingBox bb = geometry::bounding_box(triangle_scaled);
    TGAColor color = random_color();
    for(int x = std::floor(bb.left); x < std::ceil(bb.right); x++)
    {
        for(int y = std::floor(bb.bottom); y <= std::ceil(bb.top); y++)
        {
            geometry::Point2D candidate_point{static_cast<float>(x),static_cast<float>(y)};
            auto bc_coords = geometry::barycentric(triangle_scaled, candidate_point);
            if(geometry::is_inside_triangle_barycentric(bc_coords))
            {

                auto norm_x = triangle.normp1.x*bc_coords.x + triangle.normp2.x*bc_coords.y + triangle.normp3.x*bc_coords.z;
                auto norm_y = triangle.normp1.y*bc_coords.x + triangle.normp2.y*bc_coords.y + triangle.normp3.y*bc_coords.z;
                auto norm_z = triangle.normp1.z*bc_coords.x + triangle.normp2.z*bc_coords.y + triangle.normp3.z*bc_coords.z;

                geometry::Vector3D normal_vec{norm_x, norm_y, norm_z};

                float brightness = normal_vec.dot(light_direction);
                if(brightness > 0.0F) {
                    auto interpolated_z = triangle_scaled.p1.z*bc_coords.x +
                            triangle_scaled.p2.z*bc_coords.y +
                            triangle_scaled.p3.z*bc_coords.z;

                    auto interpolated_u = triangle.texp1.x*bc_coords.x + triangle.texp2.x*bc_coords.y + triangle.texp3.x*bc_coords.z;
                    auto interpolated_v = triangle.texp1.y*bc_coords.x + triangle.texp2.y*bc_coords.y + triangle.texp3.y*bc_coords.z;
                    interpolated_u = interpolated_u;
                    interpolated_v = 1.0F-interpolated_v;
                    auto z_buffer_index = width*y+x;



                    if(interpolated_z >= z_buffer[z_buffer_index])
                    {
                        z_buffer[z_buffer_index] = interpolated_z;
                        TGAColor tex = texture.get(interpolated_u*1024, interpolated_v*1024);
                        tex.r*=brightness;
                        tex.g*=brightness;
                        tex.b*=brightness;
                        interpolated_z+=1.0F;
                        TGAColor c(255 * interpolated_z, 255 * interpolated_z, 255 * interpolated_z, 255);

                         image.set(x, y, tex);
                    }
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    const int width = 1000;
    const int height = 1000;
    TGAImage image(width, height, TGAImage::RGB);
    TGAImage texture(1024, 1024, 24);
    texture.read_tga_file("data/textures/african_head_diffuse.tga");
   // texture.flip_vertically();

    wfol::Model african_head("data/models/african_head.obj");

    auto triangles = african_head.getFaceTriangles();
    std::vector<float> z_buffer(width*height);
    for(auto& f : z_buffer)
    {
        f = -10000000000000.0;
    }
    for(auto& triangle : triangles)
    {
        draw_triangle(triangle, image, z_buffer, texture);
    }

    image.flip_vertically();
    image.write_tga_file("output.tga");
    return 0;
}