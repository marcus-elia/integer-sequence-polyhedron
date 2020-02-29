#include "text3d.h"
#include "graphics.h"

Text3D::Text3D() : DrawableObject()
{
    text = "???";
    fontSize = 12;
}
Text3D::Text3D(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor, std::string inputText,int inputFontSize) :
               DrawableObject(inputCenter, inputColor, inputHighlightedColor)
{
    text = inputText;
    fontSize = inputFontSize;
}

void Text3D::draw() const
{
    glColor3f(color.r, color.g, color.b);
    glRasterPos3i(center.x - (4 * text.length()), center.y + 7, center.z);
    for (const char &letter : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

void Text3D::move(double delta_x, double delta_y, double delta_z)
{
    center.x += delta_x;
    center.y += delta_y;
    center.z += delta_z;
}