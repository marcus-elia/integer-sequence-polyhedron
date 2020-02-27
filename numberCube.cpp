#include "numberCube.h"

#include <utility>

NumberCube::NumberCube() : Cube()
{
    isHighlighted = false;
}
NumberCube::NumberCube(point inputCenter, RGBAcolor inputColor, point &inputOwnerCenter, RGBAcolor inputEdgeColor,
        unsigned int inputEdgeLength, int inputNumber, RGBAcolor inputNumberColor) :
            Cube(inputCenter, inputColor, inputOwnerCenter, inputEdgeColor, inputEdgeLength)
{
    number = DigitalNumber(inputCenter, inputNumberColor, inputOwnerCenter, inputNumber, inputEdgeLength, inputEdgeLength);
}

void NumberCube::draw() const
{
    /*point g = {ownerCenter.x, ownerCenter.y, ownerCenter.z};
    Cube c2 = Cube(g, {0,1,0,1}, g, {0,0,0,1}, 10);
    c2.draw();*/

    glDisable(GL_CULL_FACE);
    number.draw();
    glEnable(GL_CULL_FACE);
    Cube::draw();
}

void NumberCube::move(double deltaX, double deltaY, double deltaZ)
{
    number.move(deltaX, deltaY, deltaZ);
    Cube::move(deltaX, deltaY, deltaZ);
}

void NumberCube::rotateAroundOwner(double thetaX, double thetaY, double thetaZ)
{
    // Store the previous coordinates, so we know how much to move the number
    double prevX = center.x;
    double prevY = center.y;
    double prevZ = center.z;

    // Rotates and revolves around the owner
    Cube::rotateAroundOwner(thetaX, thetaY, thetaZ);

    // Move the number
    number.move(center.x - prevX, center.y - prevY, center.z - prevZ);

}