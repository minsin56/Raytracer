#include "RayTraceObject.h"

#ifndef VOXEL_BOX_H
#define VOXEL_BOX_H


class Box: public RaytraceObject
{
public:
    glm::vec3 Min,Max;
    Box(glm::vec3 Min,glm::vec3 Max)
    {
        this->Min = Min;
        this->Max = Max;
    }
    bool Intersects(Ray Ray, double &t) override;
    glm::vec3 GetNormal(glm::vec3 &Pi) override;
};


#endif //VOXEL_BOX_H
