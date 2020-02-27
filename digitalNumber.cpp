#include "digitalNumber.h"

#include <utility>

DigitalNumber::DigitalNumber() : DrawableComponent()
{
    number = 0;
    initializeDigits();
}
DigitalNumber::DigitalNumber(point inputCenter, RGBAcolor inputColor, point &inputOwnerCenter,
        int inputNumber, int inputMaxWidth, int inputMaxHeight) :
               DrawableComponent(inputCenter, inputColor, inputOwnerCenter)
{
    number = inputNumber;
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
    double digitWidth = 0.9 * maxWidth / (1.2*d - 0.2); // How wide each one is
    double digitHeight = 2*digitWidth;                  // How tall they are
    if(digitHeight > maxHeight)
    {
        digitHeight = maxHeight;
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
    for(int i : decimalDigits)
    {
        digits.push_back(Digit({curCenterX, center.y, center.z}, color, center, i, digitWidth, digitHeight, digitWidth/5));
        curCenterX -= gapSize;
        curCenterX -= digitWidth;
    }
}

void DigitalNumber::draw() const
{
    for(Digit d : digits)
    {
        d.draw();
    }
}

void DigitalNumber::move(double deltaX, double deltaY, double deltaZ)
{
    center.x += deltaX;
    center.y += deltaY;
    center.z += deltaZ;
    for(Digit &d : digits)
    {
        d.move(deltaX, deltaY, deltaZ);
    }
}

void DigitalNumber::rotate(double thetaX, double thetaY, double thetaZ)
{
    return;
}