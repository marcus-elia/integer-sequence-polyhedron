#ifndef INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBETABLE_H
#define INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBETABLE_H

#include "numberCubeRow.h"

class NumberCubeTable : public DrawableComponent
{
private:
    std::vector<std::vector<int>> vectorsOfNumbers;
    std::vector<NumberCubeRow> numberCubeRows;
    unsigned int edgeLength;
    RGBAcolor edgeColor;
    RGBAcolor numberColor;
public:
    NumberCubeTable();
    NumberCubeTable(point inputCenter, RGBAcolor inputColor, point inputOwnerCenter, RGBAcolor inputEdgeColor,
                    unsigned int inputEdgeLength, std::vector<std::vector<int>> inputVectorsOfNumbers,
                    RGBAcolor inputNumberColor);

    void initializeNumberCubeRows();

    void draw() const;
    void move(double deltaX, double deltaY, double deltaZ);
    void rotate(double thetaX, double thetaY, double thetaZ);
    void rotateAroundOwner(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBETABLE_H
