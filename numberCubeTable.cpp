#include "numberCubeTable.h"

#include <utility>

NumberCubeTable::NumberCubeTable() : DrawableComponent()
{
    vectorsOfNumbers = std::vector<std::vector<int>>{{1,341,5},{2000,2,99},{0,40,4040}};
    edgeLength = 50;
    edgeColor = {1,1,1,1};
    numberColor = {.4, .6, 1, 1};
    initializeNumberCubeRows();
}
NumberCubeTable::NumberCubeTable(point inputCenter, RGBAcolor inputColor, point &inputOwnerCenter, RGBAcolor inputEdgeColor,
unsigned int inputEdgeLength, std::vector<std::vector<int>> inputVectorsOfNumbers,
RGBAcolor inputNumberColor) : DrawableComponent(inputCenter, inputColor, inputOwnerCenter)
{
    vectorsOfNumbers = std::move(inputVectorsOfNumbers);
    edgeColor = inputEdgeColor;
    edgeLength = inputEdgeLength;
    numberColor = inputNumberColor;
    initializeNumberCubeRows();
}

void NumberCubeTable::initializeNumberCubeRows()
{
    int length = vectorsOfNumbers.size();
    double curCenterY;
    if(length % 2 == 0)
    {
        curCenterY = -(edgeLength/2.0) - (length/2.0 - 1)*edgeLength;
    }
    else
    {
        curCenterY = - (length - 1)/2.0*edgeLength;
    }
    for(std::vector<int> v : vectorsOfNumbers)
    {
        numberCubeRows.push_back(NumberCubeRow({center.x, curCenterY, center.z}, color, center,
                                                     edgeColor, edgeLength, v, numberColor));
        curCenterY += edgeLength;
    }
}

void NumberCubeTable::draw() const
{
    for(NumberCubeRow ncr : numberCubeRows)
    {
        ncr.draw();
    }
}

void NumberCubeTable::move(double deltaX, double deltaY, double deltaZ)
{
    DrawableObject::move(deltaX, deltaY, deltaZ);
    for(NumberCubeRow &ncr : numberCubeRows)
    {
        ncr.move(deltaX, deltaY, deltaZ);
    }
}

void NumberCubeTable::rotate(double thetaX, double thetaY, double thetaZ)
{
    for(NumberCubeRow &ncr : numberCubeRows)
    {
        ncr.rotateAroundOwner(thetaX, thetaY, thetaZ);
    }
}
void NumberCubeTable::rotateAroundOwner(double thetaX, double thetaY, double thetaZ)
{
    // Store the previous coordinates, so we know how much to move the number
    double prevX = center.x;
    double prevY = center.y;
    double prevZ = center.z;

    // Rotates and revolves around the owner
    rotatePointAroundPoint(center, ownerCenter, thetaX, thetaY, thetaZ);

    // Move the number cube rows
    for(NumberCubeRow &ncr : numberCubeRows)
    {
        ncr.setOwnerCenter(center);
        ncr.move(center.x - prevX, center.y - prevY, center.z - prevZ);
    }

    // Rotate the number cube rows
    for(NumberCubeRow &ncr : numberCubeRows)
    {
        ncr.rotateAroundOwner(thetaX, thetaY, thetaZ);
    }
}