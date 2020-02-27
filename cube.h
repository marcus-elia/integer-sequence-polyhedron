// The code in this file is based on code provided by Lisa Dion
// in a 3D graphics tutorial.

#ifndef INC_3D_GRAPHICS_CUBE_H
#define INC_3D_GRAPHICS_CUBE_H

#include <vector>
#include "drawableComponent.h"

class Cube : public DrawableComponent
{
protected:
    unsigned int edgeLength;
    std::vector<point> corners;
    RGBAcolor edgeColor;
    void resetCorners();
    void drawPoint(const point &p) const;
public:
    Cube();
    Cube(point inputCenter, RGBAcolor inputColor, std::shared_ptr<point> inputOwnerCenter,
            RGBAcolor inputEdgeColor, unsigned int inputEdgeLength);

    void draw() const;
    void rotate(double thetaX, double thetaY, double thetaZ);

    void move(double deltaX, double deltaY, double deltaZ);
    void rotateAroundOwner(double thetaX, double thetaY, double thetaZ);
};


#endif //INC_3D_GRAPHICS_CUBE_H
