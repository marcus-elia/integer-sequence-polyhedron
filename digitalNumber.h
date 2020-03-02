#ifndef INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H
#define INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H

#include <glm/vec3.hpp>
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

    // The digits we have
    std::vector<Digit> digits;

    // The corners of the background rectangle
    // {rightTop, rightBottom, leftBottom, leftTop}
    std::vector<point> bgCorners;
public:
    DigitalNumber();
    DigitalNumber(point inputCenter, RGBAcolor inputColor, RGBAcolor inputHighlightedColor, point &inputOwnerCenter,
            int inputNumber, int inputMaxWidth, int inputMaxHeight);

    // Create the vector of Digit objects.
    // Also initialize background corners
    void initializeDigits();

    void draw() const;

    // Setters
    void setColor(RGBAcolor inputColor);

    // Getters
    // Returns true if the point is within the background box of the number
    bool containsPoint(glm::vec3 point) const;

    void move(double delta_x, double delta_y, double delta_z);
    void rotate(double thetaX, double thetaY, double thetaZ);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_DIGITALNUMBER_H
