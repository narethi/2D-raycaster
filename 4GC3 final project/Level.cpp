#ifndef LEVEL_M
#define LEVEL_M

#include "Level.h"
#include "light.h"
#include "Ray.h"
#include "character.h"

level::level(int2D size, int tileSize) : _size(size), _tileSize(tileSize)
{
	//We need a flashlight to initialize the flash light in the wall
	_flashLight = new light();
	_readFile("test.txt");
	ALchangeGain(0,0,0,0);
}

level::level(int2D size) : level(size, 10)
{}

void level::addLight(light * newLight)
{
	if(newLight->getPosition().getX() > _size.getX()*_tileSize ||
		newLight->getPosition().getX() < 0 ||
		newLight->getPosition().getY() > _size.getY()*_tileSize ||
		newLight->getPosition().getY() < 0) return;
	_lights.push_back(newLight);
}

void level::addLight(float2D position, float direction, int viewingAngle, int density, int intensity)
{
	if(position.getX() > _size.getX()*_tileSize ||
		position.getX() < 0 ||
		position.getY() > _size.getX()*_tileSize ||
		position.getY() < 0) return;
	_lights.push_back(new light(position, direction, viewingAngle, density, intensity));
}

void level::_generateTexture(void)
{
	int xDim = _size.getX() *_tileSize, yDim = _size.getY()*_tileSize;
	//This is for the feathered texture
	_rayTexture = new float[xDim*yDim][4];
	_processArray = new (float(*[yDim])[4]);
	//This is for the 
	_pointTexture = new float[xDim*yDim][4];
	_processPointArray = new (float(*[yDim])[4]);
	for(int i = yDim; i--;)
	{
		_processArray[i] = &_rayTexture[i*xDim];
		_processPointArray[i] = &_pointTexture[i*xDim];
	}
	float emptyColor[] = { 0, 0, 0, 0};
	//initialize the textures so that there
	//is no rays being cast or viewed unless
	//otherwise specified
	for(int i = yDim; i--;)
	{
		for(int j = xDim; j--;)
		{
				_processArray[i][j][0] = emptyColor[0];
				_processArray[i][j][1] = emptyColor[1];
				_processArray[i][j][2] = emptyColor[2];
				_processArray[i][j][3] = emptyColor[3];

				_processPointArray[i][j][0] = emptyColor[0];
				_processPointArray[i][j][1] = emptyColor[1];
				_processPointArray[i][j][2] = emptyColor[2];
				_processPointArray[i][j][3] = 1;
		}
	}
	//Next run through all of the rays and populate the
	//texture buffer's color information
}

void level::softenTexture(double minimumIntensity, int levels, int passes)
{
	//initialize the temporary array
	int xDim = _size.getX()*_tileSize, yDim = _size.getY()*_tileSize;
	float *tempArray = new float[xDim*yDim * 4];
	float *** tempProcess = new float**[yDim];
	for(int i = yDim; i--;)
	{
		tempProcess[i] = new float*[xDim];
		for(int j = xDim; j--;)
		{
			tempProcess[i][j] = new float[4];
			for(int k = 4; k--;)
				tempProcess[i][j][k] = _processArray[i][j][k];
		}
	}
	//Next send it into the aliasing tree
	//_aliasTexture(tempProcess, minimumIntensity, levels);
	bool changesMade = false;
	double tempIntensity = 0;
	int limit = 0;
	while(!changesMade && limit != passes)
	{
		limit++;
		changesMade = true;
		for(int i = yDim; i--;)
		{
			for(int j = xDim; j--;)
			{

				//Find the points in the previous texture that
				//are larger than the accepted minimum intensity
				if(_processArray[i][j][3] < minimumIntensity)
				{
					//If the value is acceptable 
					//add it to the temporary lighting map
					tempIntensity = _processArray[i][j][3]/double(levels);
					tempProcess[i][j][3] += _processArray[i][j][3];
					if((i - 1) > 0)
						tempProcess[i - 1][j][3] += tempIntensity;
					if((i + 1) < yDim)
						tempProcess[i + 1][j][3] += tempIntensity;
					if((j - 1) > 0)
						tempProcess[i][j - 1][3] += tempIntensity;
					if((j + 1) < xDim)
						tempProcess[i][j + 1][3] += tempIntensity;
					changesMade = false;
				}
			}
		}
		for(int i = yDim; i--;)
		{
			for(int j = xDim; j--;)
			{
				for(int k = 4; k--;)
					_processArray[i][j][k] = tempProcess[i][j][k];
			}
		}
		_averageWorldPoints(tempProcess);
		cout << "current pass: " << limit << endl;
	}
	_averageWorldPoints(tempProcess);
	_normalizeTexture(tempProcess);
	for(int i = yDim; i--;)
	{
		for(int j = xDim; j--;)
		{
				delete[] tempProcess[i][j];
		}
	}
}

