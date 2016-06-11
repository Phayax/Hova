#include "velocityvector.hpp"
#include <complex>

// TODO: remove this
#include <iostream>

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

ThrusterVectors::ThrusterVectors(Ship* shipref): ship(shipref)
{
    shapeLeft.setSize(Vector2f(20, 0));
    shapeRight.setSize(Vector2f(20, 0));
    shapeLeft.setOrigin(Vector2f(10,0));
    shapeRight.setOrigin(Vector2f(10,0));

    shapeLeft.setFillColor(Color::White);
    shapeRight.setFillColor(Color::White);
}

RectangleShape ThrusterVectors::getLeftShape() {
    return shapeLeft;
}

RectangleShape ThrusterVectors::getRightShape() {
    return shapeRight;
}

void ThrusterVectors::applyGravity(){}

void ThrusterVectors::update() {
    Vector2f shipCenter = ship->getPosition();

    int leftThrust = static_cast<int>(ship->getLeftThruster() / 2);
    int rightThrust = static_cast<int>(ship->getRightThruster() / 2);

    // don't ask me why 39... there is a stupid "off-by-one-error" hiding somewhere.
    std::complex<float> leftPart = std::polar(39.0f, (ship->getRotation() - 90.0f) / 180.0f * static_cast<float>(M_PI));
    std::complex<float> rightPart = std::polar(40.0f, (ship->getRotation() + 90.0f) / 180.0f * static_cast<float>(M_PI));
    
    std::complex<float> leftLower = std::polar(20.0f, (ship->getRotation() -180.0f) / 180.0f * static_cast<float>(M_PI));
    std::complex<float> rightLower = std::polar(20.0f, (ship->getRotation() -180.0f) / 180.0f * static_cast<float>(M_PI));


    // add the vectors
    std::complex<float> leftPointer = leftPart + leftLower;
    std::complex<float> rightPointer = rightPart + rightLower;

    // get the distance vectors
    Vector2f leftDistance = Vector2f(imag(leftPointer), -real(leftPointer));
    Vector2f rightDistance = Vector2f(imag(rightPointer), -real(rightPointer));

    std::cout << leftDistance.x << " | " << leftDistance.y << std::endl;

    shapeLeft.setSize(Vector2f(20, leftThrust));
    shapeRight.setSize(Vector2f(20, rightThrust));
    // set position and rotation
    shapeLeft.setPosition(shipCenter + leftDistance);
    shapeLeft.setRotation(ship->getRotation());// - 90.0f);
    shapeRight.setPosition(shipCenter + rightDistance);
    shapeRight.setRotation(ship->getRotation());// + 90.0f);
}