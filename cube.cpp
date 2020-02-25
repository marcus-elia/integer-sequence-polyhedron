// The code in this file is based on code provided by Lisa Dion
// in a 3D graphics tutorial.

#include <math.h>
#include "cube.h"
#include "graphics.h"

void Cube::resetCorners()
{
    corners.clear();
    corners.resize(8);
    corners[0] = {center.x + (edgeLength / 2.0), center.y + (edgeLength / 2.0), center.z + (edgeLength / 2.0)};
    corners[1] = {center.x - (edgeLength / 2.0), center.y + (edgeLength / 2.0), center.z + (edgeLength / 2.0)};
    corners[2] = {center.x + (edgeLength / 2.0), center.y - (edgeLength / 2.0), center.z + (edgeLength / 2.0)};
    corners[3] = {center.x - (edgeLength / 2.0), center.y - (edgeLength / 2.0), center.z + (edgeLength / 2.0)};
    corners[4] = {center.x + (edgeLength / 2.0), center.y + (edgeLength / 2.0), center.z - (edgeLength / 2.0)};
    corners[5] = {center.x - (edgeLength / 2.0), center.y + (edgeLength / 2.0), center.z - (edgeLength / 2.0)};
    corners[6] = {center.x + (edgeLength / 2.0), center.y - (edgeLength / 2.0), center.z - (edgeLength / 2.0)};
    corners[7] = {center.x - (edgeLength / 2.0), center.y - (edgeLength / 2.0), center.z - (edgeLength / 2.0)};
}

void Cube::drawPoint(const point &p) const
{
    glVertex3f(p.x, p.y, p.z);
}

Cube::Cube()
{
    center = {0, 0, 0};
    edgeLength = 50;
    resetCorners();
}

Cube::Cube(point inputCenter, RGBAcolor inputColor, unsigned int inputEdgeLength) : DrawableObject(inputCenter, inputColor)
{
    edgeLength = inputEdgeLength;
    resetCorners();
}

void Cube::draw() const
{
    glBegin(GL_QUADS);
    glColor4f(color.r, color.g, color.b, color.a);

    drawPoint(corners[0]);
    drawPoint(corners[1]);
    drawPoint(corners[3]);
    drawPoint(corners[2]);

    drawPoint(corners[5]);
    drawPoint(corners[4]);
    drawPoint(corners[6]);
    drawPoint(corners[7]);

    drawPoint(corners[6]);
    drawPoint(corners[4]);
    drawPoint(corners[0]);
    drawPoint(corners[2]);

    drawPoint(corners[4]);
    drawPoint(corners[5]);
    drawPoint(corners[1]);
    drawPoint(corners[0]);

    drawPoint(corners[6]);
    drawPoint(corners[2]);
    drawPoint(corners[3]);
    drawPoint(corners[7]);

    drawPoint(corners[3]);
    drawPoint(corners[1]);
    drawPoint(corners[5]);
    drawPoint(corners[7]);
    glEnd();

    glColor4f(.4, .6, 1, 1);
    glBegin(GL_LINES);
    drawPoint(corners[1]);
    drawPoint(corners[0]);

    drawPoint(corners[1]);
    drawPoint(corners[3]);

    drawPoint(corners[3]);
    drawPoint(corners[2]);

    drawPoint(corners[2]);
    drawPoint(corners[0]);

    drawPoint(corners[4]);
    drawPoint(corners[5]);

    drawPoint(corners[5]);
    drawPoint(corners[7]);

    drawPoint(corners[7]);
    drawPoint(corners[6]);

    drawPoint(corners[6]);
    drawPoint(corners[4]);

    drawPoint(corners[0]);
    drawPoint(corners[4]);

    drawPoint(corners[2]);
    drawPoint(corners[6]);

    drawPoint(corners[3]);
    drawPoint(corners[7]);

    drawPoint(corners[1]);
    drawPoint(corners[5]);
    
    glEnd();
}

void Cube::rotate(double theta_x, double theta_y, double theta_z)
{
    double old_x = 0, old_y = 0, old_z = 0;
    double center_x = center.x, center_y = center.y, center_z = center.z;

    // Translate to the origin
    move(-center_x, -center_y, -center_z);
    // Rotate x
    for (point &p : corners)
    {
        old_y = p.y;
        old_z = p.z;
        p.y = old_y * cos(theta_x) - old_z * sin(theta_x);
        p.z = old_y * sin(theta_x) + old_z * cos(theta_x);
    }
    // Rotate y
    for (point &p : corners)
    {
        old_x = p.x;
        old_z = p.z;
        p.x = old_x * cos(theta_y) - old_z * sin(theta_y);
        p.z = old_x * sin(theta_y) + old_z * cos(theta_y);
    }
    // Rotate z
    for (point &p : corners)
    {
        old_x = p.x;
        old_y = p.y;
        p.x = old_x * cos(theta_z) - old_y * sin(theta_z);
        p.y = old_x * sin(theta_z) + old_y * cos(theta_z);
    }
    // Translate back
    move(center_x, center_y, center_z);
}

void Cube::move(double delta_x, double delta_y, double delta_z)
{
    center.x += delta_x;
    for (point &p : corners)
    {
        p.x += delta_x;
    }
    center.y += delta_y;
    for (point &p : corners)
    {
        p.y += delta_y;
    }
    center.z += delta_z;
    for (point &p : corners)
    {
        p.z += delta_z;
    }
}