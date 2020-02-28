#include "cubeContainer.h"

CubeContainer::CubeContainer()
{
    edgeLength = 50;
    edgeColor = {1,1,1,1};
    numberColor = {0.4, 0.6, 1, 1};
    highlightedNumberColor = {1, 0.4, 0.6, 1};
}
CubeContainer::CubeContainer(unsigned int inputEdgeLength, RGBAcolor inputEdgeColor,
        RGBAcolor inputNumberColor, RGBAcolor inputHighlightedNumberColor)
{
    edgeLength = inputEdgeLength;
    edgeColor = inputEdgeColor;
    numberColor = inputNumberColor;
    highlightedNumberColor = inputHighlightedNumberColor;
}