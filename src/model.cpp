#include "model.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "batcher.h"

Model::Model(Batcher& batcher, const std::string& filepath) : m_Batcher(batcher), m_Meshes(LoadModel(filepath)) { }

std::vector<Mesh> Model::LoadModel(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        std::cerr << "Failed to open model: " << filepath << std::endl;
        return {};
    }

    std::vector<Mesh> meshes;

    struct MeshInfo { std::vector<Vertex> vertices; std::vector<unsigned int> indices; Material material };
    MeshInfo meshBuffer;

    std::vector<Material> materials;

    std::string line;
    std::string prefix;
    while (std::getline(in, line)) {
        std::istringstream iss(line);
        iss >> prefix;

        if (prefix == "v") {
            glm::vec3 pos, normal;
            glm::vec2 texCoord;
            iss >> pos.x >> pos.y >> pos.z >> normal.x >> normal.y >> normal.z >> texCoord.x >> texCoord.y;
            meshBuffer.vertices.push_back(Vertex{pos, normal, texCoord});
        } else if (prefix == "f") {
            unsigned int v0, v1, v2;
            iss >> v0 >> v1 >> v2;
            meshBuffer.indices.push_back(v0);
            meshBuffer.indices.push_back(v1);
            meshBuffer.indices.push_back(v2);
        } else if (prefix == "o") {
            unsigned int lastMaterial = meshBuffer.material;
            meshBuffer = MeshInfo{};
            meshBuffer.material = lastMaterial;
        } else if (prefix == "e") {
            meshes.push_back(Mesh(meshBuffer.vertices, meshBuffer.indices, meshBuffer.material));
        } else if (prefix == "m") {
            unsigned int id;
            iss >> id;
            meshBuffer.material = materials[id];
        } else if (prefix == "l") {
            std::string path;
            iss >> path;
            materials.push_back(Material(path));
        }
    }

    return meshes;
}
