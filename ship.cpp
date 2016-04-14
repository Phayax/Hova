#include <SFML/Window.hpp>
#include "ship.hpp"

using namespace sf;

Ship::Ship(const int initx, const int inity, const int sizex, const int sizey)
{
	shape.setSize(Vector2f(sizex, sizey));
	shape.setFillColor(Color::Green);
	shape.setOutlineColor(Color::Red);
	shape.setPosition(initx, inity);
}

void Ship::followMouse(Vector2i mpos){
	if (mpos.x > getX()) {
		velocity.x += .01f;
	} else {
		velocity.x -= .01f;
	}
	if (mpos.y > getY()) {
		velocity.y += .01f;
	} else {
		velocity.y -= .01f;
	}
}

void Ship::Update()
{
	if(Keyboard::isKeyPressed(Keyboard::Key::Left)) {
		velocity.x -= 0.1f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Right)) {
		velocity.x += 0.1f;
	}
	if(Keyboard::isKeyPressed(Keyboard::Key::Up)) {
		velocity.y -= 0.1f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::Down)) {
		velocity.y += 0.1f;
	}
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
