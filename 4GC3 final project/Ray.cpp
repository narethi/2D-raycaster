#ifndef RAY_M
#define RAY_M

#include "Ray.h"
#include "Level.h"
#include "character.h"

ray::ray() : ray(0, float2D(0,0), 0, level(int2D(0,0)), character())
{}

/*
	This is the public constructor, what it does is
	generates the first parent node, and then makes
	the previous ray itself, since it is the first node
	in the set
*/
ray::ray(int amplitude, float2D position, double angle, level &currentLevel, character &currentCharacter) :
ray(amplitude, position, angle, this, amplitude, currentLevel, currentCharacter)
{}

/*
	This is a private constructor that is invoked by the parent
	what this does is generate a new ray, and links it to the 
	parent node
*/
ray::ray(int amplitude, float2D position, double angle, ray * parent, int maxAmplitude, level &currentLevel, character &currentCharacter) :
_amplitude(amplitude), _startPosition(position), _rayAngle(angle), _previousRay(parent), _maximumAmplitude(maxAmplitude)
{
	_rayAngle = angle;
	_detectCollision(currentLevel, currentCharacter);
}

bool ray::_spawnNextRay(int amplitude, float2D position, double angle, level &currentLevel, character &currentCharacter)
{
	//If a new ray can be built then the function should return true
	if(_nextRay = new ray(amplitude, position, angle, this, _maximumAmplitude, currentLevel, currentCharacter)) return true;
	return false;
}

void ray::_debugRender(void)
{
	ray * temp;
	if(getNext())
		getNext()->_debugRender();
	glBegin(GL_LINES);
		glColor3f((double)_amplitude / (double)_maximumAmplitude, 0, 0);
		glVertex2f(getStartPos().getX(), getStartPos().getY());
		glColor3f((double)_amplitude / (double)_maximumAmplitude, 0, 0);
		glVertex2f(getEndPos().getX(), getEndPos().getY());
	glEnd();
}

void ray::debugRender(void)
{
	glColor3f(0, 1, 0);
	glPointSize(1);

	if(getNext()) getNext() -> _debugRender();
	glBegin(GL_LINES);
	glColor3f((double)_amplitude / (double)_maximumAmplitude, 0, 0);
	glVertex2f(getStartPos().getX(), getStartPos().getY());
	glColor3f((double)_amplitude / (double)_maximumAmplitude, 0, 0);
	glVertex2f(getEndPos().getX(), getEndPos().getY());
	glEnd();
}

double ray::getAlpha(void)
{
	return (double)_amplitude / (double)_maximumAmplitude;
}

float2D ray::getStartPos(void) const
{
	return _startPosition;
}

float2D ray::getEndPos(void) const
{
	return _endPosition;
}

