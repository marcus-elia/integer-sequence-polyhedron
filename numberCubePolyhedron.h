#ifndef INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEPOLYHEDRON_H
#define INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEPOLYHEDRON_H

#include "numberCubeTable.h"

class NumberCubePolyhedron : public DrawableObject, public CubeContainer
{
private:
    std::vector<std::vector<std::vector<int>>> vectorOfVectorsOfNumbers;
    std::vector<NumberCubeTable> numberCubeTables;
public:
    NumberCubePolyhedron();
    NumberCubePolyhedron(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor,
                         unsigned int inputEdgeLength, RGBAcolor inputEdgeColor, RGBAcolor inputNumberColor,
                         RGBAcolor inputHighlightedNumberColor,
                         std::vector<std::vector<std::vector<int>>>  inputVectorOfVectorsOfNumbers);


    void initializeNumberCubeTables();

    void highlight();
    void unHighlight();

    void draw() const;
    void drawLines() const;
    void drawFaces() const;
    void drawNumbers() const;

    void move(double deltaX, double deltaY, double deltaZ);
    void rotate(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEPOLYHEDRON_H
