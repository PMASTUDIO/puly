#include "Collision.h"
#include "../objects/GameObject.h"

namespace Puly {

	bool CheckRectCollision2D(GameObject& one, GameObject& two)
	{
		// X-Axis
		bool collisionX = one.m_Position.x + one.m_Scale.x >= two.m_Position.x &&
			two.m_Position.x + two.m_Scale.x >= one.m_Position.x;

		// Y-Axis
		bool collisionY = one.m_Position.y + one.m_Scale.y >= two.m_Position.y &&
			two.m_Position.y + two.m_Scale.y >= one.m_Position.y;

		return collisionX && collisionY;
	}

}