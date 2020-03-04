#include "alignmentSelecter.h"

AlignmentSelecter::AlignmentSelecter()
{
    x = 108;
    y = 108;
    width = 96;
    color = {0,0,.8,.8};
    selectedColor = {0,1,0.3,.7};
    selected = Center;
    numPoints = 32;
}


void AlignmentSelecter::draw() const
{
    double curX, curY, curTheta;

    glDisable(GL_CULL_FACE);  // Don't hide faces, it's 2d

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
    glVertex3f(x, y,0.0f); // Circle center
    for(int i = 0; i < numPoints + 2; i++)
    {
        curX = x + width/4*std::cos(curTheta);
        curY = y + width/4*std::sin(curTheta);
        curTheta += 2*3.14159/numPoints;
        glVertex3f(curX, curY, 0.0f); // Point on perimeter
    }
    glEnd();

    // Bottom Left
    if(selected == BottomLeft)
    {
        glColor4f(selectedColor.r, selectedColor.g, selectedColor.b, selectedColor.a);
    }
    else
    {
        glColor4f(color.r, color.g, color.b, color.a);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x - width/2, y - width/2, 0.0f);  // Corner
    glVertex3f(x, y - width/2, 0.0f);
    curTheta = 3*3.14159265/2;
    for(int i = 0; i < numPoints/4 + 1; i++)
    {
        curX = x + width/3*std::cos(curTheta);
        curY = y + width/3*std::sin(curTheta);
        curTheta -= 2*3.14159/numPoints;
        glVertex3f(curX, curY, 0.0f);
    }
    glVertex3f(x - width/2, y, 0.0f);
    glEnd();

    // Bottom Right
    if(selected == BottomRight)
    {
        glColor4f(selectedColor.r, selectedColor.g, selectedColor.b, selectedColor.a);
    }
    else
    {
        glColor4f(color.r, color.g, color.b, color.a);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x + width/2, y - width/2, 0.0f);  // Corner
    glVertex3f(x, y - width/2, 0.0f);
    curTheta = 3*3.14159265/2;
    for(int i = 0; i < numPoints/4 + 1; i++)
    {
        curX = x + width/3*std::cos(curTheta);
        curY = y + width/3*std::sin(curTheta);
        curTheta += 2*3.14159/numPoints;
        glVertex3f(curX, curY, 0.0f);
    }
    glVertex3f(x + width/2, y, 0.0f);
    glEnd();

    // Top Right
    if(selected == TopRight)
    {
        glColor4f(selectedColor.r, selectedColor.g, selectedColor.b, selectedColor.a);
    }
    else
    {
        glColor4f(color.r, color.g, color.b, color.a);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x + width/2, y + width/2, 0.0f);  // Corner
    glVertex3f(x, y + width/2, 0.0f);
    curTheta = 3.14159265/2;
    for(int i = 0; i < numPoints/4 + 1; i++)
    {
        curX = x + width/3*std::cos(curTheta);
        curY = y + width/3*std::sin(curTheta);
        curTheta -= 2*3.14159/numPoints;
        glVertex3f(curX, curY, 0.0f);
    }
    glVertex3f(x + width/2, y, 0.0f);
    glEnd();

    // Top Left
    if(selected == TopLeft)
    {
        glColor4f(selectedColor.r, selectedColor.g, selectedColor.b, selectedColor.a);
    }
    else
    {
        glColor4f(color.r, color.g, color.b, color.a);
    }
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(x - width/2, y + width/2, 0.0f);  // Corner
    glVertex3f(x, y + width/2, 0.0f);
    curTheta = 3.14159265/2;
    for(int i = 0; i < numPoints/4 + 1; i++)
    {
        curX = x + width/3*std::cos(curTheta);
        curY = y + width/3*std::sin(curTheta);
        curTheta += 2*3.14159/numPoints;
        glVertex3f(curX, curY, 0.0f);
    }
    glVertex3f(x - width/2, y, 0.0f);
    glEnd();

}
