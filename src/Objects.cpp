#include <Objects.h>

namespace physics {
	Object::Object(sf::RenderWindow& owner, float sizeX, float sizeY)
		: _objMovingSpeed{ -1.f }, _objVerticalHeight{ 0.f }, _obj{ (sf::Vector2f(sizeX, sizeY)) }, _owner{ owner }
	{
		_objBound = _obj.getGlobalBounds();
	};

	void Object::setPos(float x, float y)
	{
		_obj.setPosition(x, y);
	}

	void Object::setSpeed(float speed) {
		_objMovingSpeed = speed;
	}

	void Object::setHeight(float height) {
		_objVerticalHeight = height;
	}

	bool Object::getCollision(sf::RectangleShape anotherObj)
	{
		sf::FloatRect anotherObjBound = anotherObj.getGlobalBounds();
		return _objBound.intersects(anotherObjBound);
	}

	void Object::updateObjBounds()
	{
		_objBound = _obj.getGlobalBounds();
	}
	bool Object::isCollisionUpperWall()
	{
		return (_objBound.top <= 0);
	}
	bool Object::isCollisionLowerWall()
	{
		return (_objBound.top + _objBound.height >= _owner.getSize().y);
	}

	bool Object::isCollisionRightWall()
	{
		return (_objBound.left + _objBound.width >= _owner.getSize().x);
	}

	bool Object::isCollisionLeftWall()
	{
		return (_objBound.left < 0);
	}

	void Object::move()
	{
		_obj.move(_objMovingSpeed, _objVerticalHeight);
	}

	void Object::draw()
	{
		_owner.draw(_obj);
	}

}