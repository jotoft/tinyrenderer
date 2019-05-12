#pragma once
#include <string>
#include <vector>
#include <cstdint>

#include <geometry/geometry.h>

namespace wfol
{

    class Model
    {
    public:
        Model(const std::string& filename);
        ~Model();
    private:
        struct FaceVertex
        {
            int32_t vertex;
            int32_t tex;
            int32_t normal;
        };

        struct Face
        {
            FaceVertex v1, v2, v3;
        };
        std::vector<geometry::Point3D> m_vertices;
        std::vector<geometry::Point2D> m_texture_coords;
        std::vector<geometry::Vector3D> m_normal_vectors;
        std::vector<Face> m_faces;
    };
}