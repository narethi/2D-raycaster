#ifndef LIGHT_H
#define LIGHT_H

#include "stdafx.h"

class ray;
class level;
class character;

/*
	This class is used as ray source 
	for the lighting effects, it contains
	the position, direction, and emmiting
	angle, as well as the ray density
	which is the minimum angle between
	each ray
*/
class light
{
	private:
		float2D _position;
		float _direction;
		int _viewingAngle;
		int _density;
		int _intensity;
		ray ** _raysToCast;
	protected:
		friend level;
		int _getDensity(void);
	public:
		light();
		light(float2D position, float direction, int viewingAngle, int density, int intensity);
		void buildEmitter(level &currentLevel, character &currentCharacter);
		void addRaysToTexture(level &currentLevel);
		float2D getPosition(void) const;
		void debugRender(void);
};

#endif