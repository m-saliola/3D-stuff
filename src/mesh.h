#pragma once

#include <vector>

#include "vertex.h"

class Material;

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int material;
};