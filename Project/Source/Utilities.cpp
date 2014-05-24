//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Utilities.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>
#include <iostream>
#include <cmath>

// Local Includes

// This Include
#include "Utilities.h"

// Static Variables

// Static Function Prototypes

// Implementation
wchar_t* ConvertConstCharToWchart(const char* _kcpText)
{
	int iCharStrLen = static_cast<int>(strlen(_kcpText)) + 1;

	wchar_t* wchrpText = new wchar_t[iCharStrLen];

	for (int I = 0; I < iCharStrLen; ++I)
	{
		wchrpText[I] = _kcpText[I];
	}

	return (wchrpText);
}

char* ConvertWchartToChar(wchar_t* _wcText)
{
	int iWCharStrLen = static_cast<int>(wcslen(_wcText)) + 1;

	char* kcpText = new char[iWCharStrLen];

	for (int I = 0; I < iWCharStrLen; ++I)
	{
		kcpText[I] = static_cast<char>(_wcText[I]);
	}

	return (kcpText);
}

int GenerateRandomNumber(int _iMin ,int _iMax)
{
	assert(_iMax >= _iMin); //Invalid values.

	if (_iMin == _iMax)
	{
		return (_iMax);
	}

	int iRandomValue = 0;
	iRandomValue  = rand() % ((_iMax + 1) - _iMin);
	iRandomValue += _iMin;

	return (iRandomValue);
}

int ConvertCharIntSum(const char* _cpString)
{
	int iCharStrLen = static_cast<int>(strlen(_cpString) + 1);

	int iIntSum = 0;

	for (int i = 0; i < iCharStrLen; ++i)
	{
		iIntSum += static_cast<int>(_cpString[i]);
	}

	return (iIntSum);
}

bool IsCollisionBetweenCircles(float _iX1, float _iY1, float _iX2, float _iY2, float _fRadius1, float _fRadius2)
{
	if (_fRadius1 == 0.0f || _fRadius2 == 0.0f)
	{
		return (false);
	}

	float fDifferenceX = _iX2 - _iX1;
	float fDifferenceY = _iY2 - _iY1;

	if ((fDifferenceX * fDifferenceX) + (fDifferenceY * fDifferenceY) < (_fRadius1 * _fRadius2))
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

float GetDistanceBetweenTwoPoints(float _iX1, float _iY1, float _iX2, float _iY2)
{
	float fDistanceX = _iX2 - _iX1;
	float fDistanceY = _iY2 - _iY1;

	fDistanceY *= -1;

	fDistanceX = pow(fDistanceX, 2);
	fDistanceY = pow(fDistanceY, 2);

	float fDistanceTotal = sqrt( (fDistanceX + fDistanceY) );

	return (fDistanceTotal);
}

bool IsWithinBounds(RECT _rectBounds, int _iPositionX, int _iPositionY)
{
	if (_rectBounds.top    < _iPositionY &&
		_rectBounds.bottom > _iPositionY &&
		_rectBounds.left   < _iPositionX &&
		_rectBounds.right  > _iPositionX)
	{
		return (true);
	}

	return (false);
}

bool IsWithinBounds(RECT _rectBounds, float _fPositionX, float _fPositionY)
{
	int iPositionX = static_cast<int>(_fPositionX);
	int iPositionY = static_cast<int>(_fPositionY);

	return (IsWithinBounds(_rectBounds, iPositionX, iPositionY));
}

bool IsWithinBounds(RECT _rectBounds, COORD _coordPosition)
{
	int iPositionX = static_cast<int>(_coordPosition.X);
	int iPositionY = static_cast<int>(_coordPosition.Y);

	return (IsWithinBounds(_rectBounds, iPositionX, iPositionY));
}

float DotProduct(CVector3& _rVect31, CVector3& _rVect32)
{
	float fX1 = _rVect31[X];
	float fY1 = _rVect31[Y];
	float fZ1 = _rVect31[Z];

	float fX2 = _rVect32[X];
	float fY2 = _rVect32[Y];
	float fZ2 = _rVect32[Z];

	float fResult = fX1*fX2 + fY1*fY2 + fZ1*fZ2;

	return (fResult);
}

void RunTestHarness()
{

}