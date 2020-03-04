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
    RGBAcolor hoverColor;
    TableAlignment selected;
    std::experimental::optional<TableAlignment> hovered;
    int numPoints;   // how fine/coarse the circle is
public:
    AlignmentSelecter();

    // Given coordinates on the screen (due to a mouse event), this returns the
    // TableAlignment whose button is at that position, or nullopt if none
    std::experimental::optional<TableAlignment> getAlignmentFromPosition(int mx, int my);

    std::experimental::optional<TableAlignment> reactToMouseMovement(int mx, int my);

    std::experimental::optional<TableAlignment> reactToClick(int mx, int my);

    void draw() const;
};

// Geometry helper functions
double distance(double x1, double y1, double x2, double y2);

// Returns the angle from (x1, y1) to (x2, y2) assuming up is +y
double angleToPoint(double x1, double y1, double x2, double y2);

#endif //INTEGER_SEQUENCE_POLYHEDRON_ALIGNMENTSELECTER_H
