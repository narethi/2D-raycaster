#ifndef CHARACTER_M
#define CHARACTER_M

#include "character.h"
#include "level.h"
#include "Point2D.h"

character::character(float2D position, float viewAngle, int size) :
_position(position), _viewAngle(viewAngle), _size(size), _maxSpeed(1)
{
	_updateDirection();
	_initializeTile();
}

character::character(float2D position, float viewAngle) :
character(position, viewAngle, 10) {}

character::character(float2D position) :
character(position, 0, 10) {}

character::character() : character(float2D(15, 15), 0, 10) {}

void character::_initializeTile()
{
	/*
		now that we have the corners set up the colors
		for each face, where
		red is front
		blue is right
		green is back
		yellow is left
	*/
	float3D front(1, 0, 0);
	float3D right(0, 0, 1);
	float3D back(1, 1, 0);
	float3D left(0, 1, 0);
	//Next update the triangle positions
	_updateVertexData();
	//Now color each set of points with the right color
	for(int i = 3; i--;)
	{
		_colorData[i] = front;
		_colorData[3 + i] = right;
		_colorData[6 + i] = back;
		_colorData[9 + i] = left;
	}
}

void character::render()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, &_colorData[0]);
	glVertexPointer(2, GL_INT, 0, &_vertexData[0]);
	glDrawArrays(GL_TRIANGLES, 0, 12);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

int character::getSize(void) const
{
	return _size;
}

bool character::isPointInsideCharacter(int2D pointOne, int2D pointTwo, level &currentLevel)
{
	//First check to see if the rays are with in the array of the square
	//There are 4 situations 
	//above the square
	if(pointOne.getY() > _position.getY() + _size  && pointTwo.getY() > _position.getY() + _size) return false;
	//below the square
	if(pointOne.getY() < _position.getY() - _size  && pointTwo.getY() < _position.getY() - _size) return false;
	//to the right
	if(pointOne.getX() > _position.getX() + _size  && pointTwo.getX() > _position.getX() + _size) return false;
	//to the left
	if(pointOne.getX() < _position.getX() - _size  && pointTwo.getX() < _position.getX() - _size) return false;
	//

	/*
		To do this we are going to check the intersection with each face
		this is going to be used in the flash light model and the raycasted
		sound model
		so we need to test each side where
		1 0
		2 3
	*/
	//line 1 upper left to upper right
	float xDeltaIn = pointTwo.getX() - pointOne.getX();
	float xDeltaSelf = _corners[0].getX() - _corners[1].getX();
	float yDeltaIn = pointTwo.getY() - pointOne.getY();
	float yDeltaSelf = _corners[0].getY() - _corners[1].getY();
	float s, t;
	s = (-yDeltaIn * (pointOne.getX() - _corners[1].getX()) + xDeltaIn*(pointOne.getY() - _corners[1].getY())) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	t = (xDeltaSelf * (pointOne.getY() - _corners[1].getY()) - yDeltaSelf*(pointOne.getX() - _corners[1].getX())) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	float intersectX, intersectY;
	if( s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		currentLevel._addToSide[1] = true;
		return true;
	}
	
	//line 2 upper right to lower right
	xDeltaSelf = _corners[1].getX() - _corners[2].getX();
	yDeltaSelf = _corners[1].getY() - _corners[2].getY();
	s = (-yDeltaIn * (pointOne.getX() - _corners[2].getX()) + xDeltaIn*(pointOne.getY() - _corners[2].getY())) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	t = (xDeltaSelf * (pointOne.getY() - _corners[2].getY()) - yDeltaSelf*(pointOne.getX() - _corners[2].getX())) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		currentLevel._addToSide[2] = true;
		return true;
	}

	//line 3 lower right to lower left
	xDeltaSelf = _corners[2].getX() - _corners[3].getX();
	yDeltaSelf = _corners[2].getY() - _corners[3].getY();
	s = (-yDeltaIn * (pointOne.getX() - _corners[3].getX()) + xDeltaIn*(pointOne.getY() - _corners[3].getY())) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	t = (xDeltaSelf * (pointOne.getY() - _corners[3].getY()) - yDeltaSelf*(pointOne.getX() - _corners[3].getX())) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		currentLevel._addToSide[3] = true;
		return true;
	}
	
	//line 5 lower right to upper left
	xDeltaSelf = _corners[3].getX() - _corners[0].getX();
	yDeltaSelf = _corners[3].getY() - _corners[0].getY();
	s = (-yDeltaIn * (double(pointOne.getX() - _corners[0].getX())) + xDeltaIn*(double(pointOne.getY() - _corners[0].getY()))) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	t = (xDeltaSelf * (double(pointOne.getY() - _corners[0].getY())) - yDeltaSelf*(double(pointOne.getX() - _corners[0].getX()))) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		//currentLevel._addToSide[1] = true;
		//currentLevel._addToSide[3] = true;
		currentLevel._addToSide[0] = true;
		return true;
	}

	//line 4 lower right to lower left
	xDeltaSelf = _corners[3].getX() - _corners[1].getX();
	yDeltaSelf = _corners[3].getY() - _corners[1].getY();
	s = (-yDeltaIn * (double(pointOne.getX() - _corners[1].getX())) + xDeltaIn*(double(pointOne.getY() - _corners[1].getY()))) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	t = (xDeltaSelf * (double(pointOne.getY() - _corners[1].getY())) - yDeltaSelf*(double(pointOne.getX() - _corners[1].getX()))) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		return true;
	}

	//line 6 lower right to lower left
	xDeltaSelf = _corners[0].getX() - _corners[2].getX();
	yDeltaSelf = _corners[0].getY() - _corners[2].getY();
	s = (-yDeltaIn * (double(pointOne.getX() - _corners[2].getX())) + xDeltaIn*(double(pointOne.getY() - _corners[2].getY()))) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	t = (xDeltaSelf * (double(pointOne.getY() - _corners[2].getY())) - yDeltaSelf*(double(pointOne.getX() - _corners[2].getX()))) / (-xDeltaSelf*yDeltaIn + xDeltaIn*yDeltaSelf);
	if(s >= 0 && s <= 1 && t >= 0 && t <= 1)
	{
		return true;
	}
	return false;
}

