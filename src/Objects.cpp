#include <Objects.h>

namespace physics {
	void Object::setPos(float x, float y)
	{
		_obj.setPosition(x, y);
	}
	bool Object::getCollision(sf::RectangleShape anotherObj)
	{
		sf::FloatRect objBound = _obj.getGlobalBounds();
		sf::FloatRect anotherObjBound = anotherObj.getGlobalBounds();
		return objBound.intersects(anotherObjBound);
	}
	bool Object::isCollisionUpperWall()
	{
		sf::FloatRect objBound = _obj.getGlobalBounds();
		return (objBound.top >= _owner.getSize().y);
	}
}