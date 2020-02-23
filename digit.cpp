#include "digit.h"

std::vector<int>Digit::segments0{1,2,3,4,5,6};
std::vector<int>Digit::segments1{2,3};
std::vector<int>Digit::segments2{1,2,7,5,4};
std::vector<int>Digit::segments3{1,2,7,3,4};
std::vector<int>Digit::segments4{6,7,2,3};
std::vector<int>Digit::segments5{1,6,7,3,4};
std::vector<int>Digit::segments6{1,3,4,5,6,7};
std::vector<int>Digit::segments7{1,2,3};
std::vector<int>Digit::segments8{1,2,3,4,5,6,7};
std::vector<int>Digit::segments9{1,2,3,4,6,7};

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