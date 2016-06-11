#ifndef HOVA_SHIP_H
#define HOVA_SHIP_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Entity {
protected:
    // gravity factor in g | [g] = m/s^2
    // ugly bugfix
    const float gravity = 0.51f;
public:
    float getGravity();

    virtual void applyGravity() = 0;
    virtual void update() = 0;
};

class Ship : public Entity{
private:
    const float keyPressAccel = .4f;
    const float shipAccel = .96f;
    const float thrusterRotationImpulse = 3.0f;
    const float thrusterPropulsionImpulse = 0.2f;
    float rotation = 0.0f;
    Vector2f velocity{0.0f, 0.1f};
    RectangleShape shape;

    unsigned int leftThrusterPercent = 0;
    unsigned int rightThrusterPercent = 0;

public:
    Ship(const int initx, const int inity, const int sizex, const int sizey);
    float getX();
    float getY();
    float getThrusterRotation();
    float getThrusterPropulsion();
    Vector2f getPosition();
    RectangleShape getShape();
    Vector2f getVelocity();
    // careful here:
    // ship.rotation is the attribute to gather all rotation processes in one tick
    // ship.shape.rotation is the actual rotation state.
    float getRotation();

    unsigned int getLeftThruster();
    unsigned int getRightThruster();

    void followMouse(Vector2i mpos);
    void followMouseLine(Vector2i mpos);
    void followMouseThrusters(Vector2i mpos);

    void fireLeftThruster(unsigned int percent); 
    void fireRightThruster(unsigned int percent);

    void applyGravity() override;
    void update() override;
};


#endif // HOVA_SHIP_H