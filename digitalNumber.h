#ifndef INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H
#define INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H

#include "drawableObject.h"
#include "graphics.h"
#include "digit.h"

class DigitalNumber : public DrawableObject
{
private:
    // The number we are representing
    int number;

    // The dimensions we have to draw the number in
    int maxWidth;
    int maxHeight;

    std::vector<Digit> digits;
public:
    DigitalNumber();
    DigitalNumber(point inputCenter, RGBAcolor inputColor, int inputNumber, int inputMaxWidth, int inputMaxHeight);

    // Create the vector of Digit objects
    void initializeDigits();

    void draw();
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H
