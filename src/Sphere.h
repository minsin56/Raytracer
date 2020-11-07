//
// Created by vincent on 11/5/2020.
//

#ifndef VOXEL_SPHERE_H
#define VOXEL_SPHERE_H
#include "RayTraceObject.h"

struct Sphere: public RaytraceObject
{
public:
    double Radius;
    Sphere(glm::vec3 C, double Radius)
    {
        this->Center = C;
        this->Radius = Radius;
    }
    virtual bool Intersects(Ray Ray,double& t) override;
    virtual glm::vec3  GetNormal(glm::vec3& Pi) override
    {
        return glm::normalize(Pi + Center);
    }
};


#endif //VOXEL_SPHERE_H
