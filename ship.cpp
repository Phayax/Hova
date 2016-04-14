#include <SFML/Window.hpp>
#include "ship.hpp"
#include <complex>

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

RectangleShape ShipVelocity::getShape()
{
	return shape;
}