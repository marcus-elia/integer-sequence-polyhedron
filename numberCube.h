#ifndef INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBE_H
#define INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBE_H

#include "cube.h"
#include "digitalNumber.h"

class NumberCube : public Cube
{
private:
    DigitalNumber number;
    bool isHighlighted;
public:
    NumberCube();
    NumberCube(point inputCenter, RGBAcolor inputColor, RGBAcolor inputEdgeColor, unsigned int inputEdgeLength,
            int inputNumber, RGBAcolor inputNumberColor);

    void draw() const;
    void move(double deltaX, double deltaY, double deltaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBE_H
