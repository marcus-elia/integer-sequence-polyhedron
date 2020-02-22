// The code in this file is based on code provided by Lisa Dion
// in a 3D graphics tutorial.

#ifndef INC_3D_GRAPHICS_CUBE_H
#define INC_3D_GRAPHICS_CUBE_H

#include <vector>

struct point
{
    double x;
    double y;
    double z;
};

class Cube
{
private:
    point center;
    unsigned int edge_length;
    std::vector<point> corners;
    void reset_corners();
    void draw_point(const point &p) const;
public:
    Cube();
    Cube(point center, unsigned int edge_length);

    void draw() const;
    void rotate(double theta_x, double theta_y, double theta_z);

    void move(double delta_x, double delta_y, double delta_z);
};


#endif //INC_3D_GRAPHICS_CUBE_H
