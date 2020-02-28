#include "numberCube.h"

#include <utility>

NumberCube::NumberCube() : CubeContainer(), Cube()
{
    number = DigitalNumber();
}
NumberCube::NumberCube(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor,
                       point &inputOwnerCenter, RGBAcolor inputEdgeColor,
                       unsigned int inputEdgeLength, RGBAcolor inputNumberColor,
                       RGBAcolor inputHighlightedNumberColor, int inputNumber) :
            CubeContainer(inputEdgeLength,inputEdgeColor, inputNumberColor, inputHighlightedNumberColor),
            Cube(inputCenter, inputColor, inputHighlightedColor, inputOwnerCenter, inputEdgeColor, inputEdgeLength)
{
    number = DigitalNumber(inputCenter, inputNumberColor, inputHighlightedNumberColor,
            inputOwnerCenter, inputNumber, inputEdgeLength, inputEdgeLength);
}

void NumberCube::highlight()
{
    isHighlighted = true;
    number.setIsHighlighted(true);
}

void NumberCube::unHighlight()
{
    isHighlighted = false;
    number.setIsHighlighted(false);
}

void NumberCube::draw() const
{
    glDisable(GL_CULL_FACE);
    number.draw();
    glEnable(GL_CULL_FACE);
    Cube::draw();
}

void NumberCube::drawNumber() const
{
    number.draw();
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