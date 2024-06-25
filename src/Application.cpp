#include <SFML/Graphics.hpp>
#include <random>
#include <time.h>
#include <string>
#include <vector>

#include <iostream>

int main() {
	sf::RenderWindow window;

	srand(time(NULL));
	
	std::vector<sf::RectangleShape> objects{};

	window.create(sf::VideoMode(800, 600), "New Window", sf::Style::Close);
	std::cout << window.getSize().x;
	window.setVerticalSyncEnabled(true); // call it once, after creating the window

	sf::RectangleShape player(sf::Vector2f(20.f, 100.f));;
	player.setPosition(10.f, 50.f);
	player.move(5.f, 5.f);

	sf::RectangleShape object(sf::Vector2f(20.f, 20.f));
	object.setPosition(750, 300);

	sf::RectangleShape anotherObj(sf::Vector2f(20.f, 20.f));
	anotherObj.setPosition(750, 300);

	objects.push_back(object);
	objects.push_back(anotherObj);

	// set the shape color to green
	player.setFillColor(sf::Color(100, 250, 50));

	float objMovingSpeed = -2.5f;
	float objVerticalHeight = objVerticalHeight = rand() % 5 - 2;

	float anotherObjSpeed = -2.5f;
	float anotherObjVerticalHeight = objVerticalHeight = rand() % 5 - 2;

	int score = 0;

	sf::Font font;
	if (!font.loadFromFile("E:\\Visual Studio Projects\\SMFL_FUN\\Sfml_Fun\\src\\Playground.ttf")) {
		return -1;
	}
	
	sf::Text text;
	text.setFont(font);
	text.setColor(sf::Color::Black);
	text.setCharacterSize(50);
	text.setStyle(sf::Text::Bold);
	text.setPosition(700, 30);

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

		sf::FloatRect player_bounds = player.getGlobalBounds();
		sf::FloatRect object_bounds = object.getGlobalBounds();


		if (object_bounds.intersects(player_bounds)) {
			objMovingSpeed *= -1.f;
			objVerticalHeight = rand() % 5 - 2;
			score += 50;
		}

		if (object_bounds.left + object_bounds.width >= 800) {
			objMovingSpeed *= -1.25f;
			objVerticalHeight = rand() % 5 - 2;
		}

		if (object_bounds.top <= 0 || object_bounds.top >= 600) {
			objVerticalHeight *= -1.f;
		}

		if (object_bounds.left < 0) {
			window.close();
		}

		object.move(objMovingSpeed, objVerticalHeight);
		window.clear(sf::Color::Cyan);
		window.draw(player);
		window.draw(object);
		score += 1; // each frame you survive, you gain a point

		if (score >= 500) {
			window.draw(anotherObj);
			anotherObj.move(anotherObjSpeed, anotherObjVerticalHeight);
		}
		text.setString(std::to_string(score));
		window.draw(text);
		window.display();
	}

	return 0;
}