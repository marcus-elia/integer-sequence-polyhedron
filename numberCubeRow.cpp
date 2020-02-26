#include "numberCubeRow.h"

NumberCubeRow::NumberCubeRow() : DrawableComponent()
{
    numbers = std::vector<int>{1,341,5};
    edgeLength = 50;
    edgeColor = {1,1,1,1};
    numberColor = {.4, .6, 1, 1};
    initializeNumberCubes();
}

NumberCubeRow::NumberCubeRow(point inputCenter, RGBAcolor inputColor, point inputOwnerCenter, RGBAcolor inputEdgeColor,
               unsigned int inputEdgeLength, std::vector<int> inputNumbers, RGBAcolor inputNumberColor) :
               DrawableComponent(inputCenter, inputColor, inputOwnerCenter)
{
    numbers = inputNumbers;
    edgeLength = inputEdgeLength;
    edgeColor = inputEdgeColor;
    numberColor = inputNumberColor;
    initializeNumberCubes();
}

void NumberCubeRow::initializeNumberCubes()
{
    int length = numbers.size();
    double curCenter;
    if(length % 2 == 0)
    {
        curCenter = -edgeLength/2.0 - (length/2.0 - 1)*edgeLength;
    }
    else
    {
        curCenter = - (length/2.0 - 1)*edgeLength;
    }
    for(int i : numbers)
    {

    }
}