//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SpriteCache.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
	//Framework
	#include "Application.h"
	//Core
	//Game

// This Include
#include "SpriteCache.h"

// Static Variables

// Static Function Prototypes

// Implementation

CSpriteCache::CSpriteCache()
: m_hSprite(0)
, m_hSpriteMask(0)
{
	//Empty
}

CSpriteCache::~CSpriteCache()
{
	Deintiialise();
}

bool
CSpriteCache::Intiialise(const int _kiSpriteResourceId, const int _kiMaskResourceId)
{
	HINSTANCE hInstance = CApplication::GetInstance().GetInstanceHandle();

	m_hSprite = LoadBitmap(hInstance, MAKEINTRESOURCE(_kiSpriteResourceId));
	m_hSpriteMask = LoadBitmap(hInstance, MAKEINTRESOURCE(_kiMaskResourceId));

	GetObject(m_hSprite, sizeof(BITMAP), &m_bmSprite);
	GetObject(m_hSpriteMask, sizeof(BITMAP), &m_bmSpriteMask);

	return (true);
}

bool
CSpriteCache::Deintiialise()
{
	DeleteObject(m_hSprite);
	DeleteObject(m_hSpriteMask);

	return (true);
}

void
CSpriteCache::Process()
{
	//Empty
}

void
CSpriteCache::Draw()
{

	//Empty
}