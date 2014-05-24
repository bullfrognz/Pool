//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SpriteCache.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation
HBITMAP
CSpriteCache::GetHSprite()
{
	return (m_hSprite);
}

HBITMAP
CSpriteCache::GetHSpriteMask()
{
	return (m_hSpriteMask);
}

BITMAP
CSpriteCache::GetBmSprite()
{
	return (m_bmSprite);
}

BITMAP
CSpriteCache::GetBmSpriteMask()
{
	return (m_bmSpriteMask);
}