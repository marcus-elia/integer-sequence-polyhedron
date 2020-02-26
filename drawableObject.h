#ifndef INC_3D_GRAPHICS_DRAWABLEOBJECT_H
#define INC_3D_GRAPHICS_DRAWABLEOBJECT_H

#include "graphics.h"
#include <cmath>

struct RGBAcolor
{
    double r;
    double g;
    double b;
    double a;
};


struct point
{
    double x;
    double y;
    double z;
};

class DrawableObject
{
protected:
    RGBAcolor color;
    point center;
public:
    DrawableObject();
    DrawableObject(point inputCenter, RGBAcolor inputColor);
    virtual void draw() const = 0;
    virtual void move(double deltaX, double deltaY, double deltaZ) = 0;
    virtual void rotate(double thetaX, double thetaY, double thetaZ) = 0;


};

// Rotates p around pBase in 3D space
void rotatePointAroundPoint(point &p, const point &pBase, double thetaX, double thetaY, double thetaZ);


#endif //INC_3D_GRAPHICS_DRAWABLEOBJECT_H
