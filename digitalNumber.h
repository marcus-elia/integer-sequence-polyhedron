#ifndef INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H
#define INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H

#include "drawableComponent.h"
#include "graphics.h"
#include "digit.h"

class DigitalNumber : public DrawableComponent
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
    DigitalNumber(point inputCenter, RGBAcolor inputColor, point &inputOwnerCenter,
            int inputNumber, int inputMaxWidth, int inputMaxHeight);

    // Create the vector of Digit objects
    void initializeDigits();

    void draw() const;
    void move(double delta_x, double delta_y, double delta_z);
    void rotate(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H