//using Bresenham's line algorithm
bool ray::_detectCollision(level &currentLevel, character &currentCharacter)
{
	if(_rayAngle < 0) _rayAngle += 2 * PI;
	if(_rayAngle >= 360) _rayAngle -= 2 * PI + TO_RAD(1);
	//First step is to get the slope fot he line
	//since we know where the origin and the edge
	//of the map is we can use a polar rotation of 
	//an arbirtrary sized circle, i.e. 
	//2*x component size of the level

	//Second point is drawn at an arbitrary point in space
	//temp angle is used so that the calculations 
	//can be done in quadrant 0
	float2D secondPoint = float2D().polarRotate(_rayAngle)*10000 + _startPosition;
	int ystep, xstep;
	int error;
	int errorPrev;
	double y = _startPosition.getY(), x = _startPosition.getX();
	double ddx, ddy;
	double dx = secondPoint.getX() - _startPosition.getX();
	double dy = secondPoint.getY() - _startPosition.getY();
	bool loop = true;
	bool hitCharacter = false;
	//Point coord will be the actual point
	int2D pointCoords(0, 0);
	//Collision coord will be the point inside the wall
	int2D collisionCoords(0 , 0);
	if(dy < 0)
	{
		ystep = -1;
		dy = -dy;
	}
	else ystep = 1;
	if(dx < 0)
	{
		xstep = -1;
		dx = -dx;
	}
	else xstep = 1;
	ddy = 2 * dy;
	ddx = 2 * dx;
	if(ddx >= ddy)
	{
		errorPrev = error = dx;
		while(currentLevel.canPass(int2D(x, y)) && loop)
		{
			x += xstep;
			error += ddy;
			if(currentCharacter.isPointInsideCharacter(int2D(x, y), int2D(x - xstep, y), currentLevel))
			{
				if(currentLevel._addToSide[0])
					currentLevel._frontSound += getAlpha();

				else if(currentLevel._addToSide[1])
					currentLevel._leftSound += getAlpha();

				else if(currentLevel._addToSide[2])
					currentLevel._backSound += getAlpha();

				else if(currentLevel._addToSide[3])
					currentLevel._rightSound += getAlpha();
				for(int i = 4; i--;)
					currentLevel._addToSide[i] = false;
				_endPosition = _startPosition;
				return true;
			}
			if(error > ddx)
			{
				y += ystep;
				error -= ddx;
				if(error + errorPrev < ddx)
				{
					if(!currentLevel.canPass(int2D(x, y - ystep)))
					{
						collisionCoords = currentLevel.getIndexFromLocation(int2D(x, y - ystep));
						break;
					}

					if(currentCharacter.isPointInsideCharacter(int2D(x, y - ystep), int2D(x, y), currentLevel))
					{
						if(currentLevel._addToSide[0])
							currentLevel._frontSound += getAlpha();
						else if(currentLevel._addToSide[1])
							currentLevel._leftSound += getAlpha();
						else if(currentLevel._addToSide[2])
							currentLevel._backSound += getAlpha();
						else if(currentLevel._addToSide[3])
							currentLevel._rightSound += getAlpha();
						for(int i = 4; i--;)
							currentLevel._addToSide[i] = false;
						_endPosition = _startPosition;
						return true;
					}
				}
				else if(error + errorPrev > ddx)
				{
					if(!currentLevel.canPass(int2D(x - xstep, y)))
					{
						collisionCoords = currentLevel.getIndexFromLocation(int2D(x - xstep, y));
						break;
					}
					if(currentCharacter.isPointInsideCharacter(int2D(x - xstep, y), int2D(x, y), currentLevel))
					{
						if(currentLevel._addToSide[0])
							currentLevel._frontSound += getAlpha();
						else if(currentLevel._addToSide[1])
							currentLevel._leftSound += getAlpha();
						else if(currentLevel._addToSide[2])
							currentLevel._backSound += getAlpha();
						else if(currentLevel._addToSide[3])
							currentLevel._rightSound += getAlpha();
						for(int i = 4; i--;)
							currentLevel._addToSide[i] = false;
						_endPosition = _startPosition;
						return true;
					}
				}
				else
				{  // corner: bottom and left squares also 
					if(!currentLevel.canPass(int2D(x - xstep, y)))
					{
						collisionCoords = currentLevel.getIndexFromLocation(int2D(x - xstep, y));
						break;
					}
					else if(!currentLevel.canPass(int2D(x, y - ystep)))
					{
						collisionCoords = currentLevel.getIndexFromLocation(int2D(x, y - ystep));
						break;
					}
					if(currentCharacter.isPointInsideCharacter(int2D(x, y - ystep), int2D(x, y), currentLevel))
					{
						if(currentLevel._addToSide[0])
							currentLevel._frontSound += getAlpha();
						else if(currentLevel._addToSide[1])
							currentLevel._leftSound += getAlpha();
						else if(currentLevel._addToSide[2])
							currentLevel._backSound += getAlpha();
						else if(currentLevel._addToSide[3])
							currentLevel._rightSound += getAlpha();
						for(int i = 4; i--;)
							currentLevel._addToSide[i] = false;
						_endPosition = _startPosition;
						return true;
					}
					else if(currentCharacter.isPointInsideCharacter(int2D(x - xstep, y), int2D(x, y), currentLevel))
					{
						if(currentLevel._addToSide[0])
							currentLevel._frontSound += getAlpha();
						else if(currentLevel._addToSide[1])
							currentLevel._leftSound += getAlpha();
						else if(currentLevel._addToSide[2])
							currentLevel._backSound += getAlpha();
						else if(currentLevel._addToSide[3])
							currentLevel._rightSound += getAlpha();
						for(int i = 4; i--;)
							currentLevel._addToSide[i] = false;
						_endPosition = _startPosition;
						return true;
					}
				}
			}
			errorPrev = error;
		}
		_endPosition = float2D(x - xstep, y - ystep);
		pointCoords = currentLevel.getIndexFromLocation(int2D(x - xstep, y - ystep));
		if(collisionCoords == int2D(0, 0))
			collisionCoords = currentLevel.getIndexFromLocation(int2D(x + xstep, y + ystep));
	}
	else
	{
		errorPrev = error = dy;
		while(currentLevel.canPass(int2D(x, y)) && loop)
		{
			y += ystep;
			error += ddx;
			if(currentCharacter.isPointInsideCharacter(int2D(x, y), int2D(x - xstep, y), currentLevel))
			{
				if(currentLevel._addToSide[0])
					currentLevel._frontSound += getAlpha();
				else if(currentLevel._addToSide[1])
					currentLevel._leftSound += getAlpha();
				else if(currentLevel._addToSide[2])
					currentLevel._backSound += getAlpha();
				else if(currentLevel._addToSide[3])
					currentLevel._rightSound += getAlpha();
				for(int i = 4; i--;)
					currentLevel._addToSide[i] = false;
				_endPosition = _startPosition;
				return true;
			}
			if(error > ddy)
			{
				x += xstep;
				error -= ddy;
				if(error + errorPrev < ddy)
				{
					if(!currentLevel.canPass(int2D(x - xstep, y)))
					{
						collisionCoords = currentLevel.getIndexFromLocation(int2D(x - xstep, y));
						break;
					}
					if(currentCharacter.isPointInsideCharacter(int2D(x - xstep, y), int2D(x, y), currentLevel))
					{
						if(currentLevel._addToSide[0])
							currentLevel._frontSound += getAlpha();
						else if(currentLevel._addToSide[1])
							currentLevel._leftSound += getAlpha();
						else if(currentLevel._addToSide[2])
							currentLevel._backSound += getAlpha();
						else if(currentLevel._addToSide[3])
							currentLevel._rightSound += getAlpha();
						for(int i = 4; i--;)
							currentLevel._addToSide[i] = false;
						_endPosition = _startPosition;
						return true;
					}
				}
				else if(error + errorPrev > ddy)
				{
					if(!currentLevel.canPass(int2D(x, y - ystep)))
					{
						collisionCoords = currentLevel.getIndexFromLocation(int2D(x, y - ystep));
						break;
					}
					if(currentCharacter.isPointInsideCharacter(int2D(x, y - ystep), int2D(x, y), currentLevel))
					{
						if(currentLevel._addToSide[0])
							currentLevel._frontSound += getAlpha();
						else if(currentLevel._addToSide[1])
							currentLevel._leftSound += getAlpha();
						else if(currentLevel._addToSide[2])
							currentLevel._backSound += getAlpha();
						else if(currentLevel._addToSide[3])
							currentLevel._rightSound += getAlpha();
						for(int i = 4; i--;)
							currentLevel._addToSide[i] = false;
						_endPosition = _startPosition;
						return true;
					}
				}
				else
				{
					if(!currentLevel.canPass(int2D(x - xstep, y)))
					{
						collisionCoords = currentLevel.getIndexFromLocation(int2D(x - xstep, y));
						break;
					}
					else if(!currentLevel.canPass(int2D(x, y - ystep)))
					{
						collisionCoords = currentLevel.getIndexFromLocation(int2D(x, y - ystep));
						break;
					}
					if(currentCharacter.isPointInsideCharacter(int2D(x, y - ystep), int2D(x, y), currentLevel))
					{
						if(currentLevel._addToSide[0])
							currentLevel._frontSound += getAlpha();
						else if(currentLevel._addToSide[1])
							currentLevel._leftSound += getAlpha();
						else if(currentLevel._addToSide[2])
							currentLevel._backSound += getAlpha();
						else if(currentLevel._addToSide[3])
							currentLevel._rightSound += getAlpha();
						for(int i = 4; i--;)
							currentLevel._addToSide[i] = false;
						_endPosition = _startPosition;
						return true;
					}
					else if(currentCharacter.isPointInsideCharacter(int2D(x - xstep, y), int2D(x, y), currentLevel))
					{
						if(currentLevel._addToSide[0])
							currentLevel._frontSound += getAlpha();
						else if(currentLevel._addToSide[1])
							currentLevel._leftSound += getAlpha();
						else if(currentLevel._addToSide[2])
							currentLevel._backSound += getAlpha();
						else if(currentLevel._addToSide[3])
							currentLevel._rightSound += getAlpha();
						for(int i = 4; i--;)
							currentLevel._addToSide[i] = false;
						_endPosition = _startPosition;
						return true;
					}
				}
			}
			errorPrev = error;
		}
		_endPosition = float2D(x - xstep, y - ystep);
		pointCoords = currentLevel.getIndexFromLocation(int2D(x - xstep, y - ystep));
		if(collisionCoords == int2D(0,0))
			collisionCoords = currentLevel.getIndexFromLocation(int2D(x + xstep, y + ystep));
	}
	//Next generate the next ray in the 
	//sequence, with the remaining amplitude
	//aswell as ritated appropriately
	double rayTotal = sqrt( (_startPosition.getX() - _endPosition.getX())*(_startPosition.getX() - _endPosition.getX())
							+ (_startPosition.getY() - _endPosition.getY())*(_startPosition.getY() - _endPosition.getY()));
	if((_amplitude - rayTotal) < 0 || (rayTotal == 0)) return true;
	//The next step is to figure out which side we are looking at so we can add the appropriate angle
	/*
		determining the right angle of incidence requires two things
		the angle of the surface that we hit and the direction of the
		origin of the ray

		the angle of the surface is easy to figure out since
		the map consists of blocks that are all at right angles
		so the configuration is all based on that
	*/
	double angleOfIncidence = 0;

	if(collisionCoords == pointCoords) {return true;}
	//If the system hits a boundary the following situations need to be taken care of
	else if(collisionCoords.getX() != pointCoords.getX() && collisionCoords.getY() != pointCoords.getY())
		 return true;
	//First determine the side of the block that the ray collided with
	//from the left
	if((collisionCoords.getX() - pointCoords.getX()) > 0)
			angleOfIncidence = PI - _rayAngle;
	//from the right
	else if((collisionCoords.getX() - pointCoords.getX()) < 0)
			angleOfIncidence = PI - _rayAngle;

	//from the bottom
	if((collisionCoords.getY() - pointCoords.getY()) > 0)
			angleOfIncidence = 2*PI - _rayAngle;
	//from the top
	else if((collisionCoords.getY() - pointCoords.getY()) < 0)
			angleOfIncidence = 2 * PI - _rayAngle;
	_spawnNextRay(_amplitude - rayTotal, _endPosition, angleOfIncidence, currentLevel, currentCharacter);
	return true;
}


ray * ray::getNext()
{
	return _nextRay;
}
#endif