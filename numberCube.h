#ifndef INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBE_H
#define INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBE_H

#include "cube.h"
#include "digitalNumber.h"
#include "cubeContainer.h"

class NumberCube : public CubeContainer, public Cube
{
private:
    DigitalNumber number;
public:
    NumberCube();
    NumberCube(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor,
            point &inputOwnerCenter, RGBAcolor inputEdgeColor,
            unsigned int inputEdgeLength, RGBAcolor inputNumberColor, RGBAcolor inputHighlightedNumberColor, int inputNumber);

    // Draws all components
    void draw() const;

    void highlight();
    void unHighlight();

    // Draws just the DigitalNumber
    void drawNumber() const;

    void move(double deltaX, double deltaY, double deltaZ);

    void rotateAroundOwner(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBE_H
