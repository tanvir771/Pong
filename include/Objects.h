#pragma once

#include <SFML/Graphics.hpp>

namespace physics {
	class Object {
	public:
		Object(sf::RenderWindow owner, float sizeX, float sizeY)
			: _objMovingSpeed{ 0.f }, _objVerticalHeight{ 0.f }, _obj{ (sf::Vector2f(sizeX, sizeY)) }, _owner(owner)
		{};

		void setPos(float x, float y);

		bool getCollision(sf::RectangleShape anotherObj);

		bool isCollisionUpperWall();

		bool isCollisionLowerWall();

		bool isCollisionRightWall();

		bool isCollisionLeftWall();

	private:
		sf::RenderWindow _owner;
		sf::RectangleShape _obj;

		float _objMovingSpeed;
		float _objVerticalHeight;
	};
}