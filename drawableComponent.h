#ifndef INTEGER_SEQUENCE_POLYHEDRON_DRAWABLECOMPONENT_H
#define INTEGER_SEQUENCE_POLYHEDRON_DRAWABLECOMPONENT_H

#include "drawableObject.h"

class DrawableComponent : public DrawableObject
{
protected:
    point ownerCenter;
public:
    DrawableComponent();
    DrawableComponent(point inputCenter, RGBAcolor inputColor, point inputOwnerCenter);

    virtual void rotateAroundOwner(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_DRAWABLECOMPONENT_H
