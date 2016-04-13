#include "ship.hpp"

using namespace sf;

Ship::Ship(const int initx, const int inity)
{
	shape.setSize(Vector2f(100, 40));
	shape.setFillColor(Color::Green);
	shape.setOutlineColor(Color::Red);
	shape.setPosition(initx - shape.getSize().x / 2, inity - shape.getSize().y / 2);
}

void Ship::Update()
{
	shape.move(velocity);
}

float Ship::getX()
{
	return shape.getPosition().x;
}

float Ship::getY()
{
	return shape.getPosition().y;
}

RectangleShape Ship::getShape()
{
	return shape;
}
