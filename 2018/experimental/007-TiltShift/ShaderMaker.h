//
//		ShaderMaker.h
//
//		------------------------------------------------------------
//		Copyright (C) 2015. Lynn Jarvis, Leading Edge. Pty. Ltd.
//		Ported to OSX by Amaury Hazan (amaury@billaboop.com)
//
//		This program is free software: you can redistribute it and/or modify
//		it under the terms of the GNU Lesser General Public License as published by
//		the Free Software Foundation, either version 3 of the License, or
//		(at your option) any later version.
//
//		This program is distributed in the hope that it will be useful,
//		but WITHOUT ANY WARRANTY; without even the implied warranty of
//		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//		GNU Lesser General Public License for more details.
//
//		You will receive a copy of the GNU Lesser General Public License along 
//		with this program.  If not, see http://www.gnu.org/licenses/.
//		--------------------------------------------------------------
//
#pragma once
#ifndef ShaderMaker_H
#define ShaderMaker_H

#include <stdio.h>
#include <string>
#include <time.h> // for date
#include "FFGL.h" // windows : msvc project needs the FFGL folder in its include path
#include "FFGLLib.h"
#include "FFGLShader.h"
#include "FFGLPluginSDK.h"

#if (!(defined(WIN32) || defined(_WIN32) || defined(__WIN32__)))
// posix
typedef uint8_t  CHAR;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int8_t  BYTE;
typedef int16_t SHORT;
typedef int32_t LONG;
typedef LONG INT;
typedef INT BOOL;
typedef int64_t __int64; 
typedef int64_t LARGE_INTEGER;
#include <ctime>
#include <chrono> // c++11 timer
#endif

#define GL_SHADING_LANGUAGE_VERSION	0x8B8C
#define GL_READ_FRAMEBUFFER_EXT		0x8CA8
#define GL_TEXTURE_WRAP_R			0x8072


#define SCALE_SEED			4.0f
#define SHIFT_SEED			-2.0f
#define TRANSFORM_SCALE			10.0f

#define PI 		    3.1415926535897932384626433832795f
#define PI_2			2.0f*PI

 

const int DECAY_COUNT = 1000;
struct Vector {
	float x;
	float y;
	float z;
	float w;

};

class ShaderMaker : public CFreeFrameGLPlugin
{

public:

	ShaderMaker();
	~ShaderMaker();

	///////////////////////////////////////////////////
	// FreeFrameGL plugin methods
	///////////////////////////////////////////////////
    FFResult SetFloatParameter(unsigned int index, float value);
	FFResult SetBooleanParameter(unsigned int index, bool value);
	float GetFloatParameter(unsigned int index);
	bool GetBooleanParameter(unsigned int index);
	FFResult ProcessOpenGL(ProcessOpenGLStruct* pGL);
	FFResult InitGL(const FFGLViewportStruct *vp);
	FFResult DeInitGL();
	FFResult GetInputStatus(DWORD dwIndex);
	char * GetParameterDisplay(DWORD dwIndex);

	///////////////////////////////////////////////////
	// Factory method
	///////////////////////////////////////////////////
	static FFResult __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance) {
  		*ppOutInstance = new ShaderMaker();
		if (*ppOutInstance != NULL)
			return FF_SUCCESS;
		return FF_FAIL;
	}

protected:	

	// FFGL user parameters
	char  m_DisplayValue[16];
	float m_UserSpeed;
	float m_UserMouseX;
	float m_UserMouseY;
	float m_UserMouseLeftX;
	float m_UserMouseLeftY;
	float m_UserRed;
	float m_UserGreen;
	float m_UserBlue;
	float m_UserAlpha;
	Vector m_vector1;
	Vector m_vector2;
	float vector2_X;
	float vector2_Y;
	float vector2_Z;
	float vector2_W;
	Vector m_vector3;
	Vector m_vector4;
	float m_julia;
    float m_showKnobs;

	Vector decays1[DECAY_COUNT];
	Vector decays2[DECAY_COUNT];
	Vector decays3[DECAY_COUNT];


	Vector m_color1;
	Vector m_color2;
	Vector m_speeds;

	Vector m_times;

	// Flags
	bool bInitialized;

	// Local fbo and texture
	GLuint m_glTexture0;
	GLuint m_glTexture1;
	GLuint m_glTexture2;
	GLuint m_glTexture3;
	GLuint m_fbo;

	int lastWidth;
	int lastHeight;
	GLuint renderedTexture1;
	GLuint renderedTexture1Depth;
	GLuint renderedTexture2;
	GLuint renderedTexture2Depth;

	GLuint m_FramebufferId;
	GLuint m_FramebufferId2;
	// Viewport
	float m_vpWidth;
	float m_vpHeight;
    
    // Time
    double elapsedTime, lastTime;
