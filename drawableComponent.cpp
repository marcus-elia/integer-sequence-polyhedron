#include "drawableComponent.h"

#include <utility>

DrawableComponent::DrawableComponent() : DrawableObject()
{
    ownerCenter = {0,0,0};
}
DrawableComponent::DrawableComponent(point inputCenter, RGBAcolor inputColor,
        RGBAcolor inputHighlightedColor, point &inputOwnerCenter) :
                   DrawableObject(inputCenter, inputColor, inputHighlightedColor)
{
    ownerCenter = inputOwnerCenter;
}

void DrawableComponent::setOwnerCenter(point inputOwnerCenter)
{
    ownerCenter = inputOwnerCenter;
}




void DrawableComponent::rotateAroundOwner(double thetaX, double thetaY, double thetaZ)
{
    rotatePointAroundPoint(center, ownerCenter, thetaX, thetaY, thetaZ);
    rotate(thetaX, thetaY, thetaZ);
}