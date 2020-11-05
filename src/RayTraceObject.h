#include "glm/glm.hpp"
#include "Math/Ray.h"


class RaytraceObject
{
public:
    glm::vec3  Position;
    virtual bool Intersects(Ray Ray,double &t){return true;}
    virtual glm::vec3  GetNormal(glm::vec3& Pi){return glm::vec3(0,0,0);}
};        