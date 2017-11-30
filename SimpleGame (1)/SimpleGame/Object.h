#pragma once
class Object
{
public:
	Object();
	Object(float x, float y,int objecttype);
	Object(float x, float y, int objecttype, int friendnumber);
	~Object();
public:
	inline void SetPostionXYZ(float x, float y, float z) { m_x = x, m_y = y, m_z = z; }
	inline void SetSize(float size) { m_size = size; }
	inline void SetRGBA(float r, float g, float b, float a) { m_r = a, m_g = g, m_b = b, m_a = a; }
	inline void SetLife(float Life) { m_Life = Life; }
	inline void SetLifeTime(float LifeTime) { m_LifeTime = LifeTime; }
	inline void SetTimer(DWORD Timer) { m_objectTimer = Timer; }
	//inline void SetChracterTimer(DWORD Timer) { m_chracterTimer = Timer; }
	inline void SetChracterTime(float time) { m_ChracterLastTime = time; }
	inline void SetMyFriend(int friendnumber) { m_myFriend = friendnumber; };
	inline void SetMyLastBulletTime(float time) { m_bulletLastTime = time; };
	inline void SetMyLastArrowTime(float time) { m_ArrowLastTime = time; };
	inline float GetPositionX(void) { return m_x; }
	inline float GetPositionY(void) { return m_y; }
	inline float GetPositionZ(void) { return m_z; }
	inline float GetR(void) { return m_r; }
	inline float GetG(void) { return m_g; }
	inline float GetB(void) { return m_b; }
	inline float GetA(void) { return m_a; }
	inline float GetSize(void) { return m_size; };
	inline float GetLife(void) { return m_Life; };
	inline float GetLifeTime(void) { return m_LifeTime; };
	inline int GetObjectType(void) { return m_type; };
	inline DWORD GetObjectTimer(void) { return m_objectTimer; };
	//inline DWORD GetCharacterTimer(void) { return m_chracterTimer; };
	inline float GetCharacterTime(void) { return m_ChracterLastTime; };
	inline int GetMyFriend(void) { return m_myFriend; };
	inline int GetMyTEAM(void) { return m_TeamNumber; };
	inline float GetBulletTime(void) { return m_bulletLastTime; };
	inline float GetArrowTime(void) { return m_ArrowLastTime; };
	void PositionUpdate(float xvector, float yvector, DWORD time);
private:
	float m_x;
	float m_y;
	float m_z;
	float m_size;
	float m_r;
	float m_g;
	float m_b;
	float m_a;

	float m_Speed;
	char*  m_name;
	float m_Life;
	float m_LifeTime;
	int	  m_type;
	int   m_myFriend;
	int   m_TeamNumber;
	DWORD m_objectTimer;
	DWORD m_chracterTimer;
	float m_bulletLastTime;
	float m_ArrowLastTime;
	float m_ChracterLastTime;
	float m_AnimationTime;
public:
	float m_RenderLevel;
	int   m_AnimationFrame;  //max 16
	float m_BulletAnimationTime;
	float m_Vx;
	float m_Vy;
};

