#include "numberCubeTable.h"

#include <utility>

NumberCubeTable::NumberCubeTable() : DrawableComponent(), CubeContainer()
{
    vectorsOfNumbers = std::vector<std::vector<int>>{{1,341,5},{2000,2,99},{0,40,4040}};
    alignment = Center;
    initializeNumberCubeRows();
}
NumberCubeTable::NumberCubeTable(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor,
                                 point &inputOwnerCenter,
                                 unsigned int inputEdgeLength, RGBAcolor inputEdgeColor,
                                 RGBAcolor inputNumberColor, RGBAcolor inputHighlightedNumberColor,
                                 std::vector<std::vector<int>> inputVectorsOfNumbers) :
                                 DrawableComponent(inputCenter, inputColor, inputHighlightedColor, inputOwnerCenter),
                                 CubeContainer(inputEdgeLength, inputEdgeColor, inputNumberColor,
                                         inputHighlightedNumberColor)
{
    vectorsOfNumbers = std::move(inputVectorsOfNumbers);
    edgeColor = inputEdgeColor;
    edgeLength = inputEdgeLength;
    numberColor = inputNumberColor;
    alignment = Center;
    initializeNumberCubeRows();
}

void NumberCubeTable::initializeNumberCubeRows()
{
    int length = vectorsOfNumbers.size();
    double gapSize = 0.8 * edgeLength;                  // How far apart they are
    double curCenterY;

    // Choose the y-coordinate for where we put the first NumberCubeRow, so that the row are vertically centered
    if(length % 2 == 0)
    {
        curCenterY = -(edgeLength/2.0) - (length/2.0 - 1)*edgeLength - gapSize/2 - (length/2.0-1)*gapSize;
    }
    else
    {
        curCenterY = - (length - 1)/2.0*edgeLength - (length-1)/2.0*gapSize;
    }

    maxRowSize = 0;
    for(int i = vectorsOfNumbers.size() - 1; i > -1; i--)
    {
        std::vector<int> v = vectorsOfNumbers[i];

        // Check for the max row size
        if(v.size() > maxRowSize)
        {
            maxRowSize = v.size();
        }

        // initialize the numbercuberow
        numberCubeRows.push_back(NumberCubeRow({center.x, curCenterY, center.z}, color, highlightedColor, center,
                                                     edgeLength, edgeColor, numberColor, highlightedNumberColor, v));
        curCenterY += edgeLength;
        curCenterY += gapSize;
    }
}

// Update the positions of the tables when a new alignment is set
void NumberCubeTable::updateNumberCubeRows(int tableSize, int rowSize)
{
    int length = vectorsOfNumbers.size();
    double gapSize = 0.8 * edgeLength;
    double curCenterY;

    if(alignment == Center)
    {
        if(length % 2 == 0)
        {
            curCenterY = -(edgeLength/2.0) - (length/2.0 - 1)*edgeLength - gapSize/2 - (length/2.0-1)*gapSize;
        }
        else
        {
            curCenterY = - (length - 1)/2.0*edgeLength - (length-1)/2.0*gapSize;
        }
    }
    else if(alignment == BottomLeft || alignment == BottomRight)
    {
        if(tableSize % 2 == 0)
        {
            curCenterY = -(edgeLength/2.0) - (tableSize/2.0 - 1)*edgeLength - gapSize/2 - (tableSize/2.0-1)*gapSize;
        }
        else
        {
            curCenterY = - (tableSize - 1)/2.0*edgeLength - (tableSize-1)/2.0*gapSize;
        }
    }
    else
    {
        if(tableSize % 2 == 0)
        {
            curCenterY = (edgeLength/2.0) + (tableSize/2.0 - length)*edgeLength + gapSize/2 + (tableSize/2.0 - length)*gapSize;
        }
        else
        {
            curCenterY = ((tableSize + 1)/2.0 - length)*edgeLength + ((tableSize + 1)/2.0 - length)*gapSize;
        }
    }

    // Iterate through the number cube rows and move them
    for(NumberCubeRow &ncr : numberCubeRows)
    //for(int i = numberCubeRows.size() - 1; i > -1; i--)
    {
        //NumberCubeRow &ncr = numberCubeRows[i];
        ncr.move(0, curCenterY - ncr.getCenter().y, 0);

        // Move up for the next cube
        curCenterY += edgeLength;
        curCenterY += gapSize;

        // Now update the cubes' positions for the row
        ncr.updateNumberCubes(rowSize);
    }
}


std::vector<NumberCubeRow>* NumberCubeTable::getNumberCubeRows()
{
    return &numberCubeRows;
}
TableAlignment NumberCubeTable::getAlignment() const
{
    return alignment;
}
int NumberCubeTable::getMaxRowSize() const
{
    return maxRowSize;
}

// Setters
void NumberCubeTable::setAlignment(TableAlignment input)
{
    alignment = input;
    for(NumberCubeRow &ncr : numberCubeRows)
    {
        ncr.setAlignment(alignment);
    }
}


void NumberCubeTable::highlight()
{
    isHighlighted = true;
    for(NumberCubeRow &ncr : numberCubeRows)
    {
        ncr.highlight();
    }
}
void NumberCubeTable::unHighlight()
{
    isHighlighted = false;
    for(NumberCubeRow &ncr : numberCubeRows)
    {
        ncr.unHighlight();
    }
}


void NumberCubeTable::draw() const
{
    for(NumberCubeRow ncr : numberCubeRows)
    {
        ncr.draw();
    }
}

void NumberCubeTable::drawLines() const
{
    for(NumberCubeRow ncr : numberCubeRows)
    {
        ncr.drawLines();
    }
}

void NumberCubeTable::drawFaces() const
{
    for(NumberCubeRow ncr : numberCubeRows)
    {
        ncr.drawFaces();
    }
}

void NumberCubeTable::drawNumbers() const
{
    for(NumberCubeRow ncr : numberCubeRows)
    {
        ncr.drawNumbers();
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