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
		velocity.x += .1f;
	} else {
		velocity.x -= .1f;
	}
	if (mpos.y > getY()) {
		velocity.y += .1f;
	} else {
		velocity.y -= .1f;
	}
}

Vector2f Ship::getRelPosition()
{
	Vector2f pos = shape.getPosition();
	pos.x += shape.getSize().x / 2;
	pos.y += shape.getSize().y / 2;
	return pos;
}

void Ship::followMouseLine(Vector2i mpos)
{
	//Vector2f spos = shape.getPosition();
	Vector2f spos = getRelPosition();
	float xdiff = static_cast<float>(mpos.x) - spos.x;
	float ydiff = static_cast<float>(mpos.y) - spos.y;
	velocity.x = xdiff / 20;
	velocity.y = ydiff / 20;
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
