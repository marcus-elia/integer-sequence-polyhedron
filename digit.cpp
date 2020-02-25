#include "digit.h"

std::vector<std::vector<int>>Digit::segmentsVector{{1,2,3,4,5,6},{2,3},{1,2,7,5,4},
                                                   {1,2,7,3,4},{6,7,2,3},{1,6,7,3,4},
                                                   {1,4,3,5,6,7},{1,2,3},{1,2,3,4,5,6,7},
                                                   {1,2,3,4,6,7}};

Digit::Digit() : DrawableObject()
{
    digit = 0;
    width = 10;
    height = 20;
    thickness = 4;
}

Digit::Digit(point inputCenter, RGBAcolor inputColor, int inputDigit, int inputWidth, int inputHeight) :
             DrawableObject(inputCenter, inputColor)
{
    digit = inputDigit;
    width = inputWidth;
    height = inputHeight;
    thickness = 4;
}

Digit::Digit(const Digit &oldDigit)
{
    digit = oldDigit.digit;
    width = oldDigit.width;
    height = oldDigit.height;
    thickness = oldDigit.thickness;
}

Digit::~Digit()
{
    //delete segments;
    //segments = nullptr;
}


void Digit::draw() const
{
    glColor4f(color.r, color.g, color.b, color.a);
    for(int i : segmentsVector[digit])
    {
        glBegin(GL_TRIANGLE_STRIP);
        switch(i)
        {
            case 1:
                glVertex3f(center.x - width/2 + thickness/2, center.y + height/2 - thickness/2, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y + height/2 - thickness, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y + height/2, center.z);
                glVertex3f(center.x + width/2-thickness, center.y + height/2, center.z);
                glVertex3f(center.x + width/2-thickness, center.y + height/2 - thickness, center.z);
                glVertex3f(center.x + width/2 - thickness/2, center.y + height/2 - thickness/2, center.z);
                break;
            case 2:
                glVertex3f(center.x + width/2 - thickness/2, center.y + height/2 - thickness/2, center.z);
                glVertex3f(center.x + width/2 - thickness, center.y + height/2 - thickness, center.z);
                glVertex3f(center.x + width/2, center.y + height/2 - thickness, center.z);
                glVertex3f(center.x + width/2 - thickness, center.y + thickness/2, center.z);
                glVertex3f(center.x + width/2, center.y + thickness/2, center.z);
                glVertex3f(center.x + width/2 - thickness/2, center.y, center.z);
                break;
            case 3:
                glVertex3f(center.x + width/2 - thickness/2, center.y, center.z);
                glVertex3f(center.x + width/2 - thickness, center.y - thickness/2, center.z);
                glVertex3f(center.x + width/2, center.y - thickness/2, center.z);
                glVertex3f(center.x + width/2 - thickness, center.y - height/2 + thickness, center.z);
                glVertex3f(center.x + width/2, center.y - height/2 + thickness, center.z);
                glVertex3f(center.x + width/2 - thickness/2, center.y - height/2 + thickness/2, center.z);
                break;
            case 4:
                glVertex3f(center.x - width/2 + thickness/2, center.y - height/2 + thickness/2, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y - height/2, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y - height/2 + thickness, center.z);
                glVertex3f(center.x + width/2-thickness, center.y - height/2, center.z);
                glVertex3f(center.x + width/2-thickness, center.y - height/2 + thickness, center.z);
                glVertex3f(center.x + width/2 - thickness/2, center.y - height/2 + thickness/2, center.z);
                break;
            case 5:
                glVertex3f(center.x - width/2 + thickness/2, center.y, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y - thickness/2, center.z);
                glVertex3f(center.x - width/2, center.y - thickness/2, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y - height/2 + thickness, center.z);
                glVertex3f(center.x - width/2, center.y - height/2 + thickness, center.z);
                glVertex3f(center.x - width/2 + thickness/2, center.y - height/2 + thickness/2, center.z);
                break;
            case 6:
                glVertex3f(center.x - width/2 + thickness/2, center.y + height/2 - thickness/2, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y + height/2 - thickness, center.z);
                glVertex3f(center.x - width/2, center.y + height/2 - thickness, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y + thickness/2, center.z);
                glVertex3f(center.x - width/2, center.y + thickness/2, center.z);
                glVertex3f(center.x - width/2 + thickness/2, center.y, center.z);
                break;
            case 7:
                glVertex3f(center.x - width/2 + thickness/2, center.y, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y - thickness/2, center.z);
                glVertex3f(center.x - width/2 + thickness, center.y + thickness/2, center.z);
                glVertex3f(center.x + width/2-thickness, center.y + thickness/2, center.z);
                glVertex3f(center.x + width/2-thickness, center.y - thickness/2, center.z);
                glVertex3f(center.x + width/2 - thickness/2, center.y, center.z);
                break;
            default:
                break;
        }
        glEnd();
    }
}




void Digit::move(double delta_x, double delta_y, double delta_z)
{

}