// The code in this file is based on code provided by Lisa Dion
// in a 3D graphics tutorial.

#ifndef INC_3D_GRAPHICS_CUBE_H
#define INC_3D_GRAPHICS_CUBE_H

#include <vector>
#include "drawableObject.h"

class Cube : public DrawableObject
{
protected:
    unsigned int edgeLength;
    std::vector<point> corners;
    RGBAcolor edgeColor;
    void resetCorners();
    void drawPoint(const point &p) const;
public:
    Cube();
    Cube(point inputCenter, RGBAcolor inputColor, RGBAcolor inputEdgeColor, unsigned int inputEdgeLength);

    void draw() const;
    void rotate(double thetaX, double thetaY, double thetaZ);

    void move(double deltaX, double deltaY, double deltaZ);
};


#endif //INC_3D_GRAPHICS_CUBE_H
