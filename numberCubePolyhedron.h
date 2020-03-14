#ifndef INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEPOLYHEDRON_H
#define INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEPOLYHEDRON_H

#include "numberCubeTable.h"
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <experimental/optional>

enum statusOfHighlights {noneHighlighted, oneHighlighted, lineHighlighted};

// A point with integer coordinates
struct intPoint
{
    int x;
    int y;
    int z;
};

class NumberCubePolyhedron : public DrawableObject, public CubeContainer
{
private:
    std::vector<std::vector<std::vector<int>>> vectorOfVectorsOfNumbers;
    std::vector<NumberCubeTable> numberCubeTables;
    statusOfHighlights highlightStatus;
    TableAlignment alignment;
    point angle;

    // If one cube is highlighted
    NumberCube* highlightedCube;

    // The forward vector and right vector. These will tell us how to undo a rotation
    point forwardCartesian, forwardSpherical;
    point rightCartesian, rightSpherical;

    // Keep track of the rotations we did to get back to facing forwards, so we can undo them
    std::vector<point> temporaryRotationStack;

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
    // Returns true if it changes the alignment, false otherwise
    bool setAlignment(TableAlignment input);

    // DOES NOT WORK
    // Rotate so that forward and right are pointing in the given directions
    // targetForward and targetRight are the spherical coordinates
    void rotateToGivenDirection(point targetForward, point targetRight);

    // Make it so that this is facing the camera again
    void resetRotation();

    // Undo the rotations in the last call to reset rotation
    void returnRotation();

    void highlight();
    void unHighlight();

    void draw() const;
    void drawLines() const;
    void drawFaces() const;
    void drawNumbers() const;

    void move(double deltaX, double deltaY, double deltaZ);
    void rotate(double thetaX, double thetaY, double thetaZ);

    // Highlighting in response to clicks

    // Uses the ray increment method to find the first cube intersected by the ray starting at cameraloc
    // Can't use the line method because the cubes are rotated
    std::experimental::optional<NumberCube*> getNumberCubeFromClick(glm::vec3 ray, glm::vec3 cameraLoc);

    // Returns a vector of numbercubes on the specified line
    std::vector<NumberCube*> getCubesOnLine(point start, point end);

    // Returns the cube on the line closest to the start point
    std::experimental::optional<NumberCube*> getClosestCube(point start, point end);

    void highlightLineBetween(NumberCube* nc1, NumberCube* nc2);

    // The overall control for what happens when there is a click
    void reactToClick(glm::vec3 ray, glm::vec3 cameraLoc);


};

// This assumes r = 1
point cartesianToSpherical(point &p);

// 3d euclidean distance
double distance(point p1, point p2);

// If the segment intersects the box, returns a double between 0 and 1 that parametrizes the segment
// Otherwise, returns -1
double segmentIntersectsBox(point segStart, point segEnd, point boxMin, point boxMax);

#endif //INTEGER_SEQUENCE_POLYHEDRON_NUMBERCUBEPOLYHEDRON_H
