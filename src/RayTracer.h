#include "SDL2/SDL.h"
#include "Utils.h"
#include "Math/Ray.h"
#include "RayTraceObject.h"
#include<vector>
#include "Sphere.h"
#include "RayTraceResult.h"
class RayTracer
{
public:
    std::vector<RaytraceObject*> Objects;
    RayTracer(SDL_Surface* Surface);
    void Update();

private:
    float Time;
    SDL_Surface* Surface;
    bool Intersect(Ray Ray);
    bool Trace(Ray Ray, std::vector<RaytraceObject *> &Objects, double &TNear, RaytraceObject *& HitObject);
    glm::vec3 CastRay(Ray Ray, std::vector<RaytraceObject*> Objects);
};

