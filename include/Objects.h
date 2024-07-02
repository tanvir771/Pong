#pragma once

#include <SFML/Graphics.hpp>

namespace physics {
	class Player;

	class Object {
	public:
		Object(sf::RenderWindow& owner, float sizeX, float sizeY);

		void setPos(float x, float y);

		bool getCollision(std::shared_ptr<Object> anotherObj);

		bool getCollision(sf::RectangleShape& anotherObj);

		void updateObjBounds();

		bool isCollisionUpperWall();

		bool isCollisionLowerWall();

		bool isCollisionRightWall();

		bool isCollisionLeftWall();

		void move();

		void setSpeed(float speed);
		
		void setHeight(float height);
		
		void increaseSpeed(float factor);

		void increaseVerticalHeight(float amount);

		void reverseHorizontalDirection();

		void reverseVerticalDirection();

		void draw();
		sf::FloatRect _objBound;

	protected:
		sf::RenderWindow& _owner;
		sf::RectangleShape _obj;

		float _objMovingSpeed;
		float _objVerticalHeight;
	};
}