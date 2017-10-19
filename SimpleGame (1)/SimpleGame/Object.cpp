#include "stdafx.h"
#include "Object.h"


Object::Object()
{
}

Object::Object(float x, float y,float z)
{
	m_x = x, m_y = y;
	m_Vx = 1; 
	m_Vy = 1;
}

Object::~Object()
{
}
void Object::PositionUpdate(float xvector, float yvector, float time)
{
	m_x = m_x + m_Vx *(xvector * time);
	m_y = m_y + m_Vy *(yvector * time);
	m_size = 10 * sin(m_x);
	if ( m_x > 250)
	{
		m_Vx = - m_Vx;
	}
	if (m_x < -250)
	{
		m_Vx = -m_Vx;
	}
	if (m_y > 250)
	{
		m_Vy = -m_Vy;
	}
	if (m_y < -250)
	{
		m_Vy = -m_Vy;
	}
}