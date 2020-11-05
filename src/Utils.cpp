#include "Utils.h"

void Utils::SetPixel(SDL_Surface *Surface, int x, int y,  Uint32 PixelR,Uint32 PixelG,Uint32 PixelB)
{
    uchar* Pixels = (uchar*)Surface->pixels;
    for (int c = 0; c < 4; c++)
    {
        int Color;
        if (c == 0)
        {
            Color = PixelB;
        }
        else if (c == 1)
        {
            Color = PixelG;
        }
        else if (c == 2)
        {
            Color = PixelR;
        }
        Pixels[4 * (y * Surface->w + x) + c] = Color;
    }
}

void Utils::ClearPixel(SDL_Surface *Surface)
{
    for(int x=  0;x<RenderWidth;x++)
    {
        for(int y = 0;y<RenderHeight;y++)
        {
            SetPixel(Surface,x,y,100,14,255);
        }
    }
}