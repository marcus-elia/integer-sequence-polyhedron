#ifndef INTEGER_SEQUENCE_POLYHEDRON_CUBECONTAINER_H
#define INTEGER_SEQUENCE_POLYHEDRON_CUBECONTAINER_H

#include "drawableObject.h"

enum TableAlignment {Center, TopLeft, TopRight, BottomLeft, BottomRight};

class CubeContainer
{
protected:
    unsigned int edgeLength;
    RGBAcolor edgeColor;
    RGBAcolor numberColor;
    RGBAcolor highlightedNumberColor;
public:
    CubeContainer();
    CubeContainer(unsigned int inputEdgeLength, RGBAcolor inputEdgeColor,
            RGBAcolor inputNumberColor, RGBAcolor inputHighlightedNumberColor);

    virtual void highlight() = 0;
    virtual void unHighlight() = 0;
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_CUBECONTAINER_H
