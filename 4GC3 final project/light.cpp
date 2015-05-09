#ifndef LIGHT_M
#define LIGHT_M

#include "Ray.h"
#include "light.h"
#include "Level.h"
#include "character.h"

light::light() : light(float2D(0, 0), 0, 0, 0, 0) {}

light::light(float2D position, float direction, int viewingAngle, int density, int intensity) :
_position(position), _direction(direction), _viewingAngle(viewingAngle),
_density(density), _raysToCast(new ray*[density]), _intensity(intensity) {}



void light::buildEmitter(level &currentLevel, character &currentCharacter)
{
	//first get the step for the angle
	//The step for the angle is density/viewingAngle
	double angleStep = TO_RAD(double(_viewingAngle) / double(_density) );
	double currentAngle = TO_RAD(_direction);
	for(int i = _density; i--;)
	{
		//Now generate the ray
		_raysToCast[i] = new ray(_intensity, _position, currentAngle, currentLevel, currentCharacter);
		//increment the casting angle
		currentAngle += angleStep;
	}
}

void light::addRaysToTexture(level &currentLevel)
{
	for(int i = _density; i--;)
		currentLevel._addRayToTexture(_raysToCast[i]);
}

void light::debugRender(void)
{
	for(int i = _density; i--;)
		_raysToCast[i]->debugRender();
}

float2D light::getPosition(void) const
{
	return _position;
}
#endif