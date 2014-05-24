//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Text.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes
#include "Utilities.h"

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

void
CText::SetFontWidth(int _iWidth)
{
	assert(_iWidth > 0); //Invalid value.

	m_iFontWidth = _iWidth;

	UpdateFont();
}

void
CText::SetFontHeight(int _iHeight)
{
	assert(_iHeight > 0); //Invalid value.

	m_iFontHeight = _iHeight;

	UpdateFont();
}

void
CText::SetFont(int _iWidth, int _iHeight, ETextWeight _eWeight)
{
	SetFontWidth(_iWidth);
	SetFontHeight(_iHeight);
	SetFontWeight(_eWeight);
}

void
CText::SetFontWeight(ETextWeight _eWeight)
{
	if (_eWeight == TEXTWEIGHT_NORMAL)
	{
		m_iFontWeight = 100;
	}
	else if (_eWeight == TEXTWEIGHT_HEAVY)
	{
		m_iFontWeight = 900;
	}
	else
	{
		assert(false); //Invalid font weight.
	}

	UpdateFont();
}

void
CText::SetFontWeight(int _iWeight)
{
	m_iFontWeight = _iWeight;

	UpdateFont();
}

void
CText::SetFontItalic(bool _bItalic)
{
	m_byteItalic = (_bItalic == true) ? TRUE : FALSE;

	UpdateFont();
}

void
CText::SetFontUnderPlane(bool _bUnderPlane)
{
	m_byteUnderPlane = (_bUnderPlane == true) ? TRUE : FALSE;

	UpdateFont();

}

void
CText::SetFontStrikeOut(bool _bStrikeOut)
{
	m_byteStrikeOut = (_bStrikeOut == true) ? TRUE : FALSE;

	UpdateFont();
}

void
CText::SetTimeLifeSpan(float _fTimeSpan)
{
	assert(_fTimeSpan >= 0.0f); //Invalid value.

	m_fTimeLifeSpan = _fTimeSpan;
}

void
CText::SetDisplay(bool _bDisplay)
{
	m_bDisplay = _bDisplay;
}

int
CText::GetFontWidth() const
{
	return (m_iFontWidth);
}

int
CText::GetFontHeight() const
{
	return (m_iFontHeight);
}

int
CText::GetFontWeight() const
{
	return (m_iFontWeight);
}

bool
CText::IsFontItalic() const
{
	return (m_byteItalic == TRUE);
}

bool
CText::IsFontUnderPlane() const
{
	return (m_byteUnderPlane == TRUE);
}

bool 
CText::IsFontStrikeOut() const
{
	return (m_byteStrikeOut == TRUE);
}

bool
CText::IsDisplaying() const
{
	return (m_bDisplay);
}