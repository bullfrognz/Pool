//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Button.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG120_BUTTON_H__
#define __IGFEB11_IG120_BUTTON_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "MessageTarget.h"
#include "Entity.h"
#include "Sprite.h"

// Types

// Constants

// Prototypes
class CSprite;

class CButton : public CEntity, public IMessageTarget
{
    // Member Functions
public:
	CButton();
	~CButton();

	void Denitialise();

	virtual bool Initialise(const int _kiSpriteId, const int _kiMaskId);
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	void UpdateBounds();

	virtual void HandleMessage(EKeyCode _eMessageCode, WPARAM _wParam, LPARAM _lParam);

	// Member Inline Functions
	inline void SetDisplay(bool _bDisplay);

	inline bool HasBeenClicked() const;

	inline bool IsDisplaying() const;

protected:

private:

    // Member Variables
public:

protected:

private:
	RECT m_rectBounds;

	COORD m_crdMousePositionUp;
	COORD m_crdMousePositionDwn;

	CSprite* m_pSprite;

	bool m_bHasBeenClicked;

	bool m_bDisplay;

};

#include "Button.inl"

#endif // __IGFEB11_IG120_BUTTON_H__
