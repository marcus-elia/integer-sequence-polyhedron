#ifndef INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEPOLYHEDRON_H
#define INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEPOLYHEDRON_H

#include "numberCubeTable.h"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

enum statusOfHighlights {noneHighlighted, oneHighlighted, lineHighlighted};

class NumberCubePolyhedron : public DrawableObject, public CubeContainer
{
private:
    std::vector<std::vector<std::vector<int>>> vectorOfVectorsOfNumbers;
    std::vector<NumberCubeTable> numberCubeTables;
    statusOfHighlights highlightStatus;
    TableAlignment alignment;
    point angle;

    // The forward vector and right vector. These will tell us how to undo a rotation
    point forwardCartesian, forwardSpherical;
    point rightCartesian, rightSpherical;

    // Keep track of the biggest dimensions
    int maxRowSize, maxTableSize;
public:
    NumberCubePolyhedron();
    NumberCubePolyhedron(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor,
                         unsigned int inputEdgeLength, RGBAcolor inputEdgeColor, RGBAcolor inputNumberColor,
                         RGBAcolor inputHighlightedNumberColor,
                         std::vector<std::vector<std::vector<int>>>  inputVectorOfVectorsOfNumbers);


    // Create the NumberCubeTable objects, based on the vector of vectors of numbers
    // Also initializes maxRowSize and maxTableSize
    void initializeNumberCubeTables();

    // Getters
    TableAlignment getAlignment() const;
    int getMaxRowSize() const;
    int getMaxTableSize() const;

    // Setters
    void setAlignment(TableAlignment input);

    // Rotate so that forward and right are pointing in the given directions
    // targetForward and targetRight are the spherical coordinates
    void rotateToGivenDirection(point targetForward, point targetRight);

    // Make it so that this is facing the camera again
    void resetRotation();

    void highlight();
    void unHighlight();

    void draw() const;
    void drawLines() const;
    void drawFaces() const;
    void drawNumbers() const;

    void move(double deltaX, double deltaY, double deltaZ);
    void rotate(double thetaX, double thetaY, double thetaZ);

    // Highlighting in response to clicks
    void reactToClick(glm::vec3 ray, glm::vec3 cameraLoc);
    std::shared_ptr<NumberCube> getNumberCubeFromClick(glm::vec3 ray, glm::vec3 cameraLoc);
};

// This assumes r = 1
point cartesianToSpherical(point &p);

#endif //INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEPOLYHEDRON_H
