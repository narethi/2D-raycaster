#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"
class ray;
class light;
class character;

/*
	level is the stage that the reflections will be
	generated in, it will contain obstacles that the
	sound will relfect off of, and spaces that the sound
	can penetrate
*/
class level
{
	private:
		int2D _size = int2D(0, 0);
		int _tileSize;
		bool **map;
		float3D	* colorArray;
		int2D	* vertexArray;

		int _colorModel = 1;
		
		void _generateTexture(void);
		void addTile(int2D position);

		//This is for the interpolated texture
		float*** _aliasTexture(float ***previousTextureMap, double minimumIntensity, int levels, int passes);
		void _normalizeTexture(float *** temp);
		void _averageWorldPoints(float*** tempProcess);
		//These are the arrays responsible
		//for generating the texture
		float(*_rayTexture)[4];
		float(**_processArray)[4];
		GLuint _interpolatedTexture;

		//This is for the single point texture
		GLuint _outlineTexture;
		float(*_pointTexture)[4];
		float(**_processPointArray)[4];

		light * _flashLight;
		vector<light*> _lights;

		//This function is the actual render function
		//it forces the world to render the draw arrays
		//for the pre computed lighting
		void _render(void);
		void _renderRayTexture(void);
		float2D _previousCharacterPos = float2D(-1, -1);
		float _flashLightAngle = -1;
		void _readFile(string fileName);
		int _levels, _passes;
		float _minimumIntensity;

	protected:
		friend light;
		friend character;
		friend ray;
		/*
			front side is 0
			left side is 1
			back side is 2
			right side is 3
		*/
		bool _addToSide[4];
		float _leftSound;
		float _rightSound;
		float _frontSound;
		float _backSound;
		void  _addRayToTexture(ray * parentRay);

	public:
		level(int2D _size);
		level(int2D _size, int tileSize);

		//This gives all of the necessary information
		//to generate the level
		void buildLevel(void);
		void renderLevel(character &currentCharacter, level &currentLevel);
		void buildLightVolume(level &currentLevel, character &currentCharacter);
		void changeColorModel(int colorModel);
		bool canPass(int2D location) const;
		bool canPassTile(int2D tile) const;
		int2D getIndexFromLocation(int2D location);
		int2D getSize(void) const;
		int2D getDrawDimensions(void);

		//Minimum intensity is the smallest value that can be acceptable
		//levels is the magnitude that the light levels decrease by
		void softenTexture( double minimumIntensity, int levels, int passes);
		void addLight(light * newLight);
		void addLight(float2D position, float direction, int viewingAngle, int density, int intensity);
		
};

#endif