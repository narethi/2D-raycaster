#ifndef OAL_M
#define OAL_M

#include "stdafx.h"

FILE *fp = NULL;

char type[4];
uLong size, chunkSize, sampleRate, avgBytesPerSec, dataSize;
short formatType, channels, bytesPerSample, bitsPerSample;
unsigned char* buf;

ALCdevice *device;
ALCcontext *context;

ALuint buffer;
//ALuint frontSource 0, leftSource 1, backSource 2, rightSource 3;
ALuint Sources[4];
ALuint frequency;
ALenum format = 0;

ALfloat SourceBack[] = { 0.0, 0.0, -1.0 };
ALfloat SourceFront[] = { 0.0, 0.0, 1.0 };
ALfloat SourceRight[] = { 1.0, 0.0, 0.0 };
ALfloat SourceLeft[] = { -1.0, 0.0, 0.0 };

ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 
						  0.0, 1.0, 0.0 };

void ALBuffer(void)
{
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);

	alSourcefv(Sources[0], AL_POSITION, SourceFront);
	alSourcei(Sources[0], AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcefv(Sources[2], AL_POSITION, SourceBack);
	alSourcei(Sources[2], AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcefv(Sources[3], AL_POSITION, SourceRight);
	alSourcei(Sources[3], AL_SOURCE_RELATIVE, AL_TRUE);
	alSourcefv(Sources[1], AL_POSITION, SourceLeft);
	alSourcei(Sources[1], AL_SOURCE_RELATIVE, AL_TRUE);
	
	alSourceStop(Sources[0]);
	alSourceStop(Sources[1]);
	alSourceStop(Sources[2]);
	alSourceStop(Sources[3]);

	alBufferData(buffer, format, buf, dataSize, frequency);

	alSourcei(Sources[2], AL_BUFFER, buffer);
	alSourcef(Sources[2], AL_PITCH, 1.0f);
	alSourcef(Sources[2], AL_GAIN, 0.f);
	alSourcefv(Sources[2], AL_VELOCITY, SourceVel);
	alSourcei(Sources[2], AL_LOOPING, AL_TRUE);
	alSourcefv(Sources[2], AL_POSITION, SourceBack);

	alSourcei(Sources[0], AL_BUFFER, buffer);
	alSourcef(Sources[0], AL_PITCH, 1.0f);
	alSourcef(Sources[0], AL_GAIN, 0.f);
	alSourcefv(Sources[0], AL_VELOCITY, SourceVel);
	alSourcei(Sources[0], AL_LOOPING, AL_TRUE);
	alSourcefv(Sources[0], AL_POSITION, SourceFront);

	alSourcei(Sources[1], AL_BUFFER, buffer);
	alSourcef(Sources[1], AL_PITCH, 1.0f);
	alSourcef(Sources[1], AL_GAIN, 0.f);
	alSourcefv(Sources[1], AL_VELOCITY, SourceVel);
	alSourcei(Sources[1], AL_LOOPING, AL_TRUE);
	alSourcefv(Sources[1], AL_POSITION, SourceLeft);

	alSourcei(Sources[3], AL_BUFFER, buffer);
	alSourcef(Sources[3], AL_PITCH, 1.0f);
	alSourcef(Sources[3], AL_GAIN, 0.f);
	alSourcefv(Sources[3], AL_VELOCITY, SourceVel);
	alSourcei(Sources[3], AL_LOOPING, AL_TRUE);
	alSourcefv(Sources[3], AL_POSITION, SourceRight);

	alSourcePlay(Sources[2]);
	alSourcePlay(Sources[0]);
	alSourcePlay(Sources[1]);
	alSourcePlay(Sources[3]);
}

void ALchangeGain(float front, float left, float back, float right)
{
	alSourcef(Sources[3], AL_GAIN, right / 100);
	alSourcef(Sources[1], AL_GAIN, left  / 100);
	alSourcef(Sources[2], AL_GAIN, back / 100);
	alSourcef(Sources[0], AL_GAIN, front / 100);
}

int ALInit(void)
{
	device = alcOpenDevice(NULL);
	if(!device)
		return 0;
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	if(!context)
		return 0;

	frequency = sampleRate;
	format = 0;

	alGenBuffers(1, &buffer);
	alGenSources(4, Sources);

	if(bitsPerSample == 8)
	{
		if(channels == 1)
			format = AL_FORMAT_MONO8;
		else if(channels == 2)
			format = AL_FORMAT_STEREO8;
	}
	else if(bitsPerSample == 16)
	{
		if(channels == 1)
			format = AL_FORMAT_MONO16;
		else if(channels == 2)
			format = AL_FORMAT_STEREO16;
	}
	ALBuffer();
	return 1;
}

int setUpAudio(void)
{
	fp = NULL;
	fopen_s(&fp, "bee.wav", "rb");
	if(fp == NULL)
	{
		cout << "that audio file is not available, exiting program";
		for(int i = 0; i < 3; i++)
		{
			Sleep(500);
			cout << ".";
		}
		exit(100);
	}
	fread(type, sizeof(char), 4, fp);
	if(type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
		return 0;

	fread(&size, sizeof(uLong), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if(type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
		return 0;

	fread(type, sizeof(char), 4, fp);
	if(type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
		return 0;

	fread(&chunkSize, sizeof(uLong), 1, fp);
	fread(&formatType, sizeof(short), 1, fp);
	fread(&channels, sizeof(short), 1, fp);
	fread(&sampleRate, sizeof(uLong), 1, fp);
	fread(&avgBytesPerSec, sizeof(uLong), 1, fp);
	fread(&bytesPerSample, sizeof(short), 1, fp);
	fread(&bitsPerSample, sizeof(short), 1, fp);

	fread(type, sizeof(short), 1, fp);

	fread(type, sizeof(char), 4, fp);
	if(type[0] != 'd' || type[1] != 'a' || type[2] != 't' || type[3] != 'a')
		return 0;

	fread(&dataSize, sizeof(uLong), 1, fp);

	buf = new unsigned char[dataSize];
	fread(buf, sizeof(char), dataSize, fp);

	ALInit();
	return 1;
}

#endif