void character::_updateVertexData()
{
	/*
	character tiles are as follows
	there are four corners, and a center,
	_position is the center, and _corners
	are the corners.

	the corners are stored to make the collision
	detection easier, so the first step is to find
	the corners where each corner is 45 degrees
	rotated from the center * the _size of the tile
	*/
	//upper right
	_corners[0] = (float2D().polarRotate(_viewAngle + (PI / 4))*_size) + _position;
	//upper left
	_corners[1] = (float2D().polarRotate(_viewAngle + (3 * PI / 4))*_size) + _position;
	//lower left
	_corners[2] = (float2D().polarRotate(_viewAngle + (5 * PI / 4))*_size) + _position;
	//lower right
	_corners[3] = (float2D().polarRotate(_viewAngle + (7 * PI / 4))*_size) + _position;

	//Update the movement direction
	_updateDirection();
	/*
	Write out the triangles
	*/
	//This is the front face
	_vertexData[0] = _corners[0];
	_vertexData[1] = _corners[1];
	_vertexData[2] = _position;
	//This is the right face
	_vertexData[3] = _corners[0];
	_vertexData[4] = _corners[3];
	_vertexData[5] = _position;
	//This the back face
	_vertexData[6] = _corners[3];
	_vertexData[7] = _corners[2];
	_vertexData[8] = _position;
	//This is the left face
	_vertexData[9] = _corners[1];
	_vertexData[10] = _corners[2];
	_vertexData[11] = _position;
}

void character::_updateDirection(void)
{
	float2D rotationVector = float2D().polarRotate(_viewAngle);
	_direction = rotationVector * _speed;
}

float character::getViewAngle(void) const
{
	return _viewAngle;
}

void character::incrementAngle(float amount, level &currentLevel)
{
	if((GetTickCount64() - _turnTime < _frameLimit)) return;
	_turnTime = GetTickCount64();
	_viewAngle += amount;
	if(_viewAngle >= 2 * PI) _viewAngle -= 2 * PI;
	_updateVertexData();
	//Check each corner to see which corners are sticking
	if(!currentLevel.canPass(_corners[0]))
	{
		if(currentLevel.canPass(_corners[0] + int2D(0, 2)))
			_position = _position + int2D(0, 2);
		else if(currentLevel.canPass(_corners[0] + int2D(0, -2)))
			_position = _position + int2D(0, -2);
		else if(currentLevel.canPass(_corners[0] + int2D(2, 0)))
			_position = _position + int2D(2, 0);
		else if(currentLevel.canPass(_corners[0] + int2D(-2, 0)))
			_position = _position + int2D(-2, 0);
		_updateVertexData();
	}
	if(!currentLevel.canPass(_corners[1]))
	{
		if(currentLevel.canPass(_corners[1] + int2D(0, 2)))
			_position = _position + int2D(0, 2);
		else if(currentLevel.canPass(_corners[1] + int2D(0, -2)))
			_position = _position + int2D(0, -2);
		else if(currentLevel.canPass(_corners[1] + int2D(2, 0)))
			_position = _position + int2D(2, 0);
		else if(currentLevel.canPass(_corners[1] + int2D(-2, 0)))
			_position = _position + int2D(-2, 0);
		_updateVertexData();
	}
	if(!currentLevel.canPass(_corners[2]))
	{
		if(currentLevel.canPass(_corners[2] + int2D(0, 2)))
			_position = _position + int2D(0, 2);
		else if(currentLevel.canPass(_corners[2] + int2D(0, -2)))
			_position = _position + int2D(0, -2);
		else if(currentLevel.canPass(_corners[2] + int2D(2, 0)))
			_position = _position + int2D(2, 0);
		else if(currentLevel.canPass(_corners[2] + int2D(-2, 0)))
			_position = _position + int2D(-2, 0);
		_updateVertexData();
	}
	if(!currentLevel.canPass(_corners[3]))
	{
		if(currentLevel.canPass(_corners[3] + int2D(0, 2)))
			_position = _position + int2D(0, 2);
		else if(currentLevel.canPass(_corners[3] + int2D(0, -2)))
			_position = _position + int2D(0, -2);
		else if(currentLevel.canPass(_corners[3] + int2D(2, 0)))
			_position = _position + int2D(2, 0);
		else if(currentLevel.canPass(_corners[3] + int2D(-2, 0)))
			_position = _position + int2D(-2, 0);
		_updateVertexData();
	}
}


