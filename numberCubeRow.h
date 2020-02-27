#ifndef INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEROW_H
#define INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEROW_H

#include "drawableComponent.h"
#include <vector>
#include "numberCube.h"

class NumberCubeRow : public DrawableComponent
{
private:
    std::vector<int> numbers;
    std::vector<NumberCube> numberCubes;
    unsigned int edgeLength;
    RGBAcolor edgeColor;
    RGBAcolor numberColor;
public:
    NumberCubeRow();
    NumberCubeRow(point inputCenter, RGBAcolor inputColor, point &inputOwnerCenter, RGBAcolor inputEdgeColor,
                  unsigned int inputEdgeLength, std::vector<int> inputNumbers, RGBAcolor inputNumberColor);

    void initializeNumberCubes();

    void draw() const;
    void move(double deltaX, double deltaY, double deltaZ);
    void rotate(double thetaX, double thetaY, double thetaZ);
    void rotateAroundOwner(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEROW_H
