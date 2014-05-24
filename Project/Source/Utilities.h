//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Utilities.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_UTILITIES_H__
#define __IGFEB11_IG220_UTILITIES_H__

// Library Includes
#include <cassert>
#include <windows.h>
#include <ctime>

// Local Includes
#include "Vector3.h"

// Types

// Constants

// Prototypes
wchar_t* ConvertConstCharToWchart(const char* _kcpText);

char* ConvertWchartToChar(wchar_t* _wcText);

int GenerateRandomNumber(int _iMin, int _iMax);

int ConvertCharIntSum(const char* _cpString);

bool IsCollisionBetweenCircles(float _iX1, float _iY1, float _iX2, float _iY2, float _fRadius1, float _fRadius2);

float GetDistanceBetweenTwoPoints(float _iX1, float _iY1, float _iX2, float _iY2);

bool IsWithinBounds(RECT _rectBounds, int _iPositionX, int _iPositionY);
bool IsWithinBounds(RECT _rectBounds, float _fPositionX, float _fPositionY);
bool IsWithinBounds(RECT _rectBounds, COORD _coordPosition);

float DotProduct(CVector3& _rVect31, CVector3& _rVect32);

void RunTestHarness();

#endif // __IGFEB11_IG220_UTILITIES_H__