#include <SFML/Window.hpp>
#include "ship.hpp"
using namespace sf;

constexpr int windowWidth{1300}, windowHeight{700};

class Game {
private:

	RenderWindow window{{windowWidth, windowHeight},"Hova - Fly Away!"};
	Ship ship{windowWidth / 2, windowHeight / 2,100,40};
	ShipVelocity shipVector{&ship};

public:
	Game();

	void run();

	void inputPhase();
	void updatePhase();
	void renderPhase();
};