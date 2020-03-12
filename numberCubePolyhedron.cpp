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


std::vector<std::shared_ptr<NumberCube>> NumberCubePolyhedron::getCubesOnLine(point start, point end)
{
    std::vector<std::shared_ptr<NumberCube>> cubesOnLine;

    // Iterate through all number cubes
    for(NumberCubeTable &nct : numberCubeTables)
    {
        for(NumberCubeRow &ncr : *nct.getNumberCubeRows())
        {
            for(NumberCube &nc : *ncr.getNumberCubes())
            {
                double param = segmentIntersectsBox(start, end, nc.getMin(), nc.getMax());
                // If the segment intersects this cube
                if(param > -0.5)
                {
                    cubesOnLine.push_back(std::make_shared<NumberCube>(nc));
                }
            }
        }
    }
    return cubesOnLine;
}

std::experimental::optional<std::shared_ptr<NumberCube>> NumberCubePolyhedron::getClosestCube(point start, point end)
{
    std::vector<std::shared_ptr<NumberCube>> cubes = getCubesOnLine(start, end);
    if(cubes.empty())
    {
        return std::experimental::nullopt;
    }
    // Find the min distance
    double min = distance(start, cubes[0]->getCenter());
    double curDistance;
    std::shared_ptr<NumberCube> closestCube = cubes[0];
    for(std::shared_ptr<NumberCube> nc : cubes)
    {
        curDistance = distance(start, nc->getCenter());
        if(curDistance < min)
        {
            curDistance = min;
            closestCube = nc;
        }
    }
    return closestCube;
}


std::experimental::optional<std::shared_ptr<NumberCube>> NumberCubePolyhedron::getNumberCubeFromClick(glm::vec3 ray, glm::vec3 cameraLoc)
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
                        /*if(nc.getIsHighlighted())
                        {
                            nc.unHighlight();
                        }
                        else
                        {
                            nc.highlight();
                        }*/
                        return std::shared_ptr<NumberCube>(&nc);
                    }
                }
            }
        }
    }
    return std::experimental::nullopt;
}

void NumberCubePolyhedron::highlightLineBetween(std::shared_ptr<NumberCube> nc1, std::shared_ptr<NumberCube> nc2)
{
    // Store the direction the polyhedron is facing
    point targetForward = forwardSpherical;
    point targetRight = rightSpherical;

    // Reset the rotation, so we can test intersections more easily
    resetRotation();

    point start = nc1->getCenter();
    point end = nc2->getCenter();
    point direction = {end.x - start.x, end.y - start.y, end.z - start.z};
    start = {start.x - 10000*direction.x, start.y - 10000*direction.y, start.z - 10000*direction.z};
    end = {end.x + 10000*direction.x, end.y + 10000*direction.y, end.z + 10000*direction.z};

    std::vector<std::shared_ptr<NumberCube>> onLine = getCubesOnLine(start, end);
    for(std::shared_ptr<NumberCube> nc : onLine)
    {
        nc->highlight();
    }
    highlightStatus = lineHighlighted;

    // Unrotate
    rotateToGivenDirection(targetForward, targetRight);
}

void NumberCubePolyhedron::reactToClick(glm::vec3 ray, glm::vec3 cameraLoc)
{
    std::experimental::optional<std::shared_ptr<NumberCube>> newCube = getNumberCubeFromClick(ray, cameraLoc);
    if(highlightStatus == lineHighlighted || !newCube)
    {
        unHighlight();
    }
    else if(highlightStatus == noneHighlighted)
    {
        highlightedCube = newCube.value();
        highlightedCube->highlight();
        highlightStatus = oneHighlighted;
    }
    else
    {
        if(newCube.value() == highlightedCube)
        {
            unHighlight();
        }
        else  // A second cube was clicked on
        {
            highlightLineBetween(highlightedCube, newCube.value());
        }
    }
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

double distance(point p1, point p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));
}

