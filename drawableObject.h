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
    point center;
    RGBAcolor color;
    bool isHighlighted;
    RGBAcolor highlightedColor;
public:
    // Constructors
    DrawableObject();
    DrawableObject(point inputCenter, RGBAcolor inputColor, RGBAcolor highlightedColor);

    // Getters
    point getCenter();
    RGBAcolor getColor();
    bool getIsHighlighted();
    RGBAcolor getHighlightedColor();
    // Setters
    void setCenter(point inputCenter);
    void setIsHighlighted(bool inputHighlighted);
    void setColor(RGBAcolor inputColor);
    void setHighlightedColor(RGBAcolor inputHighlightedColor);

    virtual void draw() const = 0;
    virtual void move(double deltaX, double deltaY, double deltaZ);
    virtual void rotate(double thetaX, double thetaY, double thetaZ) = 0;


};

// Rotates p around pBase in 3D space
void rotatePointAroundPoint(point &p, const point &pBase, double thetaX, double thetaY, double thetaZ);


#endif //INC_3D_GRAPHICS_DRAWABLEOBJECT_H
