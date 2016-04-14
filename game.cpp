#include <SFML/Graphics.hpp>
#include <string>
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
		window.setTitle("Hova | mx: " + std::to_string(Mouse::getPosition(window).x) + " , my: " + std::to_string(Mouse::getPosition(window).y) + " | sx: " + std::to_string(ship.getRelPosition().x) + " , sy: " + std::to_string(ship.getRelPosition().y));
		inputPhase();
		updatePhase();
		renderPhase();
	}
}

void Game::inputPhase(){

}

void Game::updatePhase(){
	ship.followMouseLine(Mouse::getPosition(window));
	ship.Update();
}

void Game::renderPhase(){
	window.draw(ship.getShape());
	window.display();
}