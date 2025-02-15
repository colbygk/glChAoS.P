//------------------------------------------------------------------------------
//  Copyright (c) 2018-2019 Michele Morrone
//  All rights reserved.
//
//  https://michelemorrone.eu - https://BrutPitt.com
//
//  twitter: https://twitter.com/BrutPitt - github: https://github.com/BrutPitt
//
//  mailto:brutpitt@gmail.com - mailto:me@michelemorrone.eu
//  
//  This software is distributed under the terms of the BSD 2-Clause license
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "ParticlesUtils.h"
#include "palettes.h"

#define unsesto  .166666666666666666667
#define unterzo  .333333333333333333333
#define dueterzi .666666666666666666667

//-----------------------------------------------------------------------------
// Name: getRandomMinMax()
// Desc: Gets a random number between min/max boundaries
//-----------------------------------------------------------------------------
float getRandomMinMax( float fMin, float fMax )
{
    float fRandNum = (float)rand () / (float)RAND_MAX;
    return fMin + (fMax - fMin) * fRandNum;
}

//-----------------------------------------------------------------------------
// Name: getRandomVector()
// Desc: Generates a random vector where X,Y, and Z components are between
//       -1.0 and 1.0
//-----------------------------------------------------------------------------
vec3 getRandomVector( void )
{
	vec3 vVector;

    // Pick a random Z between -1.0f and 1.0f.
    vVector.z = getRandomMinMax( -1.0f, 1.0f );

    // Get radius of this circle
    float radius = (float)sqrt(1 - vVector.z * vVector.z);

    // Pick a random point on a circle.
    float t = getRandomMinMax( -T_PI, T_PI );

    // Compute matching X and Y for our Z.
    vVector.x = (float)cosf(t) * radius;
    vVector.y = (float)sinf(t) * radius;

	return vVector;
}

vec3 HLStoRGB( vec3 HLS)
{

    if(HLS.z==0.0) { return vec3(HLS.y,HLS.y,HLS.y); }

    if(HLS.x<0.0) HLS.x+=1.0;
    if(HLS.x>1.0) HLS.x-=1.0;

    //if(HLS.y>1) HLS.y = 1;
    //if(HLS.z>1) HLS.z = 1;

    float v2 = (HLS.y <= 0.5) ? HLS.y*(1.0+HLS.z) : (HLS.y+HLS.z) - HLS.y*HLS.z;
    float v1 = 2.0*HLS.y - v2;
    float v2_v1 = (v2-v1) * 6.0;

    if (HLS.x < unsesto )       return vec3(v2,
                                             v1 + v2_v1*HLS.x,
                                             v1 + v2_v1*(HLS.x-unterzo));
    else if (HLS.x < .5 )       return vec3(v1 + v2_v1*(unterzo-HLS.x),
                                             v2,
                                             v1 + v2_v1*(HLS.x-unterzo));
    else if (HLS.x < dueterzi ) return vec3(v1,
                                             v1 + v2_v1*(dueterzi-HLS.x),
                                             v2);
    else                        return vec3(v1,
                                             v1,
                                             v1 + v2_v1*(unterzo-HLS.x));
}

void textureBaseClass::genTex()
{
    if(generated) {
#if !defined(GLCHAOSP_LIGHTVER)
        glDeleteTextures(1,&texID);
        CHECK_GL_ERROR();
#else
        return;
#endif
    }

#ifdef GLAPP_REQUIRE_OGL45
    glCreateTextures(GL_TEXTURE_2D, 1, &texID);
#else
    glGenTextures(1, &texID);   // Generate OpenGL texture IDs
#endif

    generated = true;
}

void textureBaseClass::assignAttribs(GLint filterMin, GLint filterMag, GLint wrap) 
{
#ifdef GLAPP_REQUIRE_OGL45
    glTextureParameteri(texID, GL_TEXTURE_MAG_FILTER, filterMag);
    glTextureParameteri(texID, GL_TEXTURE_MIN_FILTER, filterMin);
    glTextureParameteri(texID, GL_TEXTURE_WRAP_S, wrap );
    glTextureParameteri(texID, GL_TEXTURE_WRAP_T, wrap );
#else
    glBindTexture(GL_TEXTURE_2D, texID);			// Bind Our Texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMag);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap );
#endif
}

