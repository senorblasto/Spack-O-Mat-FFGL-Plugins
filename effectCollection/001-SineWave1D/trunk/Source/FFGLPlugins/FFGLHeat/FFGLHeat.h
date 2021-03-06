#ifndef FFGLHeat_H
#define FFGLHeat_H

#include <FFGLShader.h>
#include "../FFGLPluginSDK.h"

struct SineWave{
	float count;
	float frequency;
	float amplitude;
	float wavelength;
};
class FFGLHeat :


public CFreeFrameGLPlugin
{
public:
	FFGLHeat();
  virtual ~FFGLHeat() {}

	///////////////////////////////////////////////////
	// FreeFrameGL plugin methods
	///////////////////////////////////////////////////
	
	DWORD	SetParameter(const SetParameterStruct* pParam);		
	DWORD	GetParameter(DWORD dwIndex);					
	DWORD	ProcessOpenGL(ProcessOpenGLStruct* pGL);
  DWORD InitGL(const FFGLViewportStruct *vp);
  DWORD DeInitGL();
  	DWORD SetTime(double time);
	

double GetTimeInSecondsSinceStart();
	///////////////////////////////////////////////////
	// Factory method
	///////////////////////////////////////////////////

	static DWORD __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance)
  {
  	*ppOutInstance = new FFGLHeat();
	  if (*ppOutInstance != NULL)
      return FF_SUCCESS;
	  return FF_FAIL;
  }
protected:	
	// Time
	double m_Time;
	SYSTEMTIME m_SystemTimeStart;
	SYSTEMTIME m_SystemTimeLastFrame;
	double timeCounter;
	double sinCounter1;
	double sinCounter2;
	double sinCounter3;
	double sinCounter4; 
	float m_sinXSpeed;
	float m_sinXSpeed2;
	float m_sinXVariance; 
	float m_sinYSpeed;
	float m_sinYSpeed2;
	float m_sinYVariance; 
	float m_dotcount;
	float m_dotsize;
	float m_beatdotsize;
	float m_beatdotrange;

	
	 SineWave sineWave1;
	 SineWave sineWave2;
	 SineWave sineWave3;
	
	int m_initResources;

	GLuint m_heatTextureId;

	FFGLExtensions m_extensions;
    FFGLShader m_shader;
	GLint m_inputTextureLocation;
	GLint m_heatTextureLocation;
	GLint m_maxCoordsLocation; 
	GLint m_timeLocation; 
	GLint m_aspectLocation;
	GLint m_sineFactorsLocation;
	GLint m_sineFactors2Location;
	GLint m_dotcountLocation;
	GLint m_dotsizeLocation;
	
	GLint m_beatdotsizeLocation;
	GLint m_beatdotrangeLocation;
	GLint m_sinewave1Location;
	GLint m_sinewave2Location;
	GLint m_sinewave3Location;
};


#endif
