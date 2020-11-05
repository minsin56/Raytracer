#include "SDL2/SDL.h"
#include "Utils.h"
#include "Math/Ray.h"
#include "RayTraceObject.h"
#include<vector>
#include "Box.h"
#define MaxRef


struct RayTraceResult
{
public:
    int Color;
    bool DidIntersect;
    float HitDepth;
};
struct Sphere: public RaytraceObject
{
public:
    glm::vec3 C;
    double Radius;
    Sphere(glm::vec3 C, double Radius)
    {
        this->C = C;
        this->Radius = Radius;
    }
     bool Intersects(Ray Ray,double &t) override
    {
        const float r = Radius;
        const glm::vec3 o = Ray.Origin;
        const glm::vec3 d = Ray.Direction;
        const glm::vec3 oc = o - C;
        const double b = 2 * dot(oc, d);
        const double c = dot(oc, oc) - r*r;
        double disc = b*b - 4 * c;
        if (disc < 1e-4) return false;
        disc = sqrt(disc);
        const double t0 = -b - disc;
        const double t1 = -b + disc;

        t = (t0 < t1) ? t0 : t1;
        return true;
    }
    glm::vec3  GetNormal(glm::vec3& Pi) override
    {
        glm::vec3  XX = (Pi - C);
        return glm::vec3 (XX.x / Radius, XX.y / Radius, XX.z / Radius);
    }
};


class RayTracer
{
public:
    std::vector<RaytraceObject> Objects;
    RayTracer(SDL_Surface* Surface);
    void Update();

private:
    SDL_Surface* Surface;
    bool Intersect(Ray Ray);
    void TraceObject(RaytraceObject& Object, Ray FRay, double &t, int x, int y);
    int TraceColor(RaytraceObject& Object, Ray FRay, double &t, int x,int y,RayTraceResult & OutResult);
};