// This code is from Dan Hathaway
double segmentIntersectsBox(point segStart, point segEnd, point boxMin, point boxMax)
{
    double param;  // what will be returned

    // If the segment is oriented backwards in the x-direction
    if( segStart.x > boxMax.x &&
        segEnd.x   < boxMax.x )
    {
        param =
                (segStart.x - boxMax.x) /
                (segStart.x - segEnd.x);
        double p_y = segStart.y * (1.0f - param) + segEnd.y * param;
        double p_z = segStart.z * (1.0f - param) + segEnd.z * param;
        if( p_y >= boxMin.y &&
            p_z >= boxMin.z &&
            p_y <= boxMax.y &&
            p_z <= boxMax.z )
        {
            return param;
        }
    }
    // If the segment is oriented backwards in the y-direction
    if( segStart.y > boxMax.y &&
        segEnd.y   < boxMax.y )
    {
        param =
                (segStart.y - boxMax.y) /
                (segStart.y - segEnd.y);
        double p_x = segStart.x * (1.0f - param) + segEnd.x * param;
        double p_z = segStart.z * (1.0f - param) + segEnd.z * param;
        if( p_x >= boxMin.x &&
            p_z >= boxMin.z &&
            p_x <= boxMax.x &&
            p_z <= boxMax.z )
        {
            return param;
        }
    }
    // If the segment is oriented backwards in the z-direction
    if( segStart.z > boxMax.z &&
        segEnd.z   < boxMax.z )
    {
        param =
                (segStart.z - boxMax.z) /
                (segStart.z - segEnd.z);
        double p_x = segStart.x * (1.0f - param) + segEnd.x * param;
        double p_y = segStart.y * (1.0f - param) + segEnd.y * param;
        if( p_x >= boxMin.x &&
            p_y >= boxMin.y &&
            p_x <= boxMax.x &&
            p_y <= boxMax.y )
        {
            return param;
        }
    }

    // If the segment is oriented forwards in the x-direction
    if( segStart.x < boxMin.x &&
        segEnd.x   > boxMin.x )
    {
        param =
                (boxMin.x - segStart.x) /
                (segEnd.x - segStart.x);
        double p_y = segStart.y * (1.0f - param) + segEnd.y * param;
        double p_z = segStart.z * (1.0f - param) + segEnd.z * param;
        if( p_y >= boxMin.y &&
            p_z >= boxMin.z &&
            p_y <= boxMax.y &&
            p_z <= boxMax.z )
        {
            return param;
        }
    }
    // If the segment is oriented forwards in the y-direction
    if( segStart.y < boxMin.y &&
        segEnd.y   > boxMin.y )
    {
        param =
                (boxMin.y - segStart.y) /
                (segEnd.y - segStart.y);
        double p_x = segStart.x * (1.0f - param) + segEnd.x * param;
        double p_z = segStart.z * (1.0f - param) + segEnd.z * param;
        if( p_x >= boxMin.x &&
            p_z >= boxMin.z &&
            p_x <= boxMax.x &&
            p_z <= boxMax.z )
        {
            return param;
        }
    }
    // If the segment is oriented forwards in the z-direction
    if( segStart.z < boxMin.z &&
        segEnd.z   > boxMin.z )
    {
        param =
                (boxMin.z - segStart.z) /
                (segEnd.z - segStart.z);
        double p_x = segStart.x * (1.0f - param) + segEnd.x * param;
        double p_y = segStart.y * (1.0f - param) + segEnd.y * param;
        if( p_x >= boxMin.x &&
            p_y >= boxMin.y &&
            p_x <= boxMax.x &&
            p_y <= boxMax.y )
        {
            return param;
        }
    }

    // If the starting point is in the box already
    if( segStart.x >= boxMin.x &&
        segStart.y >= boxMin.y &&
        segStart.z >= boxMin.z &&
        segStart.x <= boxMax.x &&
        segStart.y <= boxMax.y &&
        segStart.z <= boxMax.z )
    {
        param = 0.0f;
        return param;
    }
    // Otherwise, no intersection
    return -1;
}