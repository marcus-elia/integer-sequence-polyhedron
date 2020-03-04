#ifndef INTEGER_SEQUENCE_POLYHEDRON_ALIGNMENTSELECTER_H
#define INTEGER_SEQUENCE_POLYHEDRON_ALIGNMENTSELECTER_H

#include "graphics.h"
#include "drawableObject.h"
#include "cubeContainer.h"
#include <experimental/optional>

/*
 * This is a set of five button that can be clicked on to select
 * the TableAlignment
 */

class AlignmentSelecter
{
private:
    int x;
    int y;
    int width;
    RGBAcolor color;
    RGBAcolor selectedColor;
    TableAlignment selected;
public:
    AlignmentSelecter();

    std::experimental::optional<TableAlignment> reactToClick(int mx, int my);

    void draw() const;
};

#endif //INTEGER_SEQUENCE_POLYHEDRON_ALIGNMENTSELECTER_H
