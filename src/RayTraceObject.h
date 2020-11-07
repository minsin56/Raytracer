#include "glm/glm.hpp"
#include "Math/Ray.h"
#include "Material.h"

#ifndef VOXEL_RAYTRACEOBJECT_H
#define VOXEL_RAYTRACEOBJECT_H
class RaytraceObject
{
public:
    Material FMat = Material();
    glm::vec3 Center;
    virtual bool Intersects(Ray Ray,double& t){return true;}
    virtual glm::vec3  GetNormal(glm::vec3& Pi){return glm::vec3(0,0,0);}
};        

#endif