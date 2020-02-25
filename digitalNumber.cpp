#include "digitalNumber.h"

DigitalNumber::DigitalNumber() : DrawableObject()
{
    number = 0;
}
DigitalNumber::DigitalNumber(point inputCenter, RGBAcolor inputColor, int inputNumber) :
               DrawableObject(inputCenter, inputColor)
{
    number = inputNumber;
}

void DigitalNumber::drawDigit(point position, int number)
{

}
void DigitalNumber::draw()
{
    
}