#pragma once

#include <string>
#include <vector>

#include "glad/glad.h"
#include "vertex.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "material.h"
#include "mesh.h"

class Batcher;

class Model {
private:
    Batcher& m_Batcher;
    std::vector<Mesh> m_Meshes;

public:
    Model(Batcher& batcher, const std::string& filepath);

    std::vector<Mesh> LoadModel(const std::string& filepath);

    inline const std::vector<Mesh>& GetMeshes() const { return m_Meshes; }
};