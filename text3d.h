#ifndef INC_3D_GRAPHICS_TEXT3D_H
#define INC_3D_GRAPHICS_TEXT3D_H

#include "cube.h"
#include <string>

class Text3D
{
private:
    point center;
    std::string text;
    int fontSize;
public:
    Text3D();
    Text3D(std::string inputText, point inputCenter, int inputFontSize);

    void draw() const;

    void move(double delta_x, double delta_y, double delta_z);
};

#endif //INC_3D_GRAPHICS_TEXT3D_H
