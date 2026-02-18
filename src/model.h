#pragma once

#include <string>
#include <vector>

#include "glad/glad.h"
#include "vertex.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "material.h"
#include "mesh.h"

// make dis hold array of mesh which has vao and vbo and ibo and upload but then make a new thing that makes it draw but then replace batcher with like render_queue or something that draws the stuffs from the other new thing

class Model {
private:
    std::vector<Mesh> m_Meshes;

public:
    Model(const std::string& filepath);

    std::vector<Mesh> LoadModel(const std::string& filepath);

    inline const std::vector<Mesh>& GetMeshes() const { return m_Meshes; }
};
