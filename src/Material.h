//
// Created by vincent on 11/5/2020.
//

#ifndef VOXEL_MATERIAL_H
#define VOXEL_MATERIAL_H
#include "glm/glm.hpp"
struct Material
{
public:
    glm::ivec3 Color;
    bool IsReflective;
};        

#endif //VOXEL_MATERIAL_H
