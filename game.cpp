#include <SFML/Graphics.hpp>
#include <string>
#include "game.hpp"

#include <iostream>

Game::Game()
{
	window.setFramerateLimit(60);
}

void Game::run(){
	while(true)
	{
		window.clear(Color::Black);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
		window.setTitle("Hova | mx: " + std::to_string(Mouse::getPosition(window).x) + " , my: " + std::to_string(Mouse::getPosition(window).y) + " | sx: " + std::to_string(ship.getPosition().x) + " , sy: " + std::to_string(ship.getPosition().y));
		inputPhase();
		updatePhase();
		renderPhase();
	}
}

void Game::inputPhase(){
}

void Game::updatePhase(){
	ship.applyGravity();
	//ship.followMouseLine(Mouse::getPosition(window));
	ship.followMouseThrusters(Mouse::getPosition(window));
	ship.update();
	shipVector.update();
}

void Game::renderPhase(){
	window.draw(ship.getShape());
	window.draw(shipVector.getShape());
	window.display();
}