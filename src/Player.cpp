#include <SFML/Graphics.hpp>
#include "Player.h"

namespace game {
	Player::Player(sf::RenderWindow& owner, float sizeX, float sizeY, sf::Color color) : Object(owner, sizeX, sizeY) {
		_obj.setFillColor(color);
	}

	void Player::moveUp()
	{
		_obj.move(0.f, -10.f);
	}

	void Player::moveDown()
	{
		_obj.move(0.f, 10.f);
	}

	sf::FloatRect Player::getBonuds()
	{
		return _objBound;
	}
}