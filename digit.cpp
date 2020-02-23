#include "digit.h"


Digit::Digit() : DrawableObject()
{
    digit = 0;
    width = 10;
    height = 20;
}

Digit::Digit(point inputCenter, RGBAcolor inputColor, int inputDigit, int inputWidth, int inputHeight) :
             DrawableObject(inputCenter, inputColor)
{
    digit = inputDigit;
    width = inputWidth;
    height = inputHeight;
}

void Digit::draw() const
{
    glBegin(GL_QUADS);
    glColor4f(color.r, color.g, color.b, color.a);
}