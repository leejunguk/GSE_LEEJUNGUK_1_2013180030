#pragma once
class Object
{
public:
	Object();
	~Object();
public:
	inline void SetPostionXYZ(float x, float y, float z) { m_x = x, m_y = y, m_z = z; }
	inline void SetSize(float size) { m_size = size; }
	inline void SetRGBA(float r, float g, float b, float a) { m_r = a, m_g = g, m_b = b, m_a = a; }
	inline float GetPositionX(void) { return m_x; }
	inline float GetPositionY(void) { return m_y; }
	inline float GetPositionZ(void) { return m_z; }
	inline float GetR(void) { return m_r; }
	inline float GetG(void) { return m_g; }
	inline float GetB(void) { return m_b; }
	inline float GetA(void) { return m_a; }
	inline float GetSize(void) { return m_size; };
	void PositionUpdate(float xvector, float yvector,float time);
private:
	float m_x;
	float m_y;
	float m_z;
	float m_size;
	float m_r;
	float m_g;
	float m_b;
	float m_a;
	char*  m_name;
};

