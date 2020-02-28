#include "drawableObject.h"

DrawableObject::DrawableObject()
{
    center = {0,0,0};
    color = {1,1,1,1};
    isHighlighted = false;
    highlightedColor = {1,0,0,1};
}

DrawableObject::DrawableObject(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor)
{
    center = inputCenter;
    color = inputColor;
    isHighlighted = false;
    highlightedColor = inputHighlightedColor;
}

point DrawableObject::getCenter()
{
    return center;
}
RGBAcolor DrawableObject::getColor()
{
    return color;
}
bool DrawableObject::getIsHighlighted()
{
    return isHighlighted;
}
RGBAcolor DrawableObject::getHighlightedColor()
{
    return highlightedColor;
}

void DrawableObject::setCenter(point inputCenter)
{
    center = inputCenter;
}
void DrawableObject::setColor(RGBAcolor inputColor)
{
    color = inputColor;
}
void DrawableObject::setIsHighlighted(bool inputIsHighlighted)
{
    isHighlighted = inputIsHighlighted;
}
void DrawableObject::setHighlightedColor(RGBAcolor inputHighlightedColor)
{
    highlightedColor = inputHighlightedColor;
}

void DrawableObject::move(double deltaX, double deltaY, double deltaZ)
{
    center.x += deltaX;
    center.y += deltaY;
    center.z += deltaZ;
}

void rotatePointAroundPoint(point &p, const point &pBase, double thetaX, double thetaY, double thetaZ)
{
    // Store the previous coordinates during calculations
    double prevX = 0, prevY = 0, prevZ = 0;

    // Translate pBase to the origin by moving p
    p.x -= pBase.x;
    p.y -= pBase.y;
    p.z -= pBase.z;

    // Rotate around x-axis
    prevY = p.y;
    prevZ = p.z;
    p.y = prevY * cos(thetaX) - prevZ * sin(thetaX);
    p.z = prevY * sin(thetaX) + prevZ * cos(thetaX);

    // Rotate around y-axis
    prevX = p.x;
    prevZ = p.z;
    p.x = prevX * cos(thetaY) - prevZ * sin(thetaY);
    p.z = prevX * sin(thetaY) + prevZ * cos(thetaY);

    // Rotate around z-axis
    prevX = p.x;
    prevY = p.y;
    p.x = prevX * cos(thetaZ) - prevY * sin(thetaZ);
    p.y = prevX * sin(thetaZ) + prevY * cos(thetaZ);

    // Translate back
    p.x += pBase.x;
    p.y += pBase.y;
    p.z += pBase.z;
}