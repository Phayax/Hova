#include "velocityvector.hpp"
#include <complex>

VelocityVector::VelocityVector(Ship* shipref): ship(shipref)
{
    shape.setSize(Vector2f(2,100));
    shape.setFillColor(Color::Red);
}

void VelocityVector::applyGravity(){}

void VelocityVector::update()
{
    shape.setPosition(ship->getPosition());

    // set position in the middle of the ship
    Vector2f velocity = ship->getVelocity();

    std::complex<float> cvelo{velocity.x, velocity.y};

    // set new length and angle.
    // length is scaled a bit for better visibility.
    // the angle has to be converted to degrees and then transformed 
    // to match the axis orientation of the Shape rotation system.
    shape.setSize(Vector2f(2, abs(cvelo) * 10));
    shape.setRotation(arg(cvelo) * 180.0f / M_PI - 90.0f);
}

RectangleShape VelocityVector::getShape()
{
    return shape;
}