
#include "RayTracer.h"
#include<iostream>
float Time = 0;

RayTracer::RayTracer(SDL_Surface *Surface)
{
    this->Surface = Surface;
    Objects = std::vector<RaytraceObject*>();
    
    Objects.push_back(new Sphere(glm::vec3(800 * 0.5f, 800 * 0.5f,50),100));
    Objects.push_back(new Sphere(glm::vec3(800 * 0.5f + 200, 600 * 0.5f,100),50));
    Objects.push_back(new Box(glm::vec3(200,200,200),glm::vec3(250,250,250)));
}
void RayTracer::Update()
{
    Time += 0.01f;
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
                Ray.Origin = glm::vec3(x,y,-60);
                RaytraceObject* Object;
                if (Trace(Ray,Objects,t,Object))
                {
                    TraceObject(Object, Ray, t, x, y);
                }
                Depth += 0.01f;
            }
        }
    }
}


bool RayTracer::Trace(Ray Ray, std::vector<RaytraceObject*> &Objects, double &TNear, RaytraceObject *&HitObject)
{
    TNear = 9999999;
    for(RaytraceObject* Object: Objects)
    {
        double T = 0;
        if(Object->Intersects(Ray,T) && T < TNear)
        {
            HitObject = Object;
            TNear = T;
        }
    }
    
    return HitObject != nullptr;
}

int RayTracer::TraceColor(RaytraceObject* Object, Ray FRay, double &t, int x, int y,RayTraceResult & OutResult)
{
    if (Object->Intersects(FRay, t))
    {
        glm::vec3  LOrigin = FRay.Origin;
        LOrigin.z = 0;
        glm::vec3 Pi = LOrigin + FRay.Direction * (float)t;
        const glm::vec3 L =  (Object->Position + glm::vec3 (0,0,50)) - Pi;
        const glm::vec3 N = Object->GetNormal(Pi);
        double DT = dot(glm::normalize(L),glm::normalize(N));
        if (DT < 0.2f) DT = 0.2;
        int Color = 255 * DT;
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

void RayTracer::TraceObject(RaytraceObject* Object, Ray FRay, double &t, int x, int y)
{
    RayTraceResult Result;
    TraceColor(Object,FRay,t,x,y, Result);
    
    if(Result.DidIntersect)
    {
        Utils::SetPixel(Surface,x,y,Result.Color,Result.Color,Result.Color);
    }

}

