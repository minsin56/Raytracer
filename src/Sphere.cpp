//
// Created by vincent on 11/5/2020.
//

#include "Sphere.h"
#include "Utils.h"
bool Sphere::Intersects(Ray Ray,double& t)
{
    double t0,t1;
   
    glm::vec3  L = Center - Ray.Origin;
    float A = glm::dot(Ray.Direction,Ray.Direction);
    float B = 2 * glm::dot(Ray.Direction,L);
    float C = glm::dot(L,L) - (Radius * Radius);
    if (!Utils::SolveQuadratic(A,B,C,t0,t1))
    {
        return false;
    }
    
    if(t0 > t1) std::swap(t0,t1);
    
    if (t0 < 0)
    {
        t0 = t1;
        if (t0 < 0) return false;
    }
    
    t = t0;
    
    return true;
}