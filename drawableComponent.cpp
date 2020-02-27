#include "drawableComponent.h"

#include <utility>

DrawableComponent::DrawableComponent() : DrawableObject()
{
    ownerCenter = {0,0,0};
}
DrawableComponent::DrawableComponent(point inputCenter, RGBAcolor inputColor, std::shared_ptr<point> inputOwnerCenter) :
                   DrawableObject(inputCenter, inputColor)
{
    ownerCenter = std::move(inputOwnerCenter);
}

void DrawableComponent::rotateAroundOwner(double thetaX, double thetaY, double thetaZ)
{
    rotatePointAroundPoint(center, *ownerCenter, thetaX, thetaY, thetaZ);
    rotate(thetaX, thetaY, thetaZ);
}