void HLSTexture::buildTex(int size)
{
    genTex();
    vec3 *buffer = new vec3[size];

    for(int i=0;i<size; i++) buffer[i] = HLStoRGB(vec3((float)i/(float)size,.5f,.99f));
#ifdef GLAPP_REQUIRE_OGL45
    glTextureStorage2D(texID, 1, theApp->getPalInternalPrecision(), size, 1);
    glTextureSubImage2D(texID, 0, 0, 0, size, 1, GL_RGB, GL_FLOAT, buffer);
#else    
    //glActiveTexture(GL_TEXTURE0 + texID);
    glBindTexture(GL_TEXTURE_2D, texID);			// Bind Our Texture
    glTexImage2D(GL_TEXTURE_2D, 0, theApp->getPalInternalPrecision(), size, 1, 0, GL_RGB, GL_FLOAT, buffer);
#endif
    assignAttribs(GL_LINEAR, GL_LINEAR, GL_REPEAT);
    CHECK_GL_ERROR();

    texSize = size;

    delete[] buffer;
}

void RandomTexture::buildTex(int size)
{
    genTex();
    vec3 *buffer = new vec3[size];

    for(int i=0;i<size; i++) buffer[i] = (getRandomVector() + vec3(1.0f)) * .5f;

#ifdef GLAPP_REQUIRE_OGL45
    glTextureStorage2D(texID, 1, GL_RGB32F, size, 1);
    glTextureSubImage2D(texID, 0, 0, 0, size, 1, GL_RGB, GL_FLOAT, buffer);
#else
    //glActiveTexture(GL_TEXTURE0 + texID);
    glBindTexture(GL_TEXTURE_2D, texID);			// Bind Our Texture
    glTexImage2D(GL_TEXTURE_2D, 0, theApp->getPalInternalPrecision(), size, 1, 0, GL_RGB, GL_FLOAT, buffer);
#endif
    assignAttribs(GL_LINEAR, GL_LINEAR, GL_REPEAT);
    CHECK_GL_ERROR();

    texSize = size;

    delete[] buffer;
}

void paletteTexClass::buildTex(unsigned char *buffer, int size)
{
    genTex();
#ifdef GLAPP_REQUIRE_OGL45
    glTextureStorage2D(texID, 1, theApp->getPalInternalPrecision(), size, 1);
    glTextureSubImage2D(texID, 0, 0, 0, size, 1, GL_RGB, GL_UNSIGNED_BYTE, buffer);
#else
    //glActiveTexture(GL_TEXTURE0 + texID);
    glBindTexture(GL_TEXTURE_2D, texID);			// Bind Our Texture
    glTexImage2D(GL_TEXTURE_2D, 0, theApp->getPalInternalPrecision(), size, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, buffer);
#endif
    assignAttribs(GL_LINEAR, GL_LINEAR, GL_REPEAT);
    
    CHECK_GL_ERROR();

    texSize = size;
}

void paletteTexClass::buildTex(float *buffer, int size)
{
    genTex();
#ifdef GLAPP_REQUIRE_OGL45
    glTextureStorage2D(texID, 1, theApp->getPalInternalPrecision(), size, 1);
    glTextureSubImage2D(texID, 0, 0, 0, size, 1, GL_RGB, GL_FLOAT, buffer);
#else
    //glActiveTexture(GL_TEXTURE0 + texID);
    glBindTexture(GL_TEXTURE_2D, texID);			// Bind Our Texture
    glTexImage2D(GL_TEXTURE_2D, 0, theApp->getPalInternalPrecision(), size, 1, 0, GL_RGB, GL_FLOAT, buffer);

#endif
    assignAttribs(GL_NEAREST, GL_NEAREST, GL_REPEAT);
    CHECK_GL_ERROR();

    texSize = size;
}
