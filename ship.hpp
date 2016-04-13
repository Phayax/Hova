#include <SFML/Graphics.hpp>

using namespace sf;

class Ship {
private:
	Vector2f velocity{0.0f, -2.0f};
	RectangleShape shape;
public:
	Ship(const int initx, const int inity);

	float getX();
	float getY();
	RectangleShape getShape();

	void Update();
};