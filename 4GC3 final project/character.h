#ifndef CHARACTER_H
#define CHARACTER_H

#include "stdafx.h"
class level;
/*
	This is the class that is being used to allow
	movement in the world, and view the sounds 
	that are generated from the source
*/
class character 
{
	private:
		float2D _position;
		float2D _direction;
		
		int		_size;
		float	_viewAngle;
		int		_maxSpeed;
		int		_speed = 0;
		
		int2D	_vertexData[12];
		float3D _colorData[12];
		int2D	_corners[4];

		void	_updateDirection();
		void	_initializeTile();
		void	_updateVertexData();

		void	_setMovement(int directionFlag, bool movementFlag);

		bool	_isDirty = false;
		bool	_checkForCollisions(level &currentLevel);

		int _frameLimit = 1000 / 45;
		int _previousTime = GetTickCount64();

		int _turnTime = GetTickCount64();

	public:
		character();
		character(float2D position);
		character(float2D position, float angle);
		character(float2D position, float angle, int size);

		void incrementAngle(float amount, level &currentLevel);
		void decrementAngle(float amount, level &currentLevel);
		
		void setMoveForward();
		void setMoveReverse();
		void stopMoving();

		void setSpeed(int speed);

		void move(level &currentLevel);
		void render(void);

		float2D getPosition(void) const;
		int getSpeed(void) const;
		float getViewAngle(void) const;
		int getSize(void) const;
		bool isPointInsideCharacter(int2D pointOne, int2D pointTwo, level &currentLevel);
};

#endif