#include "numberCubeRow.h"

#include <utility>

NumberCubeRow::NumberCubeRow() : DrawableComponent(), CubeContainer()
{
    numbers = std::vector<int>{1,341,5};
    initializeNumberCubes();
}

NumberCubeRow::NumberCubeRow(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor, point &inputOwnerCenter,
                             unsigned int inputEdgeLength, RGBAcolor inputEdgeColor,  RGBAcolor inputNumberColor,
                             RGBAcolor inputHighlightedNumberColor, std::vector<int> inputNumbers) :
               DrawableComponent(inputCenter, inputColor, inputHighlightedColor, inputOwnerCenter),
               CubeContainer(inputEdgeLength, inputEdgeColor, inputNumberColor, inputHighlightedNumberColor)
{
    numbers = inputNumbers;
    initializeNumberCubes();
}

void NumberCubeRow::initializeNumberCubes()
{
    int length = numbers.size();
    double gapSize = 0.8 * edgeLength;                  // How far apart they are
    double curCenter;
    if(length % 2 == 0)
    {
        curCenter = -(edgeLength/2.0) - (length/2.0 - 1)*edgeLength - gapSize/2 - (length/2.0-1)*gapSize;
    }
    else
    {
        curCenter = - (length - 1)/2.0*edgeLength - (length-1)/2*gapSize;
    }
    for(int i : numbers)
    {
        numberCubes.push_back(NumberCube({curCenter, center.y, center.z},
                color, highlightedColor, center, edgeColor, edgeLength, numberColor, highlightedNumberColor, i));
        curCenter += edgeLength;
        curCenter += gapSize;
    }
}

// Move the Cubes to conform with the TableAlignment
void NumberCubeRow::updateNumberCubes(int rowSize)
{
    int length = numbers.size();
    double gapSize = 0.8 * edgeLength;
    double curCenterX;

    // For center or left, we start left and move right
    if(alignment == Center)
    {
        if(length % 2 == 0)
        {
            curCenterX = -(edgeLength/2.0) - (length/2.0 - 1)*edgeLength - gapSize/2 - (length/2.0-1)*gapSize;
        }
        else
        {
            curCenterX = - (length - 1)/2.0*edgeLength - (length-1)/2*gapSize;
        }
    }
    else if(alignment == TopLeft || alignment == BottomLeft)
    {
        if(rowSize % 2 == 0)
        {
            curCenterX = -(edgeLength/2.0) - (rowSize/2.0 - 1)*edgeLength - gapSize/2 - (rowSize/2.0-1)*gapSize;
        }
        else
        {
            curCenterX = - (rowSize - 1)/2.0*edgeLength - (rowSize-1)/2*gapSize;
        }
    }

    // For right, we start right and move left
    else
    {
        if(rowSize % 2 == 0)
        {
            curCenterX = (edgeLength/2.0) + (rowSize/2.0 - 1)*edgeLength + gapSize/2 + (rowSize/2.0-1)*gapSize;
        }
        else
        {
            curCenterX = (rowSize - 1)/2.0*edgeLength + (rowSize-1)/2*gapSize;
        }
    }

    // Iterate through the number cubes and move them
    for(int i = 0; i < numberCubes.size(); i++)
    {
        NumberCube nc = numberCubes[i];
        nc.move(curCenterX - nc.getCenter().x, 0, 0);

        // Move to the left for the next cube
        if(alignment == TopRight || alignment == BottomRight)
        {
            curCenterX -= edgeLength;
            curCenterX -= gapSize;
        }
        // Move to the right for the next cube
        else
        {
            curCenterX += edgeLength;
            curCenterX += gapSize;
        }
    }
}





std::vector<NumberCube>* NumberCubeRow::getNumberCubes()
{
    return &numberCubes;
}

TableAlignment NumberCubeRow::getAlignment() const
{
    return alignment;
}

// Setters
void NumberCubeRow::setAlignment(TableAlignment input)
{
    alignment = input;
}




void NumberCubeRow::highlight()
{
    isHighlighted = true;
    for(NumberCube &nc : numberCubes)
    {
        nc.highlight();
    }
}
void NumberCubeRow::unHighlight()
{
    isHighlighted = false;
    for(NumberCube &nc : numberCubes)
    {
        nc.unHighlight();
    }
}

void NumberCubeRow::draw() const
{
    for(const NumberCube &nc : numberCubes)
    {
        nc.draw();
    }
}

void NumberCubeRow::drawLines() const
{
    for(const NumberCube &nc : numberCubes)
    {
        nc.drawLines();
    }
}

void NumberCubeRow::drawFaces() const
{
    for(const NumberCube &nc : numberCubes)
    {
        nc.drawFaces();
    }
}

void NumberCubeRow::drawNumbers() const
{
    for(const NumberCube &nc : numberCubes)
    {
        nc.drawNumber();
    }
}

void NumberCubeRow::move(double deltaX, double deltaY, double deltaZ)
{
    DrawableObject::move(deltaX, deltaY, deltaZ);
    for(NumberCube &nc : numberCubes)
    {
        nc.move(deltaX, deltaY, deltaZ);
    }
}

void NumberCubeRow::rotate(double thetaX, double thetaY, double thetaZ)
{
    for(NumberCube &nc : numberCubes)
    {
        nc.rotateAroundOwner(thetaX, thetaY, thetaZ);
    }
}
void NumberCubeRow::rotateAroundOwner(double thetaX, double thetaY, double thetaZ)
{
    // Store the previous coordinates, so we know how much to move the number
    double prevX = center.x;
    double prevY = center.y;
    double prevZ = center.z;

    // Rotates and revolves around the owner
    //DrawableComponent::rotateAroundOwner(thetaX, thetaY, thetaZ);
    rotatePointAroundPoint(center, ownerCenter, thetaX, thetaY, thetaZ);

    // Move the number cubes
    for(NumberCube &nc : numberCubes)
    {
        nc.setOwnerCenter(center);
        nc.move(center.x - prevX, center.y - prevY, center.z - prevZ);
    }

    // Rotate the number cubes
    for(NumberCube &nc : numberCubes)
    {
        nc.rotateAroundOwner(thetaX, thetaY, thetaZ);
        //nc.rotate(thetaX, thetaY, thetaZ);
    }
}