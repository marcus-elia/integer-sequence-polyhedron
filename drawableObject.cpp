#include "drawableObject.h"

DrawableObject::DrawableObject()
{
    center = {0,0,0};
    color = {1,1,1,1};
}

DrawableObject::DrawableObject(point inputCenter, RGBAcolor inputColor)
{
    center = inputCenter;
    color = inputColor;
}