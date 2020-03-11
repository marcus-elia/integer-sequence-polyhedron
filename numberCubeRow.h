#ifndef INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEROW_H
#define INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEROW_H

#include "cubeContainer.h"
#include <vector>
#include "numberCube.h"

class NumberCubeRow : public CubeContainer, public DrawableComponent
{
private:
    std::vector<int> numbers;
    std::vector<NumberCube> numberCubes;
    TableAlignment alignment;
public:
    NumberCubeRow();
    NumberCubeRow(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor, point &inputOwnerCenter,
            unsigned int inputEdgeLength, RGBAcolor inputEdgeColor,  RGBAcolor inputNumberColor, RGBAcolor inputHighlightedNumberColor,
            std::vector<int> inputNumbers);

    void initializeNumberCubes();
    void updateNumberCubes(int rowSize);

    // Getters
    std::vector<NumberCube>* getNumberCubes();
    TableAlignment getAlignment() const;

    // Setters
    void setAlignment(TableAlignment input);

    void highlight();
    void unHighlight();

    void draw() const;
    void drawLines() const;
    void drawNumbers() const;
    void drawFaces() const;

    void move(double deltaX, double deltaY, double deltaZ);
    void rotate(double thetaX, double thetaY, double thetaZ);
    void rotateAroundOwner(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEROW_H
