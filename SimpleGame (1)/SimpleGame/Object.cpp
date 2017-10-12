#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(float x, float y,float z)
{
	m_x = x, m_y = y;
}

Object::~Object()
{
}
void Object::PositionUpdate(float xvector, float yvector, float time)
{
	m_x = m_x + (xvector * time);
	m_y = m_y + (yvector * time);
}