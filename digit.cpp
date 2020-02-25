#include "digit.h"

/*std::vector<int>Digit::segments0{1,2,3,4,5,6};
std::vector<int>Digit::segments1{2,3};
std::vector<int>Digit::segments2{1,2,7,5,4};
std::vector<int>Digit::segments3{1,2,7,3,4};
std::vector<int>Digit::segments4{6,7,2,3};
std::vector<int>Digit::segments5{1,6,7,3,4};
std::vector<int>Digit::segments6{1,3,4,5,6,7};
std::vector<int>Digit::segments7{1,2,3};
std::vector<int>Digit::segments8{1,2,3,4,5,6,7};
std::vector<int>Digit::segments9{1,2,3,4,6,7};*/
std::vector<std::vector<int>>Digit::segmentsVector{{1,2,3,4,5,6},{2,3},{1,2,7,5,4},
                                                   {1,2,7,3,4},{6,7,2,3},{1,6,7,3,4},
                                                   {1,2,3,5,6,7},{1,2,3},{1,2,3,4,5,6,7},
                                                   {1,2,3,4,6,7}};

Digit::Digit() : DrawableObject()
{
    digit = 0;
    width = 10;
    height = 20;
    thickness = 4;
    //initializeSegments();
}

Digit::Digit(point inputCenter, RGBAcolor inputColor, int inputDigit, int inputWidth, int inputHeight) :
             DrawableObject(inputCenter, inputColor)
{
    digit = inputDigit;
    width = inputWidth;
    height = inputHeight;
    thickness = 4;
    //initializeSegments();
}

Digit::Digit(const Digit &oldDigit)
{
    digit = oldDigit.digit;
    width = oldDigit.width;
    height = oldDigit.height;
    thickness = oldDigit.thickness;
    //initializeSegments();
}

Digit::~Digit()
{
    //delete segments;
    //segments = nullptr;
}

/*void Digit::initializeSegments()
{
    switch(digit)
    {
        case 0 : segments = &segments0;
            break;
        case 1 : segments = &segments1;
            break;
        case 2 : segments = &segments2;
            break;
        case 3 : segments = &segments3;
            break;
        case 4 : segments = &segments4;
            break;
        case 5 : segments = &segments5;
            break;
        case 6 : segments = &segments6;
            break;
        case 7 : segments = &segments7;
            break;
        case 8 : segments = &segments8;
            break;
        case 9 : segments = &segments9;
            break;
    }
}*/

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