void level::_averageWorldPoints(float*** tempProcess)
{
	//initialize the temporary array
	int xDim = _size.getX()*_tileSize, yDim = _size.getY()*_tileSize;

	int count = 1;
	for(int i = yDim; i--;)
	{
		for(int j = xDim; j--;)
		{
			if(i - 1 > 0)
			{
				tempProcess[i][j][3] += _processArray[i - 1][j][3];
				count++;
			}
			if(i + 1 < yDim)
			{
				tempProcess[i][j][3] += _processArray[i + 1][j][3];
				count++;
			}
			if(j - 1 > 0)
			{
				tempProcess[i][j][3] += _processArray[i][j - 1][3];
				count++;
			}
			if(j + 1 < xDim)
			{
				tempProcess[i][j][3] += _processArray[i][j + 1][3];
				count++;
			}
			tempProcess[i][j][3] /= count;
			count = 1;
		}
	}
	for(int i = yDim; i--;)
	{
		for(int j = xDim; j--;)
		{
			for(int k = 4; k--;)
				_processArray[i][j][k] = tempProcess[i][j][k];
		}
	}
}
//Next run through all of the rays and populate the
//texture buffer's color information}

void level::_normalizeTexture(float*** tempProcess)
{
	//initialize the temporary array
	int xDim = _size.getX()*_tileSize, yDim = _size.getY()*_tileSize;
	float largest = tempProcess[0][0][3];
	int count = 1;
	for(int i = yDim; i--;)
	{
		for(int j = xDim; j--;)
		{
			if(tempProcess[i][j][3] > largest)
				largest = tempProcess[i][j][3];
		}
	}
	for(int i = yDim; i--;)
	{
		for(int j = xDim; j--;)
		{
			_processArray[i][j][3] = 1 - (tempProcess[i][j][3]/largest);
		}
	}
}

//What this function does is goes over the texture map
//and generates an aliased lighting map, so that the
//play can see the world as if the light is bouncing
//off the walls and landing on the floor
float*** level::_aliasTexture(float*** previousTexture, double minimumIntensity, int levels, int passes)
{
	//First step is to generate 
	//a temporary array to hold the data in
	int xDim = _size.getX()*_tileSize, yDim = _size.getX()*_tileSize;
	float(*temp)[4] = new float[xDim*yDim][4];
	float(**tempProcess)[4] = new (float(*[yDim])[4]);
	for(int i = yDim; i--;)
		tempProcess[i] = &temp[i*xDim];

	double tempIntensity = 0;
	bool madeChanges = false;

	//Now that the temporary arrays are set up
	//loop through the previous array, check
	//for points that suit the correct ray intensity
	//if they are above the threshold divide the value
	//by the chosen dimming value and add it to the
	//pixels above and below
	for(int i = yDim; i--;)
	{
		for(int j = xDim; j--;)
		{
			//Find the points in the previous texture that
			//are larger than the accepted minimum intensity
			if(previousTexture[i][j][3] < minimumIntensity)
			{
				//If the value is acceptable 
				//add it to the temporary lighting map
				tempIntensity = previousTexture[i][j][3];
				tempProcess[i][j][3] += tempIntensity;
				tempIntensity /= double(levels);
				//and then add the value divided byt the levels
				//to the 4 adjacent squares, be sure to make sure
				//that the squares exist
				if(i - 1 > 0)
					tempProcess[i - 1][j][3] += tempIntensity;
				if(i + 1 < yDim)
					tempProcess[i + 1][j][3] += tempIntensity;
				if(j - 1 > 0)
					tempProcess[i][j - 1][3] += tempIntensity;
				if(j + 1 < xDim)
					tempProcess[i][j + 1][3] += tempIntensity;
				madeChanges = true;
			}
		}
	}
	if(!madeChanges)
	{
		delete[] temp;
		return previousTexture;
	}
	else
	{
		//delete the previous texture, and alias again
		delete[] previousTexture;
		//return _aliasTexture((float***)&temp[0], minimumIntensity, levels);
	}
}

