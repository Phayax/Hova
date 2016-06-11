#include <SFML/Window.hpp>
#include <complex> // for simple polar -> cartesian convertion
#include "ship.hpp"
#include <iostream>

using namespace sf;


float Entity::getGravity() {
    return gravity;
}

Ship::Ship(const int initx, const int inity, const int sizex, const int sizey)
{
    shape.setSize(Vector2f(sizex, sizey));
    shape.setFillColor(Color::Blue);
    shape.setOrigin(sizex / 2.0f, sizey / 2.0f);
    shape.setPosition(initx, inity);
}

RectangleShape Ship::getShape()
{
    return shape;
}

Vector2f Ship::getVelocity()
{
    return velocity;
}

Vector2f Ship::getPosition() {
    return shape.getPosition();
}

float Ship::getThrusterRotation() {
    return thrusterRotationImpulse;
}

float Ship::getThrusterPropulsion() {
    return thrusterPropulsionImpulse;
}

void Ship::followMouse(Vector2i mpos){
    if (mpos.x > shape.getPosition().x) {
        velocity.x += shipAccel;
    } else {
        velocity.x -= shipAccel;
    }
    if (mpos.y > shape.getPosition().y) {
        velocity.y += shipAccel;
    } else {
        velocity.y -= shipAccel;
    }
}

void Ship::followMouseLine(Vector2i mpos)
{
    //Vector2f spos = shape.getPosition();
    Vector2f spos = shape.getPosition();
    float xdiff = static_cast<float>(mpos.x) - spos.x;
    float ydiff = static_cast<float>(mpos.y) - spos.y;
    velocity.x = xdiff / 20;
    velocity.y = ydiff / 20;
}

void Ship::followMouseThrusters(Vector2i mpos) {
    Vector2f spos = shape.getPosition();
    Vector2f predictedPosition;

    float xdiff = static_cast<float>(mpos.x) - spos.x;
    float ydiff = static_cast<float>(mpos.y) - spos.y;

    float projectedTargetY = spos.y;
    float projectedVeloY = velocity.y;

    // reset fill color
    shape.setFillColor(Color::Blue);

    // if the mouse is above the ship
    if (static_cast<float>(mpos.y) < spos.y) {
        // calculate the maximum height when no thrusters were used any more
        while (projectedVeloY < 0) {
            // get y-axis thrust and apply it to the y-velocity
            //std::complex<float> thrustPointer = std::polar(getThrusterPropulsion(), shape.getRotation() * static_cast<float>(M_PI) / 180.0f);
            //projectedVeloY -= real(thrustPointer);

            projectedTargetY += projectedVeloY;
            projectedVeloY += getGravity() / 5;
        }
    } else {
        // calculate the minimum height if thruster were fired constantly
        while(projectedVeloY > 0) {
            // just assume full thrust
            projectedTargetY += projectedVeloY;
            
            // get y-axis thrust and apply it to the y-velocity
            std::complex<float> thrustPointer = std::polar(getThrusterPropulsion() * 2, shape.getRotation() * static_cast<float>(M_PI) / 180.0f);
            projectedVeloY -= real(thrustPointer);

            if (real(thrustPointer) < getGravity() / 5) {
                std::cout << "critical angle" << std::endl;
                // alert the user that the ship can't keep the height
                shape.setFillColor(Color::Red);
                // make sure the thrusters don't fire(otherwise the ship is just going to veer away)
                // by making sure the succesing if statement always runs.
                projectedTargetY = mpos.y - 1.0f;
                break;
            }
            // apply gravity
            projectedVeloY += getGravity() / 5;
        }
    }
    // if the projected maximum y coordinate is below the mouse fire the thrusters
    // otherwise do nothing (let the ship slow down)
    if (static_cast<int>(projectedTargetY) > mpos.y) {
        // it would be possible to adjust the thrusters better here but it
        // would be complicated and it looks nice if the ship takes a moment to adjust.
        fireLeftThruster(100);
        fireRightThruster(100);
    }
}

float Ship::getRotation() {
    return shape.getRotation();
}

void Ship::applyGravity(){
    leftThrusterPercent = 0;
    rightThrusterPercent = 0;
    velocity.y += getGravity() / 5;
}

void Ship::update()
{
    if(Keyboard::isKeyPressed(Keyboard::Key::Left)) {
        velocity.x -= keyPressAccel;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
        velocity.x += keyPressAccel;
    }
    if(Keyboard::isKeyPressed(Keyboard::Key::Up)) {
        velocity.y -= keyPressAccel;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
        velocity.y += keyPressAccel;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
        velocity.x *= .95f;
        velocity.y *= .95f;
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::A)) {
        fireLeftThruster(100);
    }
    if (Keyboard::isKeyPressed(Keyboard::Key::T)) {
        fireRightThruster(100);
    }
    //shape.rotate(1.0f);
    shape.move(Vector2f(0.0f, velocity.y));
    // apply rotation
    shape.setRotation(rotation);
}

void Ship::fireLeftThruster(unsigned int percent) {
    // limit percentage
    if (percent > 100) {
        percent = 100;
    }
    leftThrusterPercent = percent;
    // apply rotation
    rotation += getThrusterRotation();
    //shape.rotate(getThrusterRotation());
    // apply thrust
    const float thrust = static_cast<float>(percent) / 100.0f * getThrusterPropulsion();
    std::complex<float> thrustPointer = std::polar(thrust, shape.getRotation() * static_cast<float>(M_PI) / 180.0f);
    velocity.y -= real(thrustPointer);
    velocity.x += imag(thrustPointer);
}

void Ship::fireRightThruster(unsigned int percent) {
    // limit percentage
    if (percent > 100) {
        percent = 100;
    }
    rightThrusterPercent = percent;
        // apply rotation
    rotation -= getThrusterRotation();
    //shape.rotate(-getThrusterRotation());
    // apply thrust
    const float thrust = static_cast<float>(percent) / 100.0f * getThrusterPropulsion();
    std::complex<float> thrustPointer = std::polar(thrust, shape.getRotation() * static_cast<float>(M_PI) / 180.0f);
    velocity.y -= real(thrustPointer);
    velocity.x += imag(thrustPointer);  
}

unsigned int Ship::getLeftThruster() {
    return leftThrusterPercent;
}
unsigned int Ship::getRightThruster() {
    return rightThrusterPercent;
}
