#include <SFML/Graphics.hpp>

using namespace sf;

class Entity {

public:
	const float gravity = 1.0f;
	virtual void applyGravity() = 0;
	virtual void update() = 0;
};

class Ship : public Entity{
private:
	const float shipAccel = .05f;
	Vector2f velocity{0.0f, 0.0f};
	RectangleShape shape;

public:
	Ship(const int initx, const int inity, const int sizex, const int sizey);

	float getX();
	float getY();
	Vector2f getRelPosition();
	RectangleShape getShape();
	Vector2f getVelocity();

	void followMouse(Vector2i mpos);
	void followMouseLine(Vector2i mpos);

	void applyGravity() override;
	void update() override;
};

class ShipVelocity : public Entity{
	RectangleShape shape;
	Ship* ship;

	float atanDeg(const Vector2f vector);
public: 
	ShipVelocity(Ship* shipref);
	RectangleShape getShape();

	void applyGravity() override;
	void update() override;
};