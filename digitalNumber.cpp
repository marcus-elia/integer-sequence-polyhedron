#include "digitalNumber.h"

#include <utility>

DigitalNumber::DigitalNumber() : DrawableComponent()
{
    number = 0;
    initializeDigits();
}
DigitalNumber::DigitalNumber(point inputCenter, RGBAcolor inputColor,RGBAcolor inputHighlightedColor, point &inputOwnerCenter,
        int inputNumber, int inputMaxWidth, int inputMaxHeight) :
               DrawableComponent(inputCenter, inputColor, inputHighlightedColor, inputOwnerCenter)
{
    if(number >= 0)
    {
        number = inputNumber;
    }
    else
    {
        number = -inputNumber;
    }
    maxWidth = inputMaxWidth;
    maxHeight = inputMaxHeight;
    initializeDigits();
}

void DigitalNumber::initializeDigits()
{
    // First, get a list of digits. So 341 becomes {1,4,3}
    std::vector<int> decimalDigits;
    decimalDigits.push_back(number % 10);
    int x = number - number % 10;
    x = x / 10;
    while(x != 0)
    {
        decimalDigits.push_back(x % 10);
        x = x - x % 10;
        x = x / 10;
    }

    // Now create Digit objects in the correct locations
    int d = decimalDigits.size();
    double digitWidth = 0.8 * maxWidth / (1.2*d - 0.2); // How wide each one is
    double digitHeight = 2*digitWidth;                  // How tall they are
    if(digitHeight > 0.8*maxHeight)
    {
        digitHeight = 0.8*maxHeight;
        digitWidth = digitHeight/2;
    }
    double gapSize = 0.2 * digitWidth;                  // How far apart they are

    double curCenterX;   // Keep track of we are putting Digits
    if(d % 2 == 0)
    {
        curCenterX = center.x + gapSize/2.0 + (d/2.0-1)*digitWidth + (d/2.0-1)*gapSize + digitWidth/2.0;
    }
    else
    {
        curCenterX = center.x + (d-1)/2*gapSize + (d-1)/2*digitWidth;
    }

    // The right side of the background
    bgCorners.push_back({curCenterX + digitWidth/2 + gapSize, center.y + digitHeight/2, center.z - 1});
    bgCorners.push_back({curCenterX + digitWidth/2 + gapSize, center.y - digitHeight/2, center.z - 1});

    // Create the digit objects in the correct places
    for(int i : decimalDigits)
    {
        digits.push_back(Digit({curCenterX, center.y, center.z}, color, center, i, digitWidth, digitHeight, digitWidth/5));

        // Move the location to the left
        curCenterX -= gapSize;
        curCenterX -= digitWidth;
    }
    // The left side of the background
    bgCorners.push_back({curCenterX + digitWidth/2, center.y - digitHeight/2, center.z - 1});
    bgCorners.push_back({curCenterX + digitWidth/2, center.y + digitHeight/2, center.z - 1});
}


void DigitalNumber::setColor(RGBAcolor inputColor)
{
    color = inputColor;
    for(Digit &d : digits)
    {
        d.setColor(inputColor);
    }
}

void DigitalNumber::draw() const
{
    // Draw each digit
    for(Digit d : digits)
    {
        d.draw();
    }

    // Draw the background
    glColor4f(0,0,0,0.9);
    glBegin(GL_QUADS);
    for(const point &p : bgCorners)
    {
        glVertex3f(p.x, p.y, p.z);
    }
    glEnd();
}

void DigitalNumber::move(double deltaX, double deltaY, double deltaZ)
{
    // Move the center of the number
    center.x += deltaX;
    center.y += deltaY;
    center.z += deltaZ;

    // Move each individual digit
    for(Digit &d : digits)
    {
        d.move(deltaX, deltaY, deltaZ);
    }

    // Move the background
    for(point &p : bgCorners)
    {
        p.x += deltaX;
        p.y += deltaY;
        p.z += deltaZ;
    }
}

void DigitalNumber::rotate(double thetaX, double thetaY, double thetaZ)
{
    return;
}