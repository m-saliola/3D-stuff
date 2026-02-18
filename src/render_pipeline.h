#pragma once

#include <vector>

#include "instance.h"

class RenderPipeline {
private:
    std::vector<Instance> instances;

public:
    RenderPipeline(/* what go here */);

    void AddInstance(Instance instance);
    void AddInstances(const std::vector<Instance>& instances);
};
