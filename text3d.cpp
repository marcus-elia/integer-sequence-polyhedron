#include "text3d.h"
#include "graphics.h"

Text3D::Text3D()
{
    text = "???";
    center = {0,0,0};
    fontSize = 12;
}
Text3D::Text3D(std::string inputText, point inputCenter, int inputFontSize)
{
    text = inputText;
    center = inputCenter;
    fontSize = inputFontSize;
}

void Text3D::draw() const
{
    glColor3f(1, 1, 1);
    glRasterPos3i(center.x - (4 * text.length()), center.y + 7, center.z);
    for (const char &letter : text) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

void Text3D::move(double delta_x, double delta_y, double delta_z)
{

}