#pragma once
#include <string>
#include <vector>

#include <geometry/geometry.h>

namespace wfol
{

    struct Face
    {

    };

    class Model
    {
    public:
        Model(const std::string& filename);
        ~Model();
    private:
        std::vector<geometry::Point3D> m_vertices;
        std::vector<geometry::Point2D> m_texture_coords;
        std::vector<geometry::Vector3D> m_normal_vectors;
    };
}