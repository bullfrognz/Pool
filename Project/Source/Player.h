//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   CPlayer.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_PLAYER_H__
#define __IGFEB11_IG220_PLAYER_H__

// Library Includes

// Local Includes
#include "GameDefines.h"

// Types

// Constants

// Prototypes
class CText;

class CPlayer
{
	// Member Functions
public:
	 CPlayer();
	~CPlayer();

	bool Initialise(EPlayer _ePlayerId);
	bool Deinitialise();
	void Process(float _fDeltaTick);
	void Draw();


	// Inline
	inline void SetBallOwnerType(EBallType m_eType);

	inline EBallType GetBallOwnerType();
	inline CText& GetNameText();

protected:

private:

	// Member Variables
public:

protected:

private:
	char m_cPlayerName[64];

	CText* m_pNameText;

	EBallType m_eBallOwnerType;

	// Static
	static int s_iRefCount;

};

#include "Player.inl"

#endif // __IGFEB11_IG220_-----_H__