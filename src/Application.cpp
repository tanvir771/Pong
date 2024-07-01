#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <string>
#include <vector>
#include <memory>
#include "Objects.h"

#include <iostream>

void createObjects(sf::RenderWindow& window, std::vector<std::shared_ptr<physics::Object>>& objects);

int main() {
	sf::RenderWindow window;

	srand(time(NULL));
	
	window.create(sf::VideoMode(800, 600), "New Window", sf::Style::Close);
	window.setVerticalSyncEnabled(true); // call it once, after creating the window

	sf::RectangleShape player(sf::Vector2f(20.f, 100.f));;
	player.setPosition(10.f, 50.f);
	player.move(5.f, 5.f);

	float barXSize = 20.f;
	float barYSize = 100.f;
	sf::RectangleShape bar(sf::Vector2f(barXSize, barYSize));
	bar.setPosition(780, 250);
	bar.setFillColor(sf::Color::Black);

	int objNumber = 1; 

	std::vector<std::shared_ptr<physics::Object>> objects{};

	createObjects(window, objects);


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


		window.clear(sf::Color::Cyan);
		window.draw(player);

		std::vector<std::shared_ptr<physics::Object>> objectsToRemove;

		for (std::shared_ptr<physics::Object> obj : objects) {

			float objSpeed = -1.f;
			float objHeight = 0.f;

			obj->updateObjBounds();	// recalculates the position and updates the objBound with it
									// TODO: dont want to update bounds each frame
			if (obj->getCollision(player)) {
				obj->increaseSpeed(1.25f);
				obj->reverseHorizontalDirection();
				obj->increaseVerticalHeight((rand() % 3) - 3);
			}

			if (obj->getCollision(bar)) {
				objectsToRemove.push_back(obj);
				bar.move(0, (rand() % 200) - 200);
				barYSize -= 1;
				if (barYSize <= 0) {
					window.close();
				}
				bar.setSize(sf::Vector2f(barXSize, barYSize));
				continue;
			}

			if (obj->isCollisionRightWall()) {
				obj->reverseHorizontalDirection();
			}

			if (obj->isCollisionUpperWall() || obj->isCollisionLowerWall()) {
				obj->reverseVerticalDirection();
			}

			if (obj->isCollisionLeftWall()) {
				window.close();
			}
			obj->move();
			obj->draw();

		}

		// Remove objects that collided with the bar
		for (const auto& obj : objectsToRemove) {
			objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
		}

		score += 1; // each frame you survive, you gain a point


		if (score % 700 == 0) {
			createObjects(window, objects);
		}

		text.setString(std::to_string(score));
		window.draw(text);
		window.draw(bar);
		window.display();
	}

	return 0;
}

void createObjects(sf::RenderWindow& window, std::vector<std::shared_ptr<physics::Object>>& objects) {
	std::shared_ptr<physics::Object> obj = std::make_shared<physics::Object>(window, 20.f, 20.f);
	obj->setPos(750, 300);
	objects.push_back(obj);
}