#include <SFML/Graphics.hpp>

using namespace sf;

class Ship {
private:
	Vector2f velocity{0.0f, 0.0f};
	RectangleShape shape;
public:
	Ship(const int initx, const int inity, const int sizex, const int sizey);

	float getX();
	float getY();
	RectangleShape getShape();

	void followMouse(Vector2i mpos);

	void Update();
};