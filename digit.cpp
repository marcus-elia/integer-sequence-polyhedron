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
    thickness = 2.5;
    initializeSegments();
}

Digit::Digit(point inputCenter, RGBAcolor inputColor, int inputDigit, int inputWidth, int inputHeight) :
             DrawableObject(inputCenter, inputColor)
{
    digit = inputDigit;
    width = inputWidth;
    height = inputHeight;
    thickness = 2.5;
    initializeSegments();
}

void Digit::initializeSegments()
{
    switch(digit)
    {
        case 0 : segments = std::shared_ptr<std::vector<int>>(&segments0);
        break;
        case 1 : segments = std::shared_ptr<std::vector<int>>(&segments1);
            break;
        case 2 : segments = std::shared_ptr<std::vector<int>>(&segments2);
            break;
        case 3 : segments = std::shared_ptr<std::vector<int>>(&segments3);
            break;
        case 4 : segments = std::shared_ptr<std::vector<int>>(&segments4);
            break;
        case 5 : segments = std::shared_ptr<std::vector<int>>(&segments5);
            break;
        case 6 : segments = std::shared_ptr<std::vector<int>>(&segments6);
            break;
        case 7 : segments = std::shared_ptr<std::vector<int>>(&segments7);
            break;
        case 8 : segments = std::shared_ptr<std::vector<int>>(&segments8);
            break;
        case 9 : segments = std::shared_ptr<std::vector<int>>(&segments9);
            break;
    }
}

void Digit::draw() const
{
    glColor4f(color.r, color.g, color.b, color.a);
    for(int i : *segments)
    {
        glBegin(GL_TRIANGLE_STRIP);
        switch(i)
        {
            case 1 :
                glVertex3f(center.x - width/2 + thickness/2, center.y + height/2 - thickness/2, 0);
                glVertex3f(center.x - width/2 + thickness, center.y + height/2 - thickness, 0);
                glVertex3f(center.x - width/2 + thickness, center.y + height/2, 0);
                glVertex3f(center.x + width/2-thickness, center.y + height/2, 0);
                glVertex3f(center.x + width/2-thickness, center.y + height/2 - thickness, 0);
                glVertex3f(center.x + width/2 - thickness/2, center.y + height/2 - thickness/2, 0);
                break;
            case 2 :
                break;
            default:
                break;
        }
    }

}