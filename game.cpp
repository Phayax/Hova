#include <SFML/Graphics.hpp>
#include "game.hpp"
Game::Game()
{
	window.setFramerateLimit(60);
}

void Game::run(){
	while(true)
	{
		window.clear(Color::Black);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
		inputPhase();
		updatePhase();
		renderPhase();
	}
}

void Game::inputPhase(){

}

void Game::updatePhase(){
	ship.Update();
}

void Game::renderPhase(){
	window.draw(ship.getShape());
	window.display();
}