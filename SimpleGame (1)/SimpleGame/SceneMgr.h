#pragma once
#include "Object.h"
#include "Renderer.h"
#include "Sound.h"


class SceneMgr
{
public:
	SceneMgr();
	~SceneMgr();
public:
	Object* m_objectList[MAX_OBJECTS_COUNT];
	Object* m_Climate; // 날씨 시간카운트때매
	Object* m_Command; // 커맨드 시간 카운드 

	Sound* m_Scenesound;
	Sound* m_effectSound;

	int Sound_MutalDeath;
	int Sound_MarineBirth;
	int Sound_MutalBirth;
	int Sound_MainreFire;
	int Sound_MarineDeath;
	int Sound_ScourgeBirth;
	int Sound_ScourgeDeath;
	//int Sound_MarineDeath;
private:
	int		m_objectCnt;
	Renderer *m_Renderer;
	
public:
	void Update(float xvector, float yvector, DWORD time);
	void Render();
	bool CollisionCheck(Object *a, Object *b);
	void CollisionCheckList();
	bool AttackBoundaryCheck(Object *a, Object *b);
	int	 AddObjectList(float x, float y,int objecttype);
	int	 AddObjectList(float x, float y, int objecttype, int friendnumber);
	void DeleteObject(int index);
	void DeleteOlderObject();
	GLuint m_texCharacter;
	GLuint m_airCharacter;
	GLuint m_BakcGround;
	GLuint m_CharaterAnimation;
	GLuint m_Paticle;
	GLuint m_snow;
	GLuint m_Spire;
	GLuint m_Barrack;
	GLuint m_Marine;
	GLuint m_MutalDeathEffect;
	GLuint m_LifleEffect;
	GLuint m_MutalBullet;
	GLuint m_Scourge;
	GLuint m_ScourgeEffect;
	GLuint m_MarineEffect;
	GLuint m_MainImage;
	GLuint m_GameOver;
	float m_ClimateAnimationTime;
	float m_CommandAnimationTime;
	bool isGameEnd;
public:
	inline void SetObjCnt(int cnt) { m_objectCnt = cnt; };
	inline int GetObjCnt() { return m_objectCnt; };
};