void character::decrementAngle(float amount, level &currentLevel)
{
	if((GetTickCount64() - _turnTime < _frameLimit)) return;
	_turnTime = GetTickCount64();
	_viewAngle -= amount;
	if(_viewAngle < 0) _viewAngle += 2 * PI;
	_updateVertexData();
	if(!currentLevel.canPass(_corners[0]))
	{
		if(currentLevel.canPass(_corners[0] + int2D(0, 2)))
			_position = _position + int2D(0, 2);
		else if(currentLevel.canPass(_corners[0] + int2D(0, -2)))
			_position = _position + int2D(0, -2);
		else if(currentLevel.canPass(_corners[0] + int2D(2, 0)))
			_position = _position + int2D(2, 0);
		else if(currentLevel.canPass(_corners[0] + int2D(-2, 0)))
			_position = _position + int2D(-2, 0);
		_updateVertexData();
	}
	if(!currentLevel.canPass(_corners[1]))
	{
		if(currentLevel.canPass(_corners[1] + int2D(0, 2)))
			_position = _position + int2D(0, 2);
		else if(currentLevel.canPass(_corners[1] + int2D(0, -2)))
			_position = _position + int2D(0, -2);
		else if(currentLevel.canPass(_corners[1] + int2D(2, 0)))
			_position = _position + int2D(2, 0);
		else if(currentLevel.canPass(_corners[1] + int2D(-2, 0)))
			_position = _position + int2D(-2, 0);
		_updateVertexData();
	}
	if(!currentLevel.canPass(_corners[2]))
	{
		if(currentLevel.canPass(_corners[2] + int2D(0, 2)))
			_position = _position + int2D(0, 2);
		else if(currentLevel.canPass(_corners[2] + int2D(0, -2)))
			_position = _position + int2D(0, -2);
		else if(currentLevel.canPass(_corners[2] + int2D(2, 0)))
			_position = _position + int2D(2, 0);
		else if(currentLevel.canPass(_corners[2] + int2D(-2, 0)))
			_position = _position + int2D(-2, 0);
		_updateVertexData();
	}
	if(!currentLevel.canPass(_corners[3]))
	{
		if(currentLevel.canPass(_corners[3] + int2D(0, 2)))
			_position = _position + int2D(0, 2);
		else if(currentLevel.canPass(_corners[3] + int2D(0, -2)))
			_position = _position + int2D(0, -2);
		else if(currentLevel.canPass(_corners[3] + int2D(2, 0)))
			_position = _position + int2D(2, 0);
		else if(currentLevel.canPass(_corners[3] + int2D(-2, 0)))
			_position = _position + int2D(-2, 0);
		_updateVertexData();
	}
}

void character::_setMovement(int directionFlag, bool movementFlag)
{
	_isDirty = movementFlag;
	_speed = _maxSpeed * directionFlag;
	_updateVertexData();
}

void character::setMoveForward()
{
	_setMovement(1, true);
}

void character::setMoveReverse()
{
	_setMovement(-1, true);
}

void character::stopMoving()
{
	_setMovement(0, false);
}

void character::setSpeed(int speed)
{
	_maxSpeed = speed;
}

bool character::_checkForCollisions(level &currentLevel)
{
	if(currentLevel.canPass(_corners[0] + _direction) &&
	   currentLevel.canPass(_corners[1] + _direction) &&
	   currentLevel.canPass(_corners[2] + _direction) &&
	   currentLevel.canPass(_corners[3] + _direction))
		return true;
	else
	{
		_position = _position - _direction;
		return false;
	}
	return true;
}

int character::getSpeed(void) const {return _speed;}
float2D character::getPosition(void) const {return _position;}

void character::move(level &currentLevel)
{
	if(_isDirty && (GetTickCount64() - _previousTime >= _frameLimit))
	{
		_position = _position + _direction;
		if(!_checkForCollisions(currentLevel)) return;
		_previousTime = GetTickCount64();
		_updateVertexData();
	}
}

#endif