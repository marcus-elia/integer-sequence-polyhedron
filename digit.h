#ifndef INTEGER_SEQUENCE_POLYHEDRON_DIGIT_H
#define INTEGER_SEQUENCE_POLYHEDRON_DIGIT_H

#include "drawableObject.h"
#include <vector>
#include <memory>

/*
 * Each digit is primarily a numerical digit (0-9)
 * with functionality to render it using a
 * seven-segment display.
 *       1
 *       _
 *    6 |_| 2
 *    5 |_| 3
 *       4
 *  (7 is the middle segment)
 */

class Digit : public DrawableObject
{
private:
    int digit;

    // The width and height that the digit will take up
    double width;
    double height;
    // The thickness of the segments
    double thickness;

    static std::vector<std::vector<int>> segmentsVector;
public:
    Digit();
    Digit(point inputCenter, RGBAcolor inputColor, int inputDigit,
            double inputWidth, double inputHeight, double inputThickness);

    // Initialize the vector of segments to match the digit
    //void initializeSegments();

    void draw() const;
    void move(double delta_x, double delta_y, double delta_z);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_DIGIT_H
