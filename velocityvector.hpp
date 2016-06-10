#ifndef HOVA_VELOVEC_H
#define HOVA_VELOVEC_H

#include <SFML/Graphics.hpp>
#include "ship.hpp"

using namespace sf;

class VelocityVector : public Entity{
private:
    RectangleShape shape;
    Ship* ship;

public: 
    VelocityVector(Ship* shipref);
    RectangleShape getShape();

    void applyGravity() override;
    void update() override;
};

#endif // HOVA_VELOVEC_H