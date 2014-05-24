//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   "-----"
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cassert>

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation
void
CSprite::SetPosition(int _iPositionX, int _iPositionY)
{
	m_iPositionX = _iPositionX;
	m_iPositionY = _iPositionY;
}

void
CSprite::SetPosition(float _fPositionX, float _fPositionY)
{
	SetPosition(static_cast<int>(_fPositionX), static_cast<int>(_fPositionY));
}

void
CSprite::TranslatePosition(int _iX, int _iY)
{
	SetPosition(m_iPositionX + _iX, m_iPositionY + _iY);
}

void
CSprite::TranslatePosition(float _fX, float _fY)
{
	SetPosition(m_iPositionX + static_cast<int>(_fX), m_iPositionY + static_cast<int>(_fY));
}

void
CSprite::SetFrameStartX(int _iFrameStartX)
{
	assert(_iFrameStartX >= 0); //Invalid value.

	m_iFrameStartX = _iFrameStartX;
}

void
CSprite::SetFrameStartY(int _iFrameStartY)
{
	assert(_iFrameStartY >= 0); //Invalid value.

	m_iFrameStartY = _iFrameStartY;
}

void
CSprite::SetFrameWidth(int _iFrameWidth)
{
	assert(_iFrameWidth > 0); //Invalid value.

	m_iFrameWidth = _iFrameWidth;
}

void
CSprite::SetFrameHeight(int _iFrameHeight)
{
	assert(_iFrameHeight > 0); //Invalid value.

	m_iFrameHeight = _iFrameHeight;
}

int
CSprite::GetPositionX() const
{
	return (m_iPositionX);
}
int
CSprite::GetPositionY() const
{
	return (m_iPositionY);
}

int
CSprite::GetFrameStartX() const
{
	return (m_iFrameStartX);
}

int
CSprite::GetFrameStartY() const
{
	return (m_iFrameStartY);
}

int
CSprite::GetFrameWidth() const
{
	return (m_iFrameWidth);
}

int
CSprite::GetFrameHeight() const
{
	return (m_iFrameHeight);
}

int
CSprite::GetSpriteWidth() const
{
	return (m_bmSprite.bmWidth);
}

int
CSprite::GetSpriteHeight() const
{
	return (m_bmSprite.bmHeight);
}

BITMAP
CSprite::GetSpriteBitmap() const
{
	return (m_bmSprite);
}