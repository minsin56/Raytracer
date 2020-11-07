#define NOMINMAX

#include "RayTracer.h"
#include<iostream>
#include<math.h>
float Time = 0;

RayTracer::RayTracer(SDL_Surface *Surface)
{
    this->Surface = Surface;
    Objects = std::vector<RaytraceObject*>();
    Sphere* Sphere1 = new Sphere(glm::vec3(800 * 0.5f, 800 * 0.5f,40),100);
    Sphere1->FMat.Color = glm::vec3 (124, 230, 100);
    Sphere1->FMat.IsReflective = true;
    Objects.push_back(Sphere1);
    Objects.push_back(new Sphere(glm::vec3(800 * 0.5f + 300, 600 * 0.5f,10),50));
}
void RayTracer::Update()
{
    Time += 0.01f;
    Utils::ClearPixel(Surface);
    Ray FRay = Ray(glm::vec3(0,0,0),glm::vec3());
    float Distance = 0;
    double t;
    Time += 0.001f;
    Ray Ray(glm::vec3(0,0, 0),glm::vec3(0,0,20));
    float Depth = 0;

    for(int y = 0;y < RenderHeight; y++)
    {
        for(int x = 0;x < RenderWidth; x++)
        {
            Ray.Origin = glm::vec3(x,y,0);
            glm::vec3 ColorToSet = CastRay(Ray,Objects);
            
            Utils::SetPixel(Surface,x,y,ColorToSet.x,ColorToSet.y,ColorToSet.z);
        }

    }
}

bool RayTracer::Trace(Ray Ray, std::vector<RaytraceObject *> &Objects, double &TNear, RaytraceObject *& HitObject)
{
    TNear = INFINITY;
    for(int i = 0;i<Objects.size();i++)
    {
        double t = INFINITY;
        if (Objects[i]->Intersects(Ray,t) && t < TNear)
        {
            HitObject = Objects[i];
            TNear = t;
        }
    }
    
    if(!HitObject) return false;
    
    
    return true;
}

glm::vec3 RayTracer::CastRay(Ray Ray, std::vector<RaytraceObject*> Objects)
{
    glm::vec3 HitColor = glm::vec3(135,206,250);
    RaytraceObject* Object = nullptr;
    double t;
    if (Trace(Ray,Objects,t,Object))
    {
        glm::vec3 PHit = Ray.Origin + Ray.Direction * glm::vec3 (t,t,t);
        glm::vec3 NHit = Object->GetNormal(PHit);
        double c = std::max(0.0f, glm::dot(NHit,Ray.Direction)) * 0.5f;
        HitColor = glm::vec3(Object->FMat.Color.x * c,Object->FMat.Color.y * c,Object->FMat.Color.z * c);

    }
    
    return HitColor;
    
}
