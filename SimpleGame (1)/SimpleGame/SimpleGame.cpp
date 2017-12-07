/*
Copyright 2017 Lee Taek Hee (Korea Polytech University)

This program is free software: you can redistribute it and/or modify
it under the terms of the What The Hell License. Do it plz.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY.
*/

#include "stdafx.h"
#include <iostream>
#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

//오브젝트 추가 코드
#include "Object.h"
#include "SceneMgr.h"
//
#include "Sound.h"
#include "Renderer.h"

Renderer *g_Renderer;
Object *g_Object = NULL;
//Object *mousobj = NULL;

SceneMgr* g_ScenMgr = NULL;

DWORD g_prevTime = NULL;
DWORD ElaspeTime;
float BlueTeamTimer;
//Object *objectlist[1000];
static float frame;
static int objnum = 0;
bool g_LButtonDown;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	static int a = 0;
	a++;
	///////
	DWORD currentTime = timeGetTime();
	ElaspeTime = currentTime - g_prevTime;
	
	BlueTeamTimer += float(ElaspeTime) * 0.00001f;
	//if (currentTime > g_prevTime +15 )
	//{
	//	g_ScenMgr->AddObjectList(0, 0, OBJECT_BULLET); //\dhfb
	//	g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);
	//}

	
	
	//elsapse time curr time - gprevtime
	//updateall object
	//drawallobejct()

	////
	
	// Renderer Test
	
	/*g_Object->PositionUpdate(2.1f, 5.1f, frame);
	g_Renderer->DrawSolidRect(g_Object->GetPositionX(), g_Object->GetPositionY(), g_Object->GetPositionZ(), g_Object->GetSize(), 
		                      g_Object->GetR(), g_Object->GetG(), g_Object->GetB(), g_Object->GetA());*/
	
	

	//for (int i = 0; i < g_ScenMgr->GetObjCnt(); ++i)
	//{
	//	/*g_ScenMgr->m_objectList[i]->PositionUpdate(100.1f, 100.1f, ElaspeTime);*/
	//	
	//	g_Renderer->DrawSolidRect(g_ScenMgr->m_objectList[i]->GetPositionX(), g_ScenMgr->m_objectList[i]->GetPositionY(), g_ScenMgr->m_objectList[i]->GetPositionZ()
	//	, g_ScenMgr->m_objectList[i]->GetSize(), g_ScenMgr->m_objectList[i]->GetR(), g_ScenMgr->m_objectList[i]->GetG(), g_ScenMgr->m_objectList[i]->GetB(), g_ScenMgr->m_objectList[i]->GetA());
	//	
	//}
	g_ScenMgr->Update(1.0f, 1.0f, ElaspeTime);
	g_ScenMgr->Render();

	g_prevTime = currentTime;
	glutSwapBuffers();
}

void Idle(void)
{
	RenderScene();
}

void MouseInput(int button, int state, int x, int y)
{
	RenderScene();
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		g_LButtonDown = true;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && g_LButtonDown == true)
	{

		//\dhfb
		if (-400 <= (-y + SIZEWINDOWHEIGHT / 2) && (-y + SIZEWINDOWHEIGHT / 2) <= 0 &&BlueTeamTimer >0.07f)
		{
			g_ScenMgr->AddObjectList(x - SIZEWINDOWWIDTH / 2, -y + SIZEWINDOWHEIGHT / 2, OBJECT_CHARACTER,BTEAM);
			g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);
			BlueTeamTimer = 0.f;
			
		}
		else
		{

		}
		g_LButtonDown = false;
	}
	
}

void KeyInput(unsigned char key, int x, int y)
{
	RenderScene();
}

void SpecialKeyInput(int key, int x, int y)
{
	RenderScene();
}

int main(int argc, char **argv)
{
	// Initialize GL things
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(SIZEWINDOWWIDTH, SIZEWINDOWHEIGHT);
	glutCreateWindow("Game Software Engineering KPU");
	
	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	g_ScenMgr = new SceneMgr;
	// Initialize Renderer
	/*g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}*/

	//사운드 생성 
	Sound* m_sound = new Sound();

	int soundBG = m_sound->CreateSound("./Dependencies/SoundSamples/ShapeOfYou.mp3");

	m_sound->PlaySound(soundBG, true, 0.2f);



	//ATEAM 왼쪽 상단건물
	g_ScenMgr->AddObjectList(-200, 300, OBJECT_BULDING,ATEAM); //\dhfb
	g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);
	frame = 1;
	//ATEAM 중앙 상단건물
	g_ScenMgr->AddObjectList(0, 300, OBJECT_BULDING, ATEAM); //\dhfb
	g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);

	//ATEAM 오른쪽 상단 건물
	g_ScenMgr->AddObjectList(200, 300, OBJECT_BULDING, ATEAM); //\dhfb
	g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);


	//===================================================================BTEAM

	//BTEAM 왼쪽 하단건물
	g_ScenMgr->AddObjectList(-200, -300, OBJECT_BULDING, BTEAM); //\dhfb
	g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);
	frame = 1;
	//BTEAM 중앙 하단건물
	g_ScenMgr->AddObjectList(0, -300, OBJECT_BULDING, BTEAM); //\dhfb
	g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);

	//BTEAM 오른쪽 하단 건물
	g_ScenMgr->AddObjectList(200, -300, OBJECT_BULDING, BTEAM); //\dhfb
	g_ScenMgr->SetObjCnt(g_ScenMgr->GetObjCnt() + 1);
	

	g_ScenMgr->m_texCharacter = g_Renderer->CreatePngTexture("Texture/bunker.png");
	g_ScenMgr->m_airCharacter = g_Renderer->CreatePngTexture("Texture/Building.png");
	g_ScenMgr->m_BakcGround = g_Renderer->CreatePngTexture("Texture/Background.png");
	g_ScenMgr->m_CharaterAnimation = g_Renderer->CreatePngTexture("Texture/Rockman.png");
	g_ScenMgr->m_Paticle = g_Renderer->CreatePngTexture("Texture/Particle.png");
	//초기화


	//Text 추가 
	//g_Renderer->DrawTextW
	

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	

	g_prevTime = timeGetTime();

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

