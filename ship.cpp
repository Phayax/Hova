#include <SFML/Window.hpp>
#include "ship.hpp"
#include <cmath>
#include <iostream>

using namespace sf;

Ship::Ship(const int initx, const int inity, const int sizex, const int sizey)
{
	shape.setSize(Vector2f(sizex, sizey));
	shape.setFillColor(Color::Blue);
	//shape.setOutlineColor(Color::Red);
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

Vector2f Ship::getRelPosition()
{
	Vector2f pos = shape.getPosition();
	pos.x += shape.getSize().x / 2;
	pos.y += shape.getSize().y / 2;
	return pos;
}


void Ship::followMouse(Vector2i mpos){
	if (mpos.x > getRelPosition().x) {
		velocity.x += shipAccel;
	} else {
		velocity.x -= shipAccel;
	}
	if (mpos.y > getRelPosition().y) {
		velocity.y += shipAccel;
	} else {
		velocity.y -= shipAccel;
	}
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

void Ship::applyGravity(){
	velocity.y += gravity / 50;
}

void Ship::update()
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
	if (Keyboard::isKeyPressed(Keyboard::Key::Space)) {
		velocity.x *= .95f;
		velocity.y *= .95f;
	}
	shape.move(velocity);
}

ShipVelocity::ShipVelocity(Ship* shipref): ship(shipref)
{
	shape.setSize(Vector2f(2,100));
	shape.setFillColor(Color::Red);
}

void ShipVelocity::applyGravity(){}

void ShipVelocity::update()
{
	shape.setPosition(ship->getRelPosition());
	Vector2f velocity = ship->getVelocity();
	float length = std::sqrt(std::pow(velocity.x, 2) + std::pow(velocity.y, 2));
	//std::cout << std::to_string(velocity.x) + ", " + std::to_string(velocity.y) + " -> " + std::to_string(length) << std::endl;
	length *= 10;
	shape.setSize(Vector2f(2, length));
	//shape.rotate(3.0f);
	std::cout << atanDeg(velocity.x, velocity.y) << std::endl;
	shape.setRotation(atanDeg(velocity.x, velocity.y));
}

float ShipVelocity::atanDeg(const float x, const float y)
{
	// radian-angle and angle(in degree - the target unit)
	float rangle{0.0f};
	float angle{0.0f};

	// calculate for window coordinates

	rangle = atan(y / x);
	if (x < 0) {
		// atan(1) = π/4
		rangle += atan(1) * 4;
	}

	// change to degrees:
	angle = rangle * 360.0f / (2 * atan(1) * 4);

	while(angle < 0.0f){
		angle += 360.0f;
	}

	// transform to the rotation axis orientation of a Shape object:
	// overlay the two x axis
	angle -= 90.0f;

	// return the value and cry about axis orientations
	return angle;
}

RectangleShape ShipVelocity::getShape()
{
	return shape;
}