void level::_renderRayTexture(void)
{
	int maxX = _size.getX()*_tileSize, maxY = _size.getY()*_tileSize;

	glEnable(GL_TEXTURE_2D);

	switch(_colorModel)
	{
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, maxX, maxY, 0, GL_RGBA, GL_FLOAT, &_rayTexture[0]);
			glBindTexture(GL_TEXTURE_2D, _interpolatedTexture);
			break;
		case 4:
		default:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, maxX, maxY, 0, GL_RGBA, GL_FLOAT, &_pointTexture[0]);
			glBindTexture(GL_TEXTURE_2D, _outlineTexture);
			break;
	}
	

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glClear(GL_DEPTH_BUFFER_BIT);
	float2D textureArray[6];
	int2D corners[6];
	float3D colors[6];
	corners[0] = int2D(0, 0);
	textureArray[0] = float2D(0, 0);
	corners[1] = int2D(0, maxY);
	textureArray[1] = float2D(0, 1.f);
	corners[2] = int2D(maxX, maxY);
	textureArray[2] = float2D(1.f, 1.f);
	corners[3] = int2D(maxX, maxY);
	textureArray[3] = float2D(1.f, 1.f);
	corners[4] = int2D(maxX, 0);
	textureArray[4] = float2D(1.f, 0);
	corners[5] = int2D(0, 0);
	textureArray[5] = float2D(0, 0);
	for(int i = 0; i < 6; i++) colors[i] = float3D(1.f, 1.f, 1.f);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, &colors[0]);
	glVertexPointer(2, GL_INT, 0, &corners[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &textureArray[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glClear(GL_DEPTH_BUFFER_BIT);
	glDisable(GL_TEXTURE_2D);
	

}

void level::buildLightVolume(level &currentLevel, character &currentCharacter)
{
	for(int i = _lights.size(); i--;)
	{
		_lights.at(i)->buildEmitter(currentLevel, currentCharacter);
		_lights.at(i)->addRaysToTexture(currentLevel);
	}
	softenTexture(_minimumIntensity, _levels, _passes);
}

void level::_addRayToTexture(ray * parentRay)
{
	ray * tempRay = parentRay;
	int2D pos = int2D(tempRay->getEndPos().getX(), tempRay->getEndPos().getY());
	double currentAlpha = tempRay -> getAlpha();
	while(tempRay)
	{
		pos = int2D(tempRay->getEndPos().getX(), tempRay->getEndPos().getY());
		currentAlpha = tempRay->getAlpha();
		_processArray[pos.getY()][pos.getX()][3] += currentAlpha;
		_processPointArray[pos.getY()][pos.getX()][3] -= currentAlpha;
		tempRay = tempRay->getNext();
	}
}

void level::changeColorModel(int colorModel)
{
	ALchangeGain(0,0,0,0);
	_colorModel = colorModel;
	float3D tempColor;
	_frontSound = 0;
	_leftSound = 0;
	_backSound = 0;
	_rightSound = 0;
	switch(_colorModel)
	{
		//This is the full color mode
		//feathered mode, and outline mode
		case 1:
		case 3:
		case 4:
		for(int i = 0; i < _size.getY(); i++)
		{
			for(int j = 0; j < _size.getX(); j++)
			{
				map[i][j] ? tempColor = float3D(0.8, 0.8, 0.8) : tempColor = float3D(0.2, 0.2, 1);
				for(int k = 0; k < 6; k++) colorArray[(i*_size.getX() + j)*6 + k] = tempColor;
			}
		}
		_leftSound = _rightSound = _backSound = _frontSound = 0;
		break;
		//This is black tiles
		//This is the mode you can see the 
		//rays in i.e. the light debug render
		case 5:
		case 2:
			tempColor = float3D(0, 0, 0);
			for(int i = 0; i < _size.getX()*_size.getY() * 6; i++)
				colorArray[i] = tempColor;
			_leftSound = _rightSound = _backSound = _frontSound = 0;
			break;
		//This will be the flash light mode
		case 6:
			break;
		//This is the sound model
		case 7:
			break;
		default:;
	}
}

void level::addTile(int2D position)
{
	if(position.getX() >= _size.getX() || position.getY() >= _size.getY()) return;
	int startPoisition = (position.getY()*_size.getX() + position.getX())*6;
	float3D tempColor;
	int2D tempVertices[4];
	map[position.getY()][position.getX()] ? tempColor = float3D(0.8, 0.8, 0.8) : tempColor = float3D(0.2, 0.2, 1);
	for(int i = 0; i < 6; i++)
		colorArray[i + startPoisition] = tempColor;
	//bottom left
	tempVertices[0] = int2D(position.getX()*_tileSize + 1, position.getY()*_tileSize + 1), 
		//bottom right
		tempVertices[1] = int2D((position.getX() + 1)*_tileSize - 1, position.getY()*_tileSize + 1),
		//upper right
		tempVertices[2] = int2D((position.getX() + 1)*_tileSize - 1, (position.getY() + 1)*_tileSize - 1),
		//upper left
		tempVertices[3] = int2D(position.getX()*_tileSize + 1, (position.getY() + 1)*_tileSize - 1);
	vertexArray[startPoisition] = tempVertices[0];
	vertexArray[startPoisition + 1] = tempVertices[1];
	vertexArray[startPoisition + 2] = tempVertices[2];

	vertexArray[startPoisition + 3] = tempVertices[2];
	vertexArray[startPoisition + 4] = tempVertices[3];
	vertexArray[startPoisition + 5] = tempVertices[0];
}

void level::buildLevel(void)
{
	for(int i = 0; i < _size.getY(); i++)
		for(int j = 0; j < _size.getX(); j++)
			addTile(int2D(j, i));
}

int2D level::getIndexFromLocation(int2D location)
{
	location = location / _tileSize;
	if(location.getX() >= _size.getX() ||
	   location.getY() >= _size.getY() ||
	   location.getX() < 0 || location.getY() < 0)
	{
		int tempX = 0, tempY = 0;
		if(location.getX() >= _size.getX())
			tempX = _size.getX() - 1;
		else if(location.getX() < 0)
			tempX = 0;
		else tempX = location.getX();

		if(location.getY() >= _size.getY())
			tempY = _size.getY() - 1;
		else if(location.getY() < 0)
			tempY = 0;
		else tempY = location.getX();
		return int2D(tempX, tempY);
	}
	return location;
}

//This function takes in a tile position
//i.e. the index of the boolean map
bool level::canPassTile(int2D location) const
{
	if(location.getX() >= _size.getX() ||
		location.getY() >= _size.getY() ||
		location.getX() < 1 || location.getY() < 1)
		return false;
	return map[location.getY()][location.getX()];
}

int2D level::getDrawDimensions(void)
{
	return _size*_tileSize;
}

bool level::canPass(int2D location) const
{
	//normalize the location data so
	//that the information that is returned
	//belongs to boolean map
	location = location/_tileSize;
	if(location.getX() >= _size.getX() ||
		location.getY() >= _size.getY() ||
		location.getX() < 1 || location.getY() < 1)
		return false;
	return map[location.getY()][location.getX()];
}

void level::renderLevel(character &currentCharacter, level &currentLevel)
{
	float2D tempPos;
	switch(_colorModel)
	{
		//This is the full color mode
		//This is black tiles
		case 1:
			currentCharacter.render();
			_render();
			break;
			//This is feathered lighting model and the
			//point light model
		case 2:
			//check if the player has moved
			tempPos = currentCharacter.getPosition() + float2D().polarRotate(currentCharacter.getViewAngle())*currentCharacter.getSize();
			if(!(_previousCharacterPos == tempPos) || currentCharacter.getViewAngle() != _flashLightAngle)
			{
				_frontSound = 0;
				_leftSound = 0;
				_backSound = 0;
				_rightSound = 0;
				//if the player has moved then set the 
				//previous position to the new position
				_previousCharacterPos = tempPos;
				_flashLightAngle = currentCharacter.getViewAngle();
				//next update the flash light
				_flashLight = new light(_previousCharacterPos, TO_DEGREE(_flashLightAngle) - (135 / 2), 135, 135, 100);
				//_flashLight = new light(_previousCharacterPos, TO_DEGREE(_flashLightAngle), 1, 1, 200);
				_flashLight->buildEmitter(currentLevel, currentCharacter);
				cout << endl;
				cout << "Front sound: " << _frontSound << endl;
				cout << "Back sound: " << _backSound << endl;
				cout << "Left sound: " << _leftSound << endl;
				cout << "Right sound: " << _rightSound << endl;
				ALchangeGain(_frontSound, _leftSound, _backSound, _rightSound);
			}
			currentCharacter.render();
			_render();
			break;
		case 3:
		case 4:
			_render();
			_renderRayTexture();
			currentCharacter.render();
			
			
			
			break;
			//This is the mode you can see the 
			//rays in i.e. the light debug render
		case 5:
			//check if the player has moved
			tempPos = currentCharacter.getPosition() + float2D().polarRotate(currentCharacter.getViewAngle())*currentCharacter.getSize();
			if(!(_previousCharacterPos == tempPos) || currentCharacter.getViewAngle() != _flashLightAngle)
			{
				_frontSound = 0;
				_leftSound = 0;
				_backSound = 0;
				_rightSound = 0;
				//if the player has moved then set the 
				//previous position to the new position
				_previousCharacterPos = tempPos;
				_flashLightAngle = currentCharacter.getViewAngle();
				//next update the flash light
				_flashLight = new light(_previousCharacterPos, TO_DEGREE(_flashLightAngle) - (135/2), 135, 135, 100);
				//_flashLight = new light(_previousCharacterPos, TO_DEGREE(_flashLightAngle), 1, 1, 200);
				_flashLight->buildEmitter(currentLevel, currentCharacter);
				
				cout << "Front sound: " << _frontSound << endl;
				cout << "Back sound: " << _backSound << endl;
				cout << "Left sound: " << _leftSound << endl;
				cout << "Right sound: " << _rightSound << endl;
			}
			currentCharacter.render();
			_flashLight->debugRender();
			_render();
			break;
			//This will be the flash light mode
		case 6:
			break;
			//This is the sound model
		case 7:
			break;
		default:;
	}
}

void level::_render(void)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_FLOAT, 0, &colorArray[0]);
	glVertexPointer(2, GL_INT, 0, &vertexArray[0]);
	glDrawArrays(GL_TRIANGLES, 0, _size.getX()*_size.getY() * 6);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

int2D level::getSize(void) const
{
	return _size;
}

void level::_readFile(string fileName)
{
	FILE * currentFile = NULL;
	int fileSize = 0;
	int count = 0;
	int xSize, ySize, tileSize;
	char * readBuffer;
	string currentValue = "";
	float2D playerStart;
	float2D goalPosition;
	fopen_s(&currentFile, &fileName[0], "rb");
	if(currentFile == NULL)
	{
		cout << "that level file is not available, exiting program";
		for(int i = 0; i < 3; i++)
		{
			Sleep(500);
			cout << ".";
		}
		exit(100);
	}
	if(!currentFile) return;
	//The file lay out is as follow
	/*
		first line
		is the tile size
		second line
		x and y size of map
		
		next is the grid 
		0s for a blocked path
		1s for a clear path

		next line is the x and y start position
		next line is the x and y goal position

		after that is the information needed for 
		the generation of the lights in the map

		the next line is the start position
		the next line is the goal position

		the next series of lines is the lighting data

	*/
	fseek(currentFile, 0, SEEK_END);
	fileSize = ftell(currentFile);
	rewind(currentFile);
	readBuffer = new char[fileSize];
	fread_s(readBuffer, fileSize, sizeof(char), fileSize, currentFile);
	while(readBuffer[count] != '\n')
	{
		currentValue += readBuffer[count];
		count++;
	}
	tileSize = atoi(&currentValue[0]);
	currentValue = "";
	count++;
	while(readBuffer[count] != ' ')
	{
		currentValue += readBuffer[count];
		count++;
	}
	xSize = atoi(&currentValue[0]);
	currentValue = "";
	count++;
	while(readBuffer[count] != '\n')
	{
		currentValue += readBuffer[count];
		count++;
	}
	ySize = atoi(&currentValue[0]);
	map = new bool*[ySize];

	for(int i = ySize; i--;)
		map[i] = new bool[xSize];
	count++;
	for(int i = ySize; i--;)
	{
		for(int j = 0; j < xSize; j++)
		{
			while(readBuffer[count] != '1' && readBuffer[count] != '0')
			{
				count++;
				if(count > fileSize) return;
			}
			if(readBuffer[count] == '1')
				map[i][j] = true;
			else
				map[i][j] = false;
			count++;
		}
	}
	_tileSize = tileSize;
	_size = int2D(xSize, ySize);
	colorArray = new float3D[_size.getX()*_size.getY() * 6];
	vertexArray = new int2D[_size.getX()*_size.getY() * 6];
	//Now we need to set up the start position and the goal goal position
	currentValue = "";
	count++;
	while(readBuffer[count] != ' ')
	{
		currentValue += readBuffer[count];
		count++;
	}
	playerStart = float2D(float(atoi(&currentValue[0])), 0);
	count++;
	currentValue = "";
	while(readBuffer[count] != '\n')
	{
		currentValue += readBuffer[count];
		count++;
	}
	playerStart = float2D(playerStart.getX(), float(atoi(&currentValue[0])));
	//Now we need to set up the start position and the goal goal position
	currentValue = "";
	count++;
	while(readBuffer[count] != ' ')
	{
		currentValue += readBuffer[count];
		count++;
	}
	goalPosition = float2D(float(atoi(&currentValue[0])), 0);
	count++;
	currentValue = "";
	while(readBuffer[count] != '\n')
	{
		currentValue += readBuffer[count];
		count++;
	}
	goalPosition = float2D(goalPosition.getX(), float(atoi(&currentValue[0])));
	count++;
	_generateTexture();
	//Next get the values for the light volume that will be built
	//which are minimum radiance followed by the levels, and then by passes
	while(readBuffer[count] != ' ')
	{
		currentValue += readBuffer[count];
		count++;
	}
	count++;
	_minimumIntensity = atof(&currentValue[0]);
	currentValue = "";
	while(readBuffer[count] != ' ')
	{
		currentValue += readBuffer[count];
		count++;
	}
	count++;
	_levels = atoi(&currentValue[0]);
	currentValue = "";
	while(readBuffer[count] != '\n')
	{
		currentValue += readBuffer[count];
		count++;
	}
	count++;
	_passes = atoi(&currentValue[0]);
	currentValue = "";
	//Now get the lights that the users want to build
	//These are the light variables
	float lightXPos, lightYPos, lightDirection;
	int radianceAngle, rayNumber, rayIntensity;
	//now run through the file and get all of the lighting information
	while(count < fileSize)
	{
		while(readBuffer[count] != ' ')
		{
			currentValue += readBuffer[count];
			count++;
		}
		count++;
		lightXPos = atoi(&currentValue[0]);
		currentValue = "";
		while(readBuffer[count] != ' ')
		{
			currentValue += readBuffer[count];
			count++;
		}
		count++;
		lightYPos = atoi(&currentValue[0]);
		currentValue = "";
		while(readBuffer[count] != ' ')
		{
			currentValue += readBuffer[count];
			count++;
		}
		count++;
		lightDirection = stof(&currentValue[0]);
		currentValue = "";
		while(readBuffer[count] != ' ')
		{
			currentValue += readBuffer[count];
			count++;
		}
		count++;
		radianceAngle = atoi(&currentValue[0]);
		currentValue = "";
		while(readBuffer[count] != ' ')
		{
			currentValue += readBuffer[count];
			count++;
		}
		count++;
		rayNumber = atoi(&currentValue[0]);
		currentValue = "";
		while(readBuffer[count] != '\n')
		{
			currentValue += readBuffer[count];
			count++;
		}
		count++;
		rayIntensity = atoi(&currentValue[0]);
		currentValue = "";
		addLight(float2D(lightXPos, lightYPos), lightDirection, radianceAngle, rayNumber, rayIntensity);
	}
	fclose(currentFile);
}
#endif