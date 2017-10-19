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

#include "Renderer.h"

Renderer *g_Renderer = NULL;
Object *g_Object = NULL;
//Object *mousobj = NULL;

SceneMgr* g_ScenMgr;

//Object *objectlist[1000];
static float frame;
static int objnum = 0;
bool g_LButtonDown;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	
	// Renderer Test
	
	/*g_Object->PositionUpdate(2.1f, 5.1f, frame);
	g_Renderer->DrawSolidRect(g_Object->GetPositionX(), g_Object->GetPositionY(), g_Object->GetPositionZ(), g_Object->GetSize(), 
		                      g_Object->GetR(), g_Object->GetG(), g_Object->GetB(), g_Object->GetA());*/
	
	//g_ScenMgr->Update(5.1f, 5.1f, frame);

	for (int i = 0; i < g_ScenMgr->m_objcctCnt; ++i)
	{
		g_ScenMgr->m_objectList[i]->PositionUpdate(5.1f, 5.1f, frame);

		g_Renderer->DrawSolidRect(g_ScenMgr->m_objectList[i]->GetPositionX(), g_ScenMgr->m_objectList[i]->GetPositionY(), g_ScenMgr->m_objectList[i]->GetPositionZ()
		, g_ScenMgr->m_objectList[i]->GetSize(), g_ScenMgr->m_objectList[i]->GetR(), g_ScenMgr->m_objectList[i]->GetG(), g_ScenMgr->m_objectList[i]->GetB(), g_ScenMgr->m_objectList[i]->GetA());
		
	}

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
		Object* mousobj = new Object(x - 250, -y + 250, 0);
		mousobj->SetSize(5.f);
		mousobj->SetRGBA(1, 1, 1, 1);
		g_ScenMgr->m_objectList[g_ScenMgr->m_objcctCnt++] = mousobj; //\dhfb
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
	glutInitWindowSize(500, 500);
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

	// Initialize Renderer
	g_Renderer = new Renderer(500, 500);
	if (!g_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}

	frame = 1;

	//g_Object = new Object;
	//g_Object->SetPostionXYZ(10, 10, 10);
	//g_Object->SetRGBA(1, 1, 0, 1);
	//g_Object->SetSize(100);
	
	g_ScenMgr = new SceneMgr;


	//초기화

	glutDisplayFunc(RenderScene);
	glutIdleFunc(Idle);
	glutKeyboardFunc(KeyInput);
	glutMouseFunc(MouseInput);
	glutSpecialFunc(SpecialKeyInput);
	

	glutMainLoop();

	delete g_Renderer;

    return 0;
}

