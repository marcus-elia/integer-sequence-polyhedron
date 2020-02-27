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
    double gapSize = 0.4 * edgeLength;                  // How far apart they are
    double curCenterZ;
    if(length % 2 == 0)
    {
        curCenterZ = -(edgeLength/2.0) - (length/2.0 - 1)*edgeLength - gapSize/2 - (length/2.0-1)*gapSize;
    }
    else
    {
        curCenterZ = - (length - 1)/2.0*edgeLength - (length-1)/2*gapSize;
    }
    for(std::vector<std::vector<int>> v : vectorOfVectorsOfNumbers)
    {
        numberCubeTables.push_back(NumberCubeTable({center.x, center.y, curCenterZ},
                color, center, edgeColor, edgeLength, v, numberColor));
        curCenterZ += edgeLength;
        curCenterZ += gapSize;
    }
}

void NumberCubePolyhedron::draw() const
{
    drawLines();
    glDisable(GL_CULL_FACE);
    drawNumbers();
    glEnable(GL_CULL_FACE);
    drawFaces();
}

void NumberCubePolyhedron::drawLines() const
{
    for(const NumberCubeTable &nct : numberCubeTables)
    {
        nct.drawLines();
    }
}

void NumberCubePolyhedron::drawFaces() const
{
    for(const NumberCubeTable &nct : numberCubeTables)
    {
        nct.drawFaces();
    }
}

void NumberCubePolyhedron::drawNumbers() const
{
    for(const NumberCubeTable &nct : numberCubeTables)
    {
        nct.drawNumbers();
    }
}

void NumberCubePolyhedron::move(double deltaX, double deltaY, double deltaZ)
{
    DrawableObject::move(deltaX, deltaY, deltaZ);
    for(NumberCubeTable &nct : numberCubeTables)
    {
        nct.move(deltaX, deltaY, deltaZ);
        nct.setOwnerCenter(center);
    }
}

void NumberCubePolyhedron::rotate(double thetaX, double thetaY, double thetaZ)
{
    for(NumberCubeTable &nct : numberCubeTables)
    {
        nct.rotateAroundOwner(thetaX, thetaY, thetaZ);
    }
}