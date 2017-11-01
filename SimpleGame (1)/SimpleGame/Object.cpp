#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_Life = 100.f;
	m_LifeTime = 100000.f;
}

Object::Object(float x, float y)
{
	m_Life = 100.f;
	m_LifeTime = 100000.f;
	m_x = x, m_y = y;
	m_size = 20;
	m_r = 0;
	m_g = 0;
	m_b = 0;
	m_a = 1;
	m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
	m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
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
	//m_size = 20 * sin(m_x);
	m_size = 20;
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