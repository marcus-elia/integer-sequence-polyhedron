#include "numberCubePolyhedron.h"

#include <utility>

NumberCubePolyhedron::NumberCubePolyhedron() : DrawableObject(), CubeContainer()
{
    vectorOfVectorsOfNumbers = {{{1,2},{3,4}},{{5,6},{7,8}}};
    highlightStatus = noneHighlighted;
    alignment = Center;
    angle = {0,0,0};
    initializeNumberCubeTables();
}
NumberCubePolyhedron::NumberCubePolyhedron(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor,
                                           unsigned int inputEdgeLength, RGBAcolor inputEdgeColor, RGBAcolor inputNumberColor,
                                           RGBAcolor inputHighlightedNumberColor,
                                           std::vector<std::vector<std::vector<int>>>  inputVectorOfVectorsOfNumbers) :
                                           DrawableObject(inputCenter, inputColor, inputHighlightedColor),
                                           CubeContainer(inputEdgeLength, inputEdgeColor, inputNumberColor,
                                                   inputHighlightedNumberColor)
{
    vectorOfVectorsOfNumbers = std::move(inputVectorOfVectorsOfNumbers);
    highlightStatus = noneHighlighted;
    alignment = Center;
    angle = {0,0,0};
    initializeNumberCubeTables();
}


void NumberCubePolyhedron::initializeNumberCubeTables()
{
    int length = vectorOfVectorsOfNumbers.size();
    double gapSize = 0.8 * edgeLength;                  // How far apart they are
    double curCenterZ;
    if(length % 2 == 0)
    {
        curCenterZ = -(edgeLength/2.0) - (length/2.0 - 1)*edgeLength - gapSize/2 - (length/2.0-1)*gapSize;
    }
    else
    {
        curCenterZ = - (length - 1)/2.0*edgeLength - (length-1)/2.0*gapSize;
    }

    for(int i = vectorOfVectorsOfNumbers.size() - 1; i > -1; i--)
    {
        std::vector<std::vector<int>> v = vectorOfVectorsOfNumbers[i];
        numberCubeTables.push_back(NumberCubeTable({center.x, center.y, curCenterZ},
                color, highlightedColor, center, edgeLength, edgeColor, numberColor, highlightedNumberColor, v));
        curCenterZ += edgeLength;
        curCenterZ += gapSize;
    }
}

// Getters
TableAlignment NumberCubePolyhedron::getAlignment() const
{
    return alignment;
}

// Setters
void NumberCubePolyhedron::setAlignment(TableAlignment input)
{
    alignment = input;
}
void NumberCubePolyhedron::resetRotation()
{
    rotate(-angle.x, -angle.y, -angle.z);
}


void NumberCubePolyhedron::highlight()
{
    isHighlighted = true;
    for(NumberCubeTable &nct : numberCubeTables)
    {
        nct.highlight();
    }
}
void NumberCubePolyhedron::unHighlight()
{
    isHighlighted = false;
    for(NumberCubeTable &nct : numberCubeTables)
    {
        nct.unHighlight();
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
    angle = {angle.x + thetaX, angle.y + thetaY, angle.z + thetaZ};
}

void NumberCubePolyhedron::reactToClick(glm::vec3 ray, glm::vec3 cameraLoc)
{

}
std::shared_ptr<NumberCube> NumberCubePolyhedron::getNumberCubeFromClick(glm::vec3 ray, glm::vec3 cameraLoc)
{
    double deltaT = 10;
    for(int t = 0; t < 1000; t += deltaT)
    {
        cameraLoc = {cameraLoc.x + deltaT*ray.x, cameraLoc.y + deltaT*ray.y, cameraLoc.z + deltaT*ray.z};
        for(NumberCubeTable &nct : numberCubeTables)
        {
            for(NumberCubeRow &ncr : *nct.getNumberCubeRows())
            {
                for(NumberCube &nc : *ncr.getNumberCubes())
                {
                    if(nc.getDigitalNumber().containsPoint(cameraLoc))
                    {
                        if(nc.getIsHighlighted())
                        {
                            nc.unHighlight();
                        }
                        else
                        {
                            nc.highlight();
                        }
                        return std::shared_ptr<NumberCube>();
                    }
                }
            }
        }
    }
    return std::shared_ptr<NumberCube>();
}