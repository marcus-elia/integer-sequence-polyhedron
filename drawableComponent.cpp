#include "drawableComponent.h"

DrawableComponent::DrawableComponent() : DrawableObject()
{
    ownerCenter = {0,0,0};
}
DrawableComponent::DrawableComponent(point inputCenter, RGBAcolor inputColor, point inputOwnerCenter) :
                   DrawableObject(inputCenter, inputColor)
{
    ownerCenter = inputOwnerCenter;
}

void DrawableComponent::rotateAroundOwner(double thetaX, double thetaY, double thetaZ)
{
    rotatePointAroundPoint(center, ownerCenter, thetaX, thetaY, thetaZ);
    rotate(thetaX, thetaY, thetaZ);
}