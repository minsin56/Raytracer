#include<stdint.h>
#include<math.h>
#include "SDL2/SDL.h"
typedef unsigned int uint;
typedef unsigned char uchar;
#define null __null;
#define RenderWidth 800
#define RenderHeight 600

namespace Utils
{
    void SetPixel(SDL_Surface* Surface,int x,int y, Uint32 PixelR,Uint32 PixelG,Uint32 PixelB);

    void ClearPixel(SDL_Surface* Surface);
    bool SolveQuadratic(const double &a, const double &b, const double &c, double &x0, double &x1);
}