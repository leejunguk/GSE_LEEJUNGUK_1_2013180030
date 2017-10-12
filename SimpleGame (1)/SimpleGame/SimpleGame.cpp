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
//

#include "Renderer.h"

Renderer *g_Renderer = NULL;
Object *g_Object = NULL;
Object *mousobj = NULL;
Object *objectlist[1000];
static float frame;
static int objnum = 0;

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.3f, 0.3f, 1.0f);

	
	// Renderer Test
	
	g_Object->PositionUpdate(2.1f, 5.1f, frame);
	g_Renderer->DrawSolidRect(g_Object->GetPositionX(), g_Object->GetPositionY(), g_Object->GetPositionZ(), g_Object->GetSize(), 
		                      g_Object->GetR(), g_Object->GetG(), g_Object->GetB(), g_Object->GetA());
	for (int i = 0; i < objnum; ++i)
	{
		objectlist[i]->PositionUpdate(5.1f, 0.f, frame);
		g_Renderer->DrawSolidRect(objectlist[i]->GetPositionX(), objectlist[i]->GetPositionY(), objectlist[i]->GetPositionZ()
		, objectlist[i]->GetSize(),objectlist[i]->GetR(), objectlist[i]->GetG(), objectlist[i]->GetB(), objectlist[i]->GetA());
		
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
	Object* mousobj = new Object(x-250, -y+ 250,0);
	mousobj->SetSize(5.f);
	mousobj->SetRGBA(1, 1, 1, 1);
	objectlist[objnum++] = mousobj;
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

	g_Object = new Object;
	g_Object->SetPostionXYZ(10, 10, 10);
	g_Object->SetRGBA(1, 1, 0, 1);
	g_Object->SetSize(100);
	

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

