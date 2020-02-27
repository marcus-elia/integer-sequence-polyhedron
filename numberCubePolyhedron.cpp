#include "numberCubePolyhedron.h"

#include <utility>

NumberCubePolyhedron::NumberCubePolyhedron() : DrawableObject()
{
    vectorOfVectorsOfNumbers = {{{1,2},{3,4}},{{5,6},{7,8}}};
    edgeLength = 50;
    edgeColor = {1,1,1,1};
    numberColor = {0.4, 0.6, 1, 1};
    initializeNumberCubeTables();
}
NumberCubePolyhedron::NumberCubePolyhedron(point inputCenter, RGBAcolor inputColor, RGBAcolor inputEdgeColor,
unsigned int inputEdgeLength, std::vector<std::vector<std::vector<int>>>  inputVectorOfVectorsOfNumbers,
RGBAcolor inputNumberColor) : DrawableObject(inputCenter, inputColor)
{
    vectorOfVectorsOfNumbers = std::move(inputVectorOfVectorsOfNumbers);
    edgeLength = inputEdgeLength;
    edgeColor = inputEdgeColor;
    numberColor = inputNumberColor;
    initializeNumberCubeTables();
}


void NumberCubePolyhedron::initializeNumberCubeTables()
{
    int length = vectorOfVectorsOfNumbers.size();
    double curCenterZ;
    if(length % 2 == 0)
    {
        curCenterZ = -(edgeLength/2.0) - (length/2.0 - 1)*edgeLength;
    }
    else
    {
        curCenterZ = - (length - 1)/2.0*edgeLength;
    }
    for(std::vector<std::vector<int>> v : vectorOfVectorsOfNumbers)
    {
        numberCubeTables.push_back(NumberCubeTable({center.x, center.y, curCenterZ},
                color, center, edgeColor, edgeLength, v, numberColor));
        curCenterZ += edgeLength;
    }
}

void NumberCubePolyhedron::draw() const
{
    for(NumberCubeTable nct : numberCubeTables)
    {
        nct.draw();
    }
}

void NumberCubePolyhedron::move(double deltaX, double deltaY, double deltaZ)
{
    DrawableObject::move(deltaX, deltaY, deltaZ);
    for(NumberCubeTable nct : numberCubeTables)
    {
        nct.move(deltaX, deltaY, deltaZ);
    }
}

void NumberCubePolyhedron::rotate(double thetaX, double thetaY, double thetaZ)
{
    for(NumberCubeTable nct : numberCubeTables)
    {
        nct.rotateAroundOwner(thetaX, thetaY, thetaZ);
    }
}