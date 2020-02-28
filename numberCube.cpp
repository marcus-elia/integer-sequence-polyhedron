#include "numberCube.h"

#include <utility>

NumberCube::NumberCube() : CubeContainer()
{
    cube = Cube();
    number = DigitalNumber();
}
NumberCube::NumberCube(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor,
                       point &inputOwnerCenter, RGBAcolor inputEdgeColor,
                       unsigned int inputEdgeLength, RGBAcolor inputNumberColor,
                       RGBAcolor inputHighlightedNumberColor, int inputNumber) :
            CubeContainer(inputEdgeLength,inputEdgeColor, inputNumberColor, inputHighlightedNumberColor)
{
    cube = Cube(inputCenter, inputColor, inputHighlightedColor, inputOwnerCenter,
            inputEdgeColor, inputEdgeLength);
    number = DigitalNumber(inputCenter, inputNumberColor, inputOwnerCenter, inputNumber, inputEdgeLength, inputEdgeLength);
}



void NumberCube::draw() const
{
    glDisable(GL_CULL_FACE);
    number.draw();
    glEnable(GL_CULL_FACE);
    cube.draw();
}

void NumberCube::drawNumber() const
{
    number.draw();
}

void NumberCube::move(double deltaX, double deltaY, double deltaZ)
{
    number.move(deltaX, deltaY, deltaZ);
    cube.move(deltaX, deltaY, deltaZ);
}

void NumberCube::rotateAroundOwner(double thetaX, double thetaY, double thetaZ)
{
    // Store the previous coordinates, so we know how much to move the number
    double prevX = cube.getCenter().x;
    double prevY = cube.getCenter().y;
    double prevZ = cube.getCenter().z;

    // Rotates and revolves around the owner
   cube.rotateAroundOwner(thetaX, thetaY, thetaZ);

    // Move the number
    number.move(cube.getCenter().x - prevX, cube.getCenter().y - prevY, cube.getCenter().z - prevZ);

}