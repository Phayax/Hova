#include <SFML/Graphics.hpp>
#include <string>
#include "game.hpp"

#include <iostream>

Game::Game()
{
	window.setFramerateLimit(60);
	if (!font.loadFromFile("fonts/DroidSans.ttf")) {
		window.close();
		// cry (too lazy to figure out how to close the application)
	}
	statsText.setFont(font);
	statsText.setCharacterSize(20);
}

void Game::run(){
	while(true)
	{
		window.clear(Color::Black);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape)) break;
		std::string statusString = 
			"vel: " + std::to_string(ship.getVelocity().x) +
			" ~ " + std::to_string(ship.getVelocity().y) +
			//"mx: " + std::to_string(Mouse::getPosition(window).x) +
			//" , my: " + std::to_string(Mouse::getPosition(window).y) + 
			//" | sx: " + std::to_string(ship.getPosition().x) + 
			//" , sy: " + std::to_string(ship.getPosition().y) + 
			"\nrot: " + std::to_string(static_cast<int>(ship.getRotation()));
		statsText.setString(statusString);
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
	statsText.setString(statsText.getString() + " | ttt: " + std::to_string(ship.followMouseThrusters(Mouse::getPosition(window))));
	ship.update();
	shipVector.update();
}

void Game::renderPhase(){
	window.draw(ship.getShape());
	window.draw(shipVector.getShape());
	window.draw(statsText);
	window.display();
}