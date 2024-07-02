#pragma once
#include "Objects.h"

namespace game {
	class Player : public physics::Object {
	public:
		Player(sf::RenderWindow& owner, float sizeX, float sizeY, sf::Color color);
		void moveUp();
		void moveDown();
		sf::FloatRect getBonuds();
	private:
	};
}