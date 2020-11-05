#include "SDL2/SDL.h"
#include "Utils.h"
#include "Math/Ray.h"
#include "RayTraceObject.h"
#include<vector>
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

struct Box: public RaytraceObject
{
public:
    glm::vec3 Min,Max;
    
    Box(glm::vec3 Min,glm::vec3 Max)
    {
        this->Min = Min;
        this->Max = Max;
    }
    
    bool Intersects(Ray Ray, double &t) override
    {
        float TMin = (Min.x - Ray.Origin.x) / Ray.Direction.x;
        float TMax = (Max.x - Ray.Origin.x) / Ray.Direction.x;
        
        if (TMin > TMax) std::swap(TMin,TMax);
        
        float TYMin = (Min.y - Ray.Origin.y) / Ray.Direction.y;
        float TYMax = (Max.y - Ray.Origin.y) / Ray.Direction.y;
        
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
        }
        
        return true;
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

