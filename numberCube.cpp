#include "numberCube.h"

NumberCube::NumberCube() : Cube()
{
    isHighlighted = false;
}
NumberCube::NumberCube(point inputCenter, RGBAcolor inputColor, RGBAcolor inputEdgeColor,
        unsigned int inputEdgeLength, int inputNumber, RGBAcolor inputNumberColor) :
            Cube(inputCenter, inputColor, inputEdgeColor, inputEdgeLength)
{
    number = DigitalNumber(inputCenter, inputNumberColor, inputNumber, inputEdgeLength, inputEdgeLength);
}

void NumberCube::draw() const
{
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