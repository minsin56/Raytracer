#define _RAY_H_
#pragma once

#include "glm/glm.hpp"

struct Ray
{
public:
    glm::vec3 Origin;
    glm::vec3 Direction;
    
    Ray(glm::vec3 Origin,glm::vec3 Direction)
    {
        this->Origin = Origin;
        this->Direction = Direction;
    }
};