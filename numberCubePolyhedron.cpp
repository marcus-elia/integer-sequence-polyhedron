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

    // Determine the z-position where we will put the first NumberCubeTable
    if(length % 2 == 0)
    {
        curCenterZ = -(edgeLength/2.0) - (length/2.0 - 1)*edgeLength - gapSize/2 - (length/2.0-1)*gapSize;
    }
    else
    {
        curCenterZ = - (length - 1)/2.0*edgeLength - (length-1)/2.0*gapSize;
    }

    maxTableSize = 0;
    maxRowSize = 0;
    for(int i = vectorOfVectorsOfNumbers.size() - 1; i > -1; i--)
    {
        std::vector<std::vector<int>> v = vectorOfVectorsOfNumbers[i];

        NumberCubeTable nct = NumberCubeTable({center.x, center.y, curCenterZ},
                                              color, highlightedColor, center, edgeLength, edgeColor, numberColor,
                                              highlightedNumberColor, v);
        numberCubeTables.push_back(nct);
        curCenterZ += edgeLength;
        curCenterZ += gapSize;

        // Check for new longest table and row
        if(v.size() > maxTableSize)
        {
            maxTableSize = v.size();
        }
        if(nct.getMaxRowSize() > maxRowSize)
        {
            maxRowSize = nct.getMaxRowSize();
        }
    }
}

// Getters
TableAlignment NumberCubePolyhedron::getAlignment() const
{
    return alignment;
}
int NumberCubePolyhedron::getMaxRowSize() const
{
    return maxRowSize;
}
int NumberCubePolyhedron::getMaxTableSize() const
{
    return maxTableSize;
}

// Setters
void NumberCubePolyhedron::setAlignment(TableAlignment input)
{
    // If a new alignment has been chosen, move every cube
    if(alignment != input)
    {
        // Store the direction the polyhedron is facing
        point targetForward = forwardSpherical;
        point targetRight = rightSpherical;

        // Reset the rotation, so we can translate more easily
        resetRotation();

        // Now move everything
        alignment = input;
        for(NumberCubeTable &nct : numberCubeTables)
        {
            nct.setAlignment(alignment);
            nct.updateNumberCubeRows(maxTableSize, maxRowSize);
        }

        // Undo the rotation
        rotateToGivenDirection(targetForward, targetRight);
    }
}

void NumberCubePolyhedron::rotateToGivenDirection(point targetForward, point targetRight)
{
    if(forwardSpherical.y != targetForward.y)
    {
        rotate(0, 0, targetForward.y - forwardSpherical.y);
    }
    if(forwardSpherical.z != targetForward.z)
    {
        rotate(0, forwardSpherical.z - targetForward.z, 0);
    }
    if(rightSpherical.y != targetRight.y)
    {
        rotate(0, 0, targetRight.y - rightSpherical.y);
    }
}

void NumberCubePolyhedron::resetRotation()
{
    /*
    // Rotate around z-axis, which puts the forward vector into the xz-plane
    if(forwardSpherical.y != 0)
    {
        rotate(0, 0, -forwardSpherical.y);
    }
    // Next, rotate around the y-axis to put forward facing the correct direction
    if(forwardSpherical.z != 0)
    {
        rotate(0, forwardSpherical.z, 0);
    }
    if(rightSpherical.y != PI)
    {
        rotate(0, 0, PI - rightSpherical.y);
    }
     */
    rotateToGivenDirection({1, 0, 0}, {1, PI, PI/2});
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

    /*glColor4f(1,0,1,1);
    glBegin(GL_LINES);
    glVertex3f(center.x, center.y, center.z);
    glVertex3f(center.x + 300*forwardCartesian.x, center.y + 300*forwardCartesian.y, center.z + 300*forwardCartesian.z);
    glEnd();
    glColor4f(0,.8,.4,1);
    glBegin(GL_LINES);
    glVertex3f(center.x, center.y, center.z);
    glVertex3f(center.x + 300*rightCartesian.x, center.y + 300*rightCartesian.y, center.z + 300*rightCartesian.z);
    glEnd();*/
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
    // handle floating precision error
    if(p.z > 1)
    {
        return {1, atan2(p.y, p.x), 0};
    }
    else if(p.z < -1)
    {
        return {1, atan2(p.y, p.x), PI};
    }
    return {1, atan2(p.y, p.x), acos(p.z)};
}