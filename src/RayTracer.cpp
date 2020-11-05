
#include "RayTracer.h"
float Time = 0;

RayTracer::RayTracer(SDL_Surface *Surface)
{
    this->Surface = Surface;
    Objects = std::vector<RaytraceObject>();
}

void RayTracer::Update()
{
    Sphere FSphere = Sphere(glm::vec3 (800 * 0.5f, 600 * 0.5f, 50), 100);
    Sphere FSphere2 = Sphere(glm::vec3 (800 * 0.5f + 100, 600 * 0.5f, 100), 50);
    Box FBox = Box(glm::vec3(200,-150,100),glm::vec3(50,50,50));
    Utils::ClearPixel(Surface);
    Ray FRay = Ray(glm::vec3(0,0,-60),glm::vec3());
    float Distance = 0;
    double t;
    Time += 0.001f;
    Ray Ray(glm::vec3(0,0, 0),glm::vec3(0,0,1));

    float Depth = 0;
    
    while(Depth < 2)
    {
        for(int y = 0;y < RenderHeight; y++)
        {
            for(int x = 0;x < RenderWidth; x++)
            {
                Ray.Origin = glm::vec3(x,y,0);
                TraceObject(FSphere, Ray, t, x, y);
                TraceObject(FSphere2, Ray, t, x, y);
                TraceObject(FBox, Ray, t, x, y);

                Depth += 0.01f;
            }
        }
    }
}

int RayTracer::TraceColor(RaytraceObject &Object, Ray FRay, double &t, int x, int y,RayTraceResult & OutResult)
{
    if (Object.Intersects(FRay, t))
    {
        glm::vec3  LOrigin = FRay.Origin;
        LOrigin.z = 0;
        glm::vec3 Pi = LOrigin + FRay.Direction * (float)t;
        const glm::vec3 L =  glm::vec3 (0,0,50) - Pi;
        const glm::vec3 N = Object.GetNormal(Pi);
        double DT = dot(glm::normalize(L),glm::normalize(N));
        if (DT < 0.2f) DT = 0.2;
        int Color = 255 * DT * 0.5;
        RayTraceResult Result;
        Result.Color = Color;
        Result.DidIntersect = true;
        OutResult = Result;
        return Color;
    }
    RayTraceResult Result;
    Result.Color = 0;
    Result.DidIntersect = false;
    OutResult = Result;
    
    return 0;
}

void RayTracer::TraceObject(RaytraceObject& Object, Ray FRay, double &t, int x, int y)
{
    RayTraceResult Result;
    TraceColor(Object,FRay,t,x,y, Result);
    
    if(Result.DidIntersect)
    {
        Utils::SetPixel(Surface,x,y,Result.Color,Result.Color,Result.Color);
    }

}

