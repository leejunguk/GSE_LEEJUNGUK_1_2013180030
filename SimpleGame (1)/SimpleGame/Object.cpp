#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_Life = 100;
}

Object::Object(float x, float y,float z)
{
	m_x = x, m_y = y;
	m_Vx = 1; 
	m_Vy = 1;
}

Object::~Object()
{
	//if (m_Life < 0)
	//	delete this;
}
void Object::PositionUpdate(float xvector, float yvector, DWORD time)
{
	float elapsetime = (float)time * 0.001f;

	m_x = m_x + m_Vx *(xvector * elapsetime);
	m_y = m_y + m_Vy *(yvector * elapsetime);
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