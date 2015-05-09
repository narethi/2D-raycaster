#ifndef _4GC3_FINAL_PROJECT
#define _4GC3_FINAL_PROJECT

#include "stdafx.h"
#include "character.h"
#include "Level.h"
#include "Ray.h"
#include "light.h"


character testCharacter(float2D(80, 80), 0, 16);
level testLevel(int2D(30, 30), 32);
int2D viewPortOffset = int2D(-90, -90);
int2D viewPortSize(100, 100);

bool keys[4];
/*
	checkViewPort checks if the character is on
	the edge of the view port, if it is then
	move the view port offset to force the
	character in to the viewport area
*/

bool checkViewPort(void)
{
	if((testCharacter.getPosition().getX() - viewPortOffset.getX()) > 0.70*glutGet(GLUT_WINDOW_WIDTH))
	{
		viewPortOffset = viewPortOffset + int2D(abs(testCharacter.getSpeed()), 0);
		return true;
	}
	else if((testCharacter.getPosition().getX() - viewPortOffset.getX()) < 0.30*glutGet(GLUT_WINDOW_WIDTH))
	{
		viewPortOffset = viewPortOffset - int2D(abs(testCharacter.getSpeed()), 0);
		return true;
	}
	if((testCharacter.getPosition().getY() - viewPortOffset.getY()) > 0.70*glutGet(GLUT_WINDOW_HEIGHT))
	{
		viewPortOffset = viewPortOffset + int2D(0, abs(testCharacter.getSpeed()));
		return true;
	}
	else if((testCharacter.getPosition().getY() - viewPortOffset.getY()) < 0.30*glutGet(GLUT_WINDOW_HEIGHT))
	{
		viewPortOffset = viewPortOffset - int2D(0, abs(testCharacter.getSpeed()));
		return true;
	}
	return false;
}

void checkKeys()
{
	if(keys[0])
		testCharacter.setMoveForward();
	else if(keys[1])
		testCharacter.setMoveReverse();
	else
		testCharacter.stopMoving();
	if(keys[2])
		testCharacter.decrementAngle((PI / 90), testLevel);
	if(keys[3])
		testCharacter.incrementAngle((PI / 90), testLevel);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(viewPortOffset.getX(), glutGet(GLUT_SCREEN_WIDTH) + viewPortOffset.getX(),
			   viewPortOffset.getY(), glutGet(GLUT_SCREEN_HEIGHT) + viewPortOffset.getY());
	glViewport(0, 0,
		glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));

	
	testLevel.renderLevel(testCharacter, testLevel);
	

	glutSwapBuffers();
	glFlush();
}

void idle(void)
{
	testCharacter.move(testLevel);
	checkViewPort();
	checkKeys();
	glutPostRedisplay();
}

void reshape(int x, int y)
{
	glutPostRedisplay();
}

void initializeGlut(int argc, char *argv[], string windowName)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow(&windowName[0]);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.1, 0.1, 0.1, 0);

	gluOrtho2D(viewPortOffset.getX(), glutGet(GLUT_SCREEN_WIDTH) + viewPortOffset.getX(),
		viewPortOffset.getY(), glutGet(GLUT_SCREEN_HEIGHT) + viewPortOffset.getY());
	glViewport(0, 0,
		glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
	while(checkViewPort());
}

void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w':
		case 'W':
			keys[0] = true;
			keys[1] = false;
			break;
		case 's':
		case 'S':
			keys[1] = true;
			keys[0] = false;
			break;
		case 'd':
		case 'D':
			keys[2] = true;
			keys[3] = false;
			break;
		case 'a':
		case 'A':
			keys[3] = true;
			keys[2] = false;
			break;
		case '1':
			testLevel.changeColorModel(1);
			break;
		case '2':
			testLevel.changeColorModel(2);
			break;
		case '3':
			testLevel.changeColorModel(3);
			break;
		case '4':
			testLevel.changeColorModel(4);
			break;
		//This is the flash light model
		case '5':
			testLevel.changeColorModel(5);
			break;
	}
}


void keyboardUp(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'w':
		case 'W':
			keys[0] = false;
			break;
		case 's':
		case 'S':
			keys[1] = false;
			break;
		case 'd':
		case 'D':
			keys[2] = false;
			break;
		case 'a':
		case 'A':
			keys[3] = false;
			break;
	}
}

void main(int argc, char *argv[])
{
	cout << "program started please wait for the light volume to be populated" << endl;
	testLevel.buildLevel();
	testLevel.changeColorModel(5);
	testLevel.buildLightVolume(testLevel, testCharacter);
	
	setUpAudio();

	initializeGlut(argc, argv, "Ray caster");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutReshapeFunc(reshape);
	glutMainLoop();
}

#endif