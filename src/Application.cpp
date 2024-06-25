#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <string>
#include <vector>
#include <memory>
#include "Objects.h"

#include <iostream>

int main() {
	sf::RenderWindow window;

	srand(time(NULL));
	
	window.create(sf::VideoMode(800, 600), "New Window", sf::Style::Close);
	window.setVerticalSyncEnabled(true); // call it once, after creating the window

	sf::RectangleShape player(sf::Vector2f(20.f, 100.f));;
	player.setPosition(10.f, 50.f);
	player.move(5.f, 5.f);


	//sf::RectangleShape object(sf::Vector2f(20.f, 20.f));
	//object.setPosition(750, 300);

	std::vector<sf::RectangleShape> objects{};

	std::unique_ptr<physics::Object> obj = std::make_unique<physics::Object>(window, 20.f, 20.f);
	obj->setPos(750, 300);
	// set the shape color to green
	player.setFillColor(sf::Color(100, 250, 50));


	int score = 0;

	sf::Font font;
	if (!font.loadFromFile("E:\\Visual Studio Projects\\Project_Pong\\src\\Playground.ttf")) {
		return -1;
	}
	
	sf::Text text;
	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(30);
	text.setStyle(sf::Text::Bold);
	text.setPosition(650, 30);

	float objSpeed = -1.f;
	float objHeight = 0.f;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				player.move(0, -10.f);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				player.move(0, 10.f);
			}

		}

		if (obj->getCollision(player)) {
			objSpeed *= -1.25f;
			objHeight = (rand() % 3) - 3;
		}

		if (obj->isCollisionRightWall()) {
			objSpeed *= -1.f;
		}

		if (obj->isCollisionUpperWall() || obj->isCollisionLowerWall()) {
			objHeight *= -1.f;
		}

		if (obj->isCollisionLeftWall()) {
			window.close();
		}

		obj->move(objSpeed, objHeight);
		obj->updateObjBounds();	// recalculates the position and updates the objBound with it
								// TODO: dont want to update bounds each frame
		window.clear(sf::Color::Cyan);
		window.draw(player);
		window.draw(bar1);
		window.draw(bar2);
		obj->draw();
		score += 1; // each frame you survive, you gain a point


		text.setString(std::to_string(score));
		window.draw(text);
		window.display();
	}

	return 0;
}