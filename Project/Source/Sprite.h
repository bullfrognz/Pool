//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Sprite.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_SPRITE_H__
#define __IGFEB11_IG220_SPRITE_H__

// Library Includes
#include <windows.h>
#include <map>

// Local Includes

// Types

// Constants

// Prototypes
class CSpriteCache;

class CSprite
{
    // Member Functions
public:
	         CSprite();
	virtual ~CSprite();

	virtual bool Initialise(const int _kiSpriteResourceId, const int _kiMaskResourceId);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	bool IsCached(const int _kiSpriteResourceId);
	void Cache(const int _kiSpriteResourceId, const int _kiMaskResourceId);
	CSpriteCache& GetSpriteCache(const int _kiSpriteResourceId);

	COLORREF GetPixelColour(int _iX, int iY);

	static void ClearCache();

	// Member inline Functions
	inline void SetPosition(int _iPositionX, int _iPositionY);
	inline void SetPosition(float _fPositionX, float _fPositionY);
	inline void TranslatePosition(int _iX, int _iY);
	inline void TranslatePosition(float _fX, float _fY);

	inline void SetFrameStartX(int _iFrameStartX);
	inline void SetFrameStartY(int _iFrameStartY);

	inline void SetFrameWidth(int _iFrameWidth);
	inline void SetFrameHeight(int _iFrameHeight);

	inline int GetPositionX() const;
	inline int GetPositionY() const;

	inline int GetFrameStartX() const;
	inline int GetFrameStartY() const;

	inline int GetFrameWidth() const;
	inline int GetFrameHeight() const;

	inline int GetSpriteWidth() const;
	inline int GetSpriteHeight() const;

	inline BITMAP GetSpriteBitmap() const;

protected:

private:
	CSprite(const CSprite& _kr);
	CSprite& operator= (const CSprite& _kr);

    // Member Variables
public:

protected:
	HBITMAP m_hSprite;
	HBITMAP m_hMask;

	BITMAP m_bmSprite;
	BITMAP m_bmMask;

	int m_iPositionX;
	int m_iPositionY;

	int m_iFrameStartX;
	int m_iFrameStartY;

	int m_iFrameWidth;
	int m_iFrameHeight;

	static std::map<int, CSpriteCache*> s_mapSpriteCache;
	static int s_iRefCount;
	static HDC s_hSharedSpriteDC;

private:

};

#include "Sprite.inl"

#endif // __IGFEB11_IG220_SPRITE_H__
