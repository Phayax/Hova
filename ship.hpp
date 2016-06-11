#ifndef HOVA_SHIP_H
#define HOVA_SHIP_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Entity {
protected:
	// gravity factor in g | [g] = m/s^2
	const float gravity = 0.5f;
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
	const float thrusterPropulsionImpulse = 0.1f;
	float rotation = 0.0f;
	Vector2f velocity{0.0f, 0.1f};
	RectangleShape shape;

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

	void followMouse(Vector2i mpos);
	void followMouseLine(Vector2i mpos);
	unsigned int followMouseThrusters(Vector2i mpos);

	void inputUp();
	void fireLeftThruster(unsigned int percent); 
	void fireRightThruster(unsigned int percent);

	void applyGravity() override;
	void update() override;
};


#endif // HOVA_SHIP_H