#if (defined(WIN32) || defined(_WIN32) || defined(__WIN32__))
    // windows
    double PCFreq;
    __int64 CounterStart;
#else
    // posix c++11
    std::chrono::steady_clock::time_point start;
    std::chrono::steady_clock::time_point end;
#endif
	
	//
	// Shader uniforms
	//

	// Time
	float m_time;

	// Date (year, month, day, time in seconds)
	float m_dateYear;
	float m_dateMonth;
	float m_dateDay;
	float m_dateTime;

	// Channel playback time (in seconds)
	// iChannelTime components are always equal to iGlobalTime
	float m_channelTime[4];

	// Channel resolution in pixels - 4 channels with width, height, depth each
	float m_channelResolution[4][3];

	// Mouse
	float m_mouseX;
	float m_mouseY;

	// Mouse left and right
	float m_mouseLeftX;
	float m_mouseLeftY;
	float m_mouseRightX;
	float m_mouseRightY;

	// New ShaderToy uniforms 21-11-17
	// iTime - m_time - the same as iGlobalTime
	float m_frame; // iFrame - frame number
	float m_timedelta; // iTimeDelta - time elapsed since last frame
	float m_framerate;	// iFrameRate - 1.f / _deltaTime
	float m_samplerate;
	
	int m_initResources;
	FFGLExtensions m_extensions;
    FFGLShader m_shader;

	GLint m_inputTextureLocation;
	GLint m_inputTextureLocation1;
	GLint m_inputTextureLocation2;
	GLint m_inputTextureLocation3;
	
	GLint m_timeLocation;
	GLint m_dateLocation;
	GLint m_channeltimeLocation;
	GLint m_channelresolutionLocation;
	GLint m_mouseLocation;
	GLint m_resolutionLocation;
	GLint m_mouseLocationVec4;
	GLint m_screenLocation;
	GLint m_surfaceSizeLocation;
	GLint m_surfacePositionLocation;
	GLint m_vertexPositionLocation;

	// New ShaderToy uniforms 21-11-17
	// iTime - m_timeLocation - the same as iGlobalTime
	GLint m_frameLocation; // iFrame - frame number
	GLint m_timedeltaLocation; // iTimeDelta - time elapsed since last frame
	GLint m_framerateLocation;	// iFrameRate - 1.f / _deltaTime
	GLint m_samplerateLocation;	// iSampleRate - 44100.f default
	bool decaysInitialised;
	// Extras
	GLint m_inputColourLocation;

	GLint m_inputVector1Location;
	GLint m_inputVector2Location;
	GLint m_inputVector3Location;
	GLint m_inputVector4Location;
	GLint m_inputColor1Location;
	GLint m_inputColor2Location;
	GLint m_inputTimesLocation;
	GLint m_inputIsPhase2Location;

	GLint m_inputJuliaLocation;

	GLint m_inputShowKnobsLocation;

	GLint m_displayList[1000];
	void SetDefaults();
	void StartCounter();
	double GetCounter();
	bool LoadShader(std::string shaderString);

	void createDisplayList();
	void renderQuad2(float texMaxX, float texMaxY);
	void updateRenderTargets(int newWidth, int newHeight);
	void CreateRectangleTexture(FFGLTextureStruct Texture, FFGLTexCoords maxCoords, GLuint &glTexture, GLenum texunit, GLuint &fbo, GLuint hostFbo);
	void renderTo(GLuint hostFbo,GLuint fbColorTexture,GLuint fbDepthTexture, GLuint texture1);
};


#endif
