//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SpriteCache.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_SPRITECACHE_H__
#define __IGFEB11_IG220_SPRITECACHE_H__

// Library Includes
#include <windows.h>

// Local Includes

// Types

// Constants

// Prototypes


class CSpriteCache
{
    // Member Functions
public:
	 CSpriteCache();
	~CSpriteCache();

	bool Intiialise(const int _kiSpriteResourceId, const int _kiMaskResourceId);
	bool Deintiialise();
	void Process();
	void Draw();

	// Member inline Functions
	inline HBITMAP GetHSprite();
	inline HBITMAP GetHSpriteMask();
	inline BITMAP GetBmSprite();
	inline BITMAP GetBmSpriteMask();

protected:

private:
	CSpriteCache(const CSpriteCache& _kr);
	CSpriteCache& operator= (const CSpriteCache& _kr);

    // Member Variables
public:

protected:

private:
	HBITMAP m_hSprite;
	HBITMAP m_hSpriteMask;

	BITMAP m_bmSprite;
	BITMAP m_bmSpriteMask;

};

#include "SpriteCache.inl"

#endif // __IGFEB11_IG220_SPRITECACHE_H__
