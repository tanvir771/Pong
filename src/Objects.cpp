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

	bool Object::getCollision(std::shared_ptr<Object> anotherObj)
	{
		anotherObj->updateObjBounds();
		return _objBound.intersects(anotherObj->_objBound);
	}

	bool Object::getCollision(sf::RectangleShape& anotherObj)
	{
		sf::FloatRect anotherObjBounds = anotherObj.getGlobalBounds();
		return _objBound.intersects(anotherObjBounds);
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

	void Object::increaseSpeed(float factor)
	{
		_objMovingSpeed *= factor;
	}

	void Object::draw()
	{
		_owner.draw(_obj);
	}

	void Object::increaseVerticalHeight(float amount)
	{
		this->setHeight(amount);
	}

	void Object::reverseHorizontalDirection()
	{
		_objMovingSpeed *= -1.f;
	}

	void Object::reverseVerticalDirection()
	{
		_objVerticalHeight *= -1.f;
	}

}