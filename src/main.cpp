#include <iostream>
#include "SDL2/SDL.h"
#include "Utils.h"

#define SDL_MAIN
#include "Math/Ray.h"
#include "RayTracer.h"

int WinMain()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL INIT FAILED" << std::endl;
    }
    SDL_Window* Window = SDL_CreateWindow("Voxel",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
    
    SDL_Event Event;
    bool Quit = false;
    SDL_Rect *SurfaceRect = new SDL_Rect();
    SurfaceRect->x = 0;
    SurfaceRect->y = 0;
    SurfaceRect->w = 800;
    SurfaceRect->h =600;
    SDL_Surface* Surface = SDL_CreateRGBSurface(0,RenderWidth,RenderHeight,32,0,0,0,0);
    
    RayTracer* Tracer = new RayTracer(Surface);
    while (!Quit)
    {
        if (SDL_PollEvent(&Event))
        {
            switch (Event.type)
            {
                case SDL_QUIT:
                    Quit = true;
                    break;
            }
        }
        Tracer->Update();
        SDL_BlitSurface(Surface,SurfaceRect,SDL_GetWindowSurface(Window),NULL);

        SDL_UpdateWindowSurface(Window);
    }
    
    return 0;
}