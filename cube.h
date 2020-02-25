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
    void rotate(double theta_x, double theta_y, double theta_z);

    void move(double delta_x, double delta_y, double delta_z);
};


#endif //INC_3D_GRAPHICS_CUBE_H
