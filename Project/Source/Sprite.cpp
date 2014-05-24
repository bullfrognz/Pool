//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Sprite.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <map>

// Local Includes
#include "Application.h"
#include "GameWindow.h"
#include "BackBuffer.h"
#include "SpriteCache.h"

// This Include
#include "Sprite.h"

// Static Variables

// Static Function Prototypes
std::map<int, CSpriteCache*> CSprite::s_mapSpriteCache;
HDC CSprite::s_hSharedSpriteDC = 0;
int CSprite::s_iRefCount = 0;

// Implementation
CSprite::CSprite()
: m_iPositionX(0)
, m_iPositionY(0)
, m_iFrameStartX(0)
, m_iFrameStartY(0)
, m_iFrameWidth(0)
, m_iFrameHeight(0)
{
	if (s_iRefCount == 0)
	{
		s_hSharedSpriteDC = CreateCompatibleDC(NULL);
	}

	++ s_iRefCount;
}

CSprite::~CSprite()
{
	-- s_iRefCount;

	if (s_iRefCount == 0)
	{
		DeleteDC(s_hSharedSpriteDC);
		s_hSharedSpriteDC = 0;

		ClearCache();
	}
}

bool
CSprite::Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId)
{
	if (IsCached(_kiSpriteResourceId) == false)
	{
		Cache(_kiSpriteResourceId, _kiMaskResourceId);
	}

	CSpriteCache& rSpriteCache = GetSpriteCache(_kiSpriteResourceId);

	m_hSprite = rSpriteCache.GetHSprite();
	m_hMask   = rSpriteCache.GetHSpriteMask();

	m_bmSprite = rSpriteCache.GetBmSprite();
	m_bmMask   = rSpriteCache.GetBmSpriteMask();

	m_iFrameWidth = GetSpriteWidth();
	m_iFrameHeight = GetSpriteHeight();

	return (true);
}

void
CSprite::Process(float _fDeltaTick)
{
	//Empty
}

void
CSprite::Draw()
{
	int iWidth  = GetSpriteWidth();
	int iHeight = GetSpriteHeight();

	int iPositionX = m_iPositionX - (m_iFrameWidth / 2);
	int iPositionY = m_iPositionY - (m_iFrameHeight / 2);

	CBackBuffer& rBackBuffer = CApplication::GetInstance().GetGameWindow().GetBackBuffer();

	HGDIOBJ hOldObject = SelectObject(s_hSharedSpriteDC, m_hMask);

	BitBlt(rBackBuffer.GetBFDC(), iPositionX, iPositionY, m_iFrameWidth, m_iFrameHeight, s_hSharedSpriteDC, m_iFrameStartX, m_iFrameStartY, SRCAND);

	SelectObject(s_hSharedSpriteDC, m_hSprite);

	BitBlt(rBackBuffer.GetBFDC(), iPositionX, iPositionY, m_iFrameWidth, m_iFrameHeight, s_hSharedSpriteDC, m_iFrameStartX, m_iFrameStartY, SRCPAINT);

	SelectObject(s_hSharedSpriteDC, hOldObject);
}

bool
CSprite::IsCached(const int _kiSpriteResourceId)
{
	std::map<int, CSpriteCache*>::iterator Iter;

	Iter = s_mapSpriteCache.find(_kiSpriteResourceId);

	if (Iter == s_mapSpriteCache.end())
	{
		return (false);
	}

	return (true);
}

void
CSprite::Cache(const int _kiSpriteResourceId, const int _kiMaskResourceId)
{
	CSpriteCache* pSpriteCache = new CSpriteCache();

	(*pSpriteCache).Intiialise(_kiSpriteResourceId, _kiMaskResourceId);

	s_mapSpriteCache.insert( std::pair<int, CSpriteCache*>(_kiSpriteResourceId, pSpriteCache) );
}

CSpriteCache&
CSprite::GetSpriteCache(const int _kiSpriteResourceId)
{
	std::map<int, CSpriteCache*>::iterator Iter;

	Iter = s_mapSpriteCache.find(_kiSpriteResourceId);

	return (*Iter->second);
}

void
CSprite::ClearCache()
{
	std::map<int, CSpriteCache*>::iterator Iter;

	for (Iter = s_mapSpriteCache.begin(); Iter != s_mapSpriteCache.end(); )
	{
		delete (*Iter).second;
		(*Iter).second = 0;

		Iter = s_mapSpriteCache.erase(Iter);
	}
}

COLORREF
CSprite::GetPixelColour(int _iX, int iY)
{
	HGDIOBJ hGDIObj = SelectObject(s_hSharedSpriteDC, m_hSprite);

	COLORREF crColour = ::GetPixel(s_hSharedSpriteDC, _iX, iY);

	SelectObject(s_hSharedSpriteDC, hGDIObj);

	return (crColour);
}