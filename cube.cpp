// The code in this file is based on code provided by Lisa Dion
// in a 3D graphics tutorial.

#include "cube.h"
#include "graphics.h"

void Cube::resetCorners()
{
    corners.clear();
    corners.resize(8);
    corners[0] = {center.x + (edgeLength / 2.0), center.y + (edgeLength / 2.0), center.z + (edgeLength / 2.0)};
    corners[1] = {center.x - (edgeLength / 2.0), center.y + (edgeLength / 2.0), center.z + (edgeLength / 2.0)};
    corners[2] = {center.x + (edgeLength / 2.0), center.y - (edgeLength / 2.0), center.z + (edgeLength / 2.0)};
    corners[3] = {center.x - (edgeLength / 2.0), center.y - (edgeLength / 2.0), center.z + (edgeLength / 2.0)};
    corners[4] = {center.x + (edgeLength / 2.0), center.y + (edgeLength / 2.0), center.z - (edgeLength / 2.0)};
    corners[5] = {center.x - (edgeLength / 2.0), center.y + (edgeLength / 2.0), center.z - (edgeLength / 2.0)};
    corners[6] = {center.x + (edgeLength / 2.0), center.y - (edgeLength / 2.0), center.z - (edgeLength / 2.0)};
    corners[7] = {center.x - (edgeLength / 2.0), center.y - (edgeLength / 2.0), center.z - (edgeLength / 2.0)};
}

void Cube::drawPoint(const point &p) const
{
    glVertex3f(p.x, p.y, p.z);
}

Cube::Cube() : DrawableComponent()
{
    edgeColor = {1,1,1,1};
    edgeLength = 50;
    resetCorners();
}

Cube::Cube(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor, point &inputOwnerCenter,
        RGBAcolor inputEdgeColor, unsigned int inputEdgeLength) :
        DrawableComponent(inputCenter, inputColor, inputHighlightedColor, inputOwnerCenter)
{
    edgeLength = inputEdgeLength;
    edgeColor = inputEdgeColor;
    resetCorners();
}

point Cube::getMin() const
{
    return {center.x - edgeLength, center.y - edgeLength, center.z - edgeLength};
}
point Cube::getMax() const
{
    return {center.x + edgeLength, center.y + edgeLength, center.z + edgeLength};
}

void Cube::draw() const
{
    drawLines();
    drawFaces();
}

void Cube::drawLines() const
{
    glColor4f(edgeColor.r, edgeColor.g, edgeColor.b, edgeColor.a);
    glBegin(GL_LINES);
    drawPoint(corners[1]);
    drawPoint(corners[0]);

    drawPoint(corners[1]);
    drawPoint(corners[3]);

    drawPoint(corners[3]);
    drawPoint(corners[2]);

    drawPoint(corners[2]);
    drawPoint(corners[0]);

    drawPoint(corners[4]);
    drawPoint(corners[5]);

    drawPoint(corners[5]);
    drawPoint(corners[7]);

    drawPoint(corners[7]);
    drawPoint(corners[6]);

    drawPoint(corners[6]);
    drawPoint(corners[4]);

    drawPoint(corners[0]);
    drawPoint(corners[4]);

    drawPoint(corners[2]);
    drawPoint(corners[6]);

    drawPoint(corners[3]);
    drawPoint(corners[7]);

    drawPoint(corners[1]);
    drawPoint(corners[5]);

    glEnd();
}

void Cube::drawFaces() const
{
    glBegin(GL_QUADS);
    if(!isHighlighted)
    {
        glColor4f(color.r, color.g, color.b, color.a);
    }
    else
    {
        glColor4f(highlightedColor.r, highlightedColor.g, highlightedColor.b, highlightedColor.a);
    }

    drawPoint(corners[0]);
    drawPoint(corners[1]);
    drawPoint(corners[3]);
    drawPoint(corners[2]);

    drawPoint(corners[5]);
    drawPoint(corners[4]);
    drawPoint(corners[6]);
    drawPoint(corners[7]);

    drawPoint(corners[6]);
    drawPoint(corners[4]);
    drawPoint(corners[0]);
    drawPoint(corners[2]);

    drawPoint(corners[4]);
    drawPoint(corners[5]);
    drawPoint(corners[1]);
    drawPoint(corners[0]);

    drawPoint(corners[6]);
    drawPoint(corners[2]);
    drawPoint(corners[3]);
    drawPoint(corners[7]);

    drawPoint(corners[3]);
    drawPoint(corners[1]);
    drawPoint(corners[5]);
    drawPoint(corners[7]);
    glEnd();


}

void Cube::rotate(double thetaX, double thetaY, double thetaZ)
{
    for (point &p : corners)
    {
        rotatePointAroundPoint(p, center, thetaX, thetaY, thetaZ);
    }
}

void Cube::move(double deltaX, double deltaY, double deltaZ)
{
    center.x += deltaX;
    center.y += deltaY;
    center.z += deltaZ;
    for (point &p : corners)
    {
        p.x += deltaX;
        p.y += deltaY;
        p.z += deltaZ;
    }
}

void Cube::rotateAroundOwner(double thetaX, double thetaY, double thetaZ)
{
    rotatePointAroundPoint(center, ownerCenter, thetaX, thetaY, thetaZ);

    for(point &p : corners)
    {
        rotatePointAroundPoint(p, ownerCenter, thetaX, thetaY, thetaZ);
    }
}