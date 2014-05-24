//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Referee.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_REFEREE_H__
#define __IGFEB11_IG220_REFEREE_H__

// Library Includes

// Local Includes
#include "GameDefines.h"

// Types

// Constants

// Prototypes
class CTable;

class CReferee
{
	// Member Functions
public:
	 CReferee();
	~CReferee();

	bool Initialise();
	bool Deinitialise();
	void Process(CTable* _pTable);
	void Draw();

	void ProcessBreak(CTable* _pTable);
	void ProcessPlayerTurn(CTable* _pTable);

	void ChangePlayerTurn(CTable* _pTable);

	bool IsCueBallPocketed(CTable* _pTable);
	bool IsEightBallPocketed(CTable* _pTable);
	bool IsFirstPocketedBallPlayerOwned(CTable* _pTable, EPlayer _ePlayer);
	bool IsFirstHitBallPlayerOwned(CTable* _pTable, EPlayer _ePlayer);
	bool IsRoundPocketedBallsPlayerOwned(CTable* _pTable, EPlayer _ePlayer);
	bool IsAllPlayersOwnedBallsPocketed(CTable* _pTable, EPlayer _ePlayer);

	EBallType GetFirstPocketedBallType(CTable* _pTable);
	int GetRoundNumCushionCollisions(CTable* _pTable);
	int GetRoundNumPocketedBalls(CTable* _pTable);
	int GetNumPlayerOwnedBallsRemaining(CTable* _pTable, EPlayer _ePlayer);

	void SetWinner(CTable* _pTable, EPlayer _ePlayer);

protected:

private:

	// Member Variables
public:

protected:
	bool m_bBreakFinished;

private:

};

#endif // __IGFEB11_IG220_REFEREE_H__