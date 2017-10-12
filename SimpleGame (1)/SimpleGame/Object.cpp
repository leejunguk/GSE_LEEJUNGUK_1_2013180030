#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}


Object::~Object()
{
}
void Object::PositionUpdate(float xvector, float yvector, float time)
{
	m_x = m_x + (xvector * time);
	m_y = m_y + (yvector * time);
}