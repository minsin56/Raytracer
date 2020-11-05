//
// Created by vincent on 11/4/2020.
//

#include "Box.h"

bool Box::Intersects(Ray Ray, double &t)
{
    float TMin = (Min.x - Ray.Origin.x) / Ray.Direction.x;
    float TMax = (Max.x - Ray.Origin.x) / Ray.Direction.x;

    if (TMin > TMax) std::swap(TMin,TMax);

    float TYMin = (Min.y - Ray.Origin.y) / Ray.Direction.y;
    float TYMax = (Max.y - Ray.Origin.y) / Ray.Direction.y;
    
    if (TYMin > TYMax) std::swap(TYMin,TYMax);

    if((TMin > TYMax) || (TYMin > TMax))
    {
        return false;
    }

    if (TMax > TYMax)
    {
        TMax = TYMax;
    }

    float TZMin = (Min.z - Ray.Origin.z) / Ray.Direction.z;
    float TZMax = (Max.z - Ray.Origin.z) / Ray.Direction.z;

    if (TZMin > TZMax) std::swap(TZMin,TZMax);

    if ((TMin > TZMax) || (TZMin > TMax))
    {
        return false;
    }

    if(TZMax < TMax)
    {
        TMax = TZMax;
        return true;
    }

    return true;
}

glm::vec3 Box::GetNormal(glm::vec3 &Pi)
{
    if (Pi.x < 0)
    {
        return glm::vec3(-1,0,0);
    }
    else if (Pi.x > 0)
    {
        return glm::vec3 (1,0,0);
    }
    
    return glm::vec3 (0,0,-1);
}