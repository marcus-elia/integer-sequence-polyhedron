#ifndef INTEGER_SEQUENCE_POLYHEDRON_DIGIT_H
#define INTEGER_SEQUENCE_POLYHEDRON_DIGIT_H

#include "drawableObject.h"
#include <vector>

class Digit : public DrawableObject
{
private:
    int digit;
    int width;
    int height;
    static std::vector<int> segments0;
    static std::vector<int> segments1;
    static std::vector<int> segments2;
    static std::vector<int> segments3;
    static std::vector<int> segments4;
    static std::vector<int> segments5;
    static std::vector<int> segments6;
    static std::vector<int> segments7;
    static std::vector<int> segments8;
    static std::vector<int> segments9;
public:
    Digit();
    Digit(point inputCenter, RGBAcolor inputColor, int inputDigit, int inputWidth, int inputHeight);

    void draw() const;
    void move(double delta_x, double delta_y, double delta_z);
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_DIGIT_H
