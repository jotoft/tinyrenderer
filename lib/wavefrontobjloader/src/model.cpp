#include <wavefrontobjloader/model.h>
#include <fstream>
#include <iostream>
#include <cstdio>

using geometry::Point3D;
using geometry::Point2D;
using geometry::Vector3D;

wfol::Model::Model(const std::string& filename)
{
    std::ios::sync_with_stdio(false);
    std::ifstream s(filename);

    std::string token;
    while(!s.eof()) {
        s >> token;
        if (token == "v") {
            Point3D vertex;
            s >> vertex.x >> vertex.y >> vertex.z;
            m_vertices.push_back(vertex);
        }
        else if(token == "vt")
        {
            Point2D texture_coord;
            s >> texture_coord.x >> texture_coord.y;
            m_texture_coords.push_back(texture_coord);
        }
        else if (token == "vn")
        {
            Vector3D normal_vector;
            s >> normal_vector.x >> normal_vector.y >> normal_vector.z;
            m_normal_vectors.push_back(normal_vector);
        }


    }
    std::cout << m_vertices.size() << " vertices loaded\n";
    std::cout << m_texture_coords.size() << " texture coords loaded\n";
    std::cout << m_normal_vectors.size() << " normal vectors loaded\n";
}

wfol::Model::~Model() {

}
