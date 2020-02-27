#ifndef INTEGER_SEQUENCE_POLYHEDRON_DRAWABLECOMPONENT_H
#define INTEGER_SEQUENCE_POLYHEDRON_DRAWABLECOMPONENT_H

#include "drawableObject.h"
#include <memory>

class DrawableComponent : public DrawableObject
{
protected:
    std::shared_ptr<point> ownerCenter;
public:
    DrawableComponent();
    DrawableComponent(point inputCenter, RGBAcolor inputColor, std::shared_ptr<point> inputOwnerCenter);

    virtual void rotateAroundOwner(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_DRAWABLECOMPONENT_H
