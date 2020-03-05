#include "alignmentSelecter.h"

AlignmentSelecter::AlignmentSelecter()
{
    x = 96;
    y = 96;
    width = 96;
    color = {.6,0,.1,.9};
    selectedColor = {.8,.8,0.1,1};
    hoverColor = {.8,0,0,.4};
    selected = Center;
    hovered = std::experimental::nullopt;
    numPoints = 32;
}

std::experimental::optional<TableAlignment> AlignmentSelecter::getAlignmentFromPosition(int mx, int my)
{
    // If the position is completely outside the square of the selecter
    if(mx > x + width/2 || mx < x - width/2 || my > y + width/2 || my < y - width/2)
    {
        return std::experimental::nullopt;
    }
    // If it's in the center circle
    else if(distance(x, y, mx, my) <= width/4)
    {
        return Center;
    }

    // If it's in a corner
    else if(distance(x, y, mx, my) >= width/3)
    {
        double theta = angleToPoint(x, y, mx, my);
        if(theta < -PI/2)
        {
            return BottomLeft;
        }
        else if(theta < 0)
        {
            return BottomRight;
        }
        else if(theta < PI/2)
        {
            return TopRight;
        }
        else
        {
            return TopLeft;
        }
    }
    return std::experimental::nullopt;
}

std::experimental::optional<TableAlignment> AlignmentSelecter::reactToMouseMovement(int mx, int my)
{
    hovered = getAlignmentFromPosition(mx, my);
    return hovered;
}

std::experimental::optional<TableAlignment> AlignmentSelecter::reactToClick(int mx, int my)
{
    std::experimental::optional<TableAlignment> clicked = getAlignmentFromPosition(mx, my);
    if(clicked)
    {
        selected = clicked.value();
    }
    return clicked;
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
    else if(hovered.value_or(NullAlignment) == Center)
    {
        glColor4f(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
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
    else if(hovered.value_or(NullAlignment) == BottomLeft)
    {
        glColor4f(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
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
    else if(hovered.value_or(NullAlignment) == BottomRight)
    {
        glColor4f(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
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
    else if(hovered.value_or(NullAlignment) == TopRight)
    {
        glColor4f(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
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
    else if(hovered.value_or(NullAlignment) == TopLeft)
    {
        glColor4f(hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
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

// Euclidean distance
double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

double angleToPoint(double x1, double y1, double x2, double y2)
{
    return atan2(y2 - y1, x2 - x1);
}
