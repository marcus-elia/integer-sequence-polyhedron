#ifndef INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H
#define INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H

#include "drawableObject.h"
#include "graphics.h"

class DigitalNumber : public DrawableObject
{
private:
    int number;
public:
    DigitalNumber();
    DigitalNumber(point inputCenter, RGBAcolor inputColor, int inputNumber);

    void drawDigit(point position, int number);
    void draw();
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H
