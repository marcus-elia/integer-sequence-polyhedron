#include "numberCubePolyhedron.h"

#include <utility>

NumberCubePolyhedron::NumberCubePolyhedron() : DrawableObject(), CubeContainer()
{
    vectorOfVectorsOfNumbers = {{{1,2},{3,4}},{{5,6},{7,8}}};
    highlightStatus = noneHighlighted;
    alignment = Center;
    angle = {0,0,0};
    forwardCartesian = {0,0,1};
    forwardSpherical = {1, 0, 0};
    rightCartesian = {-1, 0, 0};
    rightSpherical = {1, PI, 0};
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
    forwardCartesian = {0,0,1};
    forwardSpherical = {1, 0, 0};
    rightCartesian = {-1, 0, 0};
    rightSpherical = {1, PI, 0};
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
void NumberCubePolyhedron::resetRotation(bool forget)
{
    /*for(int i = rotationHistory.size()-1; i > -1; i--)
    {
        rotate(-rotationHistory[i].x, -rotationHistory[i].y, -rotationHistory[i].z);
    }
    if(forget) // delete the history if we are not undoing this
    {
        rotationHistory = std::vector<point>();
    }*/
    // Rotate around z-axis, which puts the forward vector into the xz-plane
    if(forwardSpherical.y != 0)
    {
        rotate(0, 0, -forwardSpherical.y);
    }
    // Next, rotate around the y-axis to put forward facing the correct direction
    if(forwardSpherical.z != 0)
    {
        rotate(0, -forwardSpherical.z, 0);
    }
    if(rightSpherical.y != PI)
    {
        rotate(0, 0, PI - rightSpherical.y);
    }
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

    // Add the rotation to the stack.
    rotationHistory.push_back({thetaX, thetaY, thetaZ});

    rotatePointAroundPoint(forwardCartesian, point{0,0,0}, thetaX, thetaY, thetaZ);
    rotatePointAroundPoint(rightCartesian, point{0,0,0}, thetaX, thetaY, thetaZ);
    forwardSpherical = cartesianToSpherical(forwardCartesian);
    rightSpherical = cartesianToSpherical(rightCartesian);
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

point cartesianToSpherical(point &p)
{
    return {1, atan2(p.y, p.x), acos(p.z)};
}