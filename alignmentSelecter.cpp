#include "alignmentSelecter.h"

AlignmentSelecter::AlignmentSelecter()
{
    x = 60;
    y = 60;
    width = 50;
    color = {0,0,1,1};
    selectedColor = {1,0,0,1};
    selected = Center;
}


void AlignmentSelecter::draw() const
{
    double curX, curY, curTheta;

    // Center circle
    if(selected == Center)
    {
        glColor4f(selectedColor.r, selectedColor.g, selectedColor.b, selectedColor.a);
    }
    else
    {
        glColor4f(color.r, color.g, color.b, color.a);
    }
    glBegin(GL_TRIANGLE_FAN);
    curTheta = 0;
    for(int i = 0; i < 30 + 2; i++)
    {
        curX = x + width/2*std::cos(curTheta);
        curY = y + width/2*std::sin(curTheta);
        curTheta += 2*3.14159/30;
        glVertex2f(curX, curY);
    }
    glEnd();
}
