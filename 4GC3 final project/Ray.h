#ifndef RAY_H
#define RAY_H

#include "stdafx.h"

class level;
class character;
/*
	The ray class is the heart the
	ray casting system. It contains
	all of the necessary information
	on how the ray caster will work
*/
class ray
{
	private:
		//Since this is generating reflections
		//there is need for some form of power
		//variable, as rays traverse a scene thier
		//amplitude goes down, and when the amplitude
		//hits 0 then the ray is finished
		int _amplitude;

		float2D _startPosition;
		float2D _endPosition;
		double _rayAngle;
		int _maximumAmplitude;


		ray(int amplitude, float2D position, double angle, ray * parent, int maxAmplitude, level &currentLevel, character &currentCharacter);
		//We will need to know where and when collisions have occured
		//This function will return true if a ray has reflected, and
		//it if has it will spawn a new ray at the reflection point
		bool _detectCollision(level &currentLevel, character &currentCharacter);

		//runtimeDetectCollision takes the character information and 
		//checks to see if the character has intercepted a ray, if
		//they have then play a sound
		bool _runtimeDetectCollision(character &character);
		bool _spawnNextRay(int amplitude, float2D position, double angle, level &currentLevel, character &currentCharacter);

		//Since rays have to spawn new rays each ray will contain
		//a pointer to the previous and next rays in the system
		ray * _nextRay;
		ray * _previousRay;
		void _debugRender(void);
	protected:
		friend class light;
		ray();

	public:
		ray(int amplitude, float2D position, double angle, level &currenLevel, character &currentCharacter);
		void debugRender(void);
		float2D getStartPos(void) const;
		float2D getEndPos(void) const;
		ray * getNext();
		ray * getPrevious();
		//This returns the ratio between
		//the amplitude and the max amplitude
		double getAlpha(void);
};

#endif