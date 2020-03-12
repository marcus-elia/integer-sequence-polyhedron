#ifndef INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBETABLE_H
#define INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBETABLE_H

#include "numberCubeRow.h"

class NumberCubeTable : public DrawableComponent, public CubeContainer
{
private:
    std::vector<std::vector<int>> vectorsOfNumbers;
    std::vector<NumberCubeRow> numberCubeRows;
    unsigned int edgeLength;
    RGBAcolor edgeColor;
    RGBAcolor numberColor;
    TableAlignment alignment;
    int maxRowSize;   // the longest row
public:
    NumberCubeTable();
    NumberCubeTable(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor, point &inputOwnerCenter,
                    unsigned int inputEdgeLength, RGBAcolor inputEdgeColor,
                    RGBAcolor inputNumberColor, RGBAcolor inputHighlightedNumberColor,
                    std::vector<std::vector<int>> inputVectorsOfNumbers);

    // Initializes the NumberCubeRow objects
    // Also finds the max row size
    void initializeNumberCubeRows();
    void updateNumberCubeRows(int tableSize, int rowSize);

    // Getters
    std::vector<NumberCubeRow>* getNumberCubeRows();
    TableAlignment getAlignment() const;
    int getMaxRowSize() const;

    // Setters
    void setAlignment(TableAlignment input);

    void highlight();
    void unHighlight();

    void draw() const;
    void drawLines() const;
    void drawFaces() const;
    void drawNumbers() const;

    void move(double deltaX, double deltaY, double deltaZ);
    void rotate(double thetaX, double thetaY, double thetaZ);
    void rotateAroundOwner(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBETABLE_H
