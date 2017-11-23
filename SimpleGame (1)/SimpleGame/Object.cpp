#include "stdafx.h"
#include "Object.h"


Object::Object()
{
	m_Life = 100.f;
	m_LifeTime = 100000.f;
	m_objectTimer = 0.00000f;
	m_bulletLastTime = 0.f;
	m_ArrowLastTime = 0.f;
	m_ChracterLastTime = 0.f;
}
Object::Object(float x, float y,int objecttype)
{
	m_bulletLastTime = 0.f;
	m_ArrowLastTime = 0.f;
	m_objectTimer = 0.00000f;
	m_ChracterLastTime = 0.f;
	if (objecttype == OBJECT_BULDING)
	{
		m_type = OBJECT_BULDING;
		m_x = 0, m_y = 0;
		m_Life = 500.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1,1,0,1);
		m_LifeTime = 100000.f;
		m_RenderLevel = RenderLevel_BULDING;
		return;
	}
	else if (objecttype == OBJECT_CHARACTER)
	{
		m_type = OBJECT_CHARACTER;
		
		m_Life = 100.f;
		m_Speed = 300.f;
		m_size = 30.f;
		m_r = 1.f;
		m_g = 1.f;
		m_b = 1;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}
	else if (objecttype == OBJECT_BULLET)
	{
		m_type = OBJECT_BULLET;
	
		m_Life = 15.f;
		m_Speed = 600.f;
		m_size = 4.f;
		m_r = 1.f;
		m_g = 0;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_RenderLevel = RenderLevel_BULLET;
		return;
	}
	else if (objecttype == OBJECT_ARROW)
	{
		m_type = OBJECT_ARROW;

		m_Life = 10.f;
		m_Speed = 100.f;
		m_size = 4.f;
		m_r = 0;
		m_g = 1.f;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_RenderLevel = RenderLevel_ARROW;
		return;
	}
	
	
	

}

Object::Object(float x, float y, int objecttype,int TeamNumber)
{
	m_objectTimer = 0.00000f;
	m_chracterTimer = 0.000000f;
	m_myFriend = TeamNumber;
	m_bulletLastTime = 0.f;
	m_ArrowLastTime = 0.f;
	m_ChracterLastTime = 0.f;
	if (objecttype == OBJECT_BULDING && TeamNumber == ATEAM)
	{
		m_type = OBJECT_BULDING;
		m_x = x, m_y = y;
		m_Life = 500.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1, 1, 0, 1);
		m_LifeTime = 100000.f;
		m_TeamNumber = ATEAM;
		m_RenderLevel = RenderLevel_BULDING;
		return;
	}
	else if (objecttype == OBJECT_BULDING && TeamNumber == BTEAM)
	{
		m_type = OBJECT_BULDING;
		m_x = x, m_y = y;
		m_Life = 500.f;
		m_Speed = 0.f;
		m_size = 100.f;
		m_r = 1;
		m_g = 1;
		m_b = 0;
		m_a = 1;
		SetRGBA(1, 1, 0, 1);
		m_LifeTime = 100000.f;
		m_TeamNumber = BTEAM;
		m_RenderLevel = RenderLevel_BULDING;
		return;
	}
	else if (objecttype == OBJECT_CHARACTER && TeamNumber == ATEAM)
	{
		m_type = OBJECT_CHARACTER;

		m_Life = 100.f;
		m_Speed = 300.f;
		m_size = 30.f;
		m_r = 1.f;
		m_g = 0.f;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = ATEAM;
		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}
	else if (objecttype == OBJECT_CHARACTER && TeamNumber == BTEAM)
	{
		m_type = OBJECT_CHARACTER;

		m_Life = 100.f;
		m_Speed = 300.f;
		m_size = 30.f;
		m_r = 0.f;
		m_g = 0.f;
		m_b = 1;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = BTEAM;
		m_RenderLevel = RenderLevel_CHARACTER;
		return;
	}
	else if (objecttype == OBJECT_BULLET && TeamNumber == ATEAM)
	{
		m_type = OBJECT_BULLET;

		m_Life = 15.f;
		m_Speed = 600.f;
		m_size = 4.f;
		m_r = 1.f;
		m_g = 0;
		m_b = 0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_RenderLevel = RenderLevel_BULLET;
		m_TeamNumber = ATEAM;
		return;
	}
	else if (objecttype == OBJECT_BULLET && TeamNumber == BTEAM)
	{
		m_type = OBJECT_BULLET;

		m_Life = 15.f;
		m_Speed = 600.f;
		m_size = 4.f;
		m_r = 0.f;
		m_g = 0;
		m_b = 1;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = BTEAM;
		m_RenderLevel = RenderLevel_BULLET;
		return;
	}
	else if (objecttype == OBJECT_ARROW&& TeamNumber == ATEAM)
	{
		m_type = OBJECT_ARROW;

		m_Life = 10.f;
		m_Speed = 100.f;
		m_size = 4.f;
		m_r = 0.5f;
		m_g = 0.2f;
		m_b = 0.7;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = ATEAM;
		m_RenderLevel = RenderLevel_ARROW;
		return;
	}
	else if (objecttype == OBJECT_ARROW&& TeamNumber == BTEAM)
	{
		m_type = OBJECT_ARROW;

		m_Life = 10.f;
		m_Speed = 100.f;
		m_size = 4.f;
		m_r = 1.0f;
		m_g = 1.0f;
		m_b = 0.0;
		m_a = 1;
		m_LifeTime = 100000.f;
		m_x = x, m_y = y;
		m_Vx = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_Vy = 50.f *(((float)std::rand() / (float)RAND_MAX) - 0.5f);
		m_TeamNumber = BTEAM;
		m_RenderLevel = RenderLevel_ARROW;
		return;
	}



}



Object::~Object()
{
	//if (m_Life < 0)
	//	delete this;
}
void Object::PositionUpdate(float xvector, float yvector, DWORD time)
{
	float elapsetime = (float)time * 0.00001f;

	m_bulletLastTime += elapsetime;
	m_ArrowLastTime += elapsetime;
	m_ChracterLastTime += elapsetime;
	m_x = m_x + m_Vx *(xvector * elapsetime) * m_Speed;
	m_y = m_y + m_Vy *(yvector * elapsetime) * m_Speed;
	//m_size = 20 * sin(m_x);
	//m_size = 20;
	if ( m_x > SIZEWINDOWWIDTH /2)
	{
		m_Vx = - m_Vx;
		
	}
	if (m_x < -(SIZEWINDOWWIDTH / 2))
	{
		m_Vx = -m_Vx;
		
	}
	if (m_y > SIZEWINDOWHEIGHT/2)
	{
		m_Vy = -m_Vy;
		
	}
	if (m_y < -(SIZEWINDOWHEIGHT / 2))
	{
		m_Vy = -m_Vy;
		
	}
	
}