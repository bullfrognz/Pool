//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Referee.cpp
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework

// Core
#include "Text.h"

// Content
#include "Table.h"
#include "Ball.h"
#include "Player.h"

// This Include
#include "Referee.h"

// Static Variables

// Static Function Prototypes

// Implementation

CReferee::CReferee()
: m_bBreakFinished(false)
{
	//Empty
}

CReferee::~CReferee()
{
	//Empty
}

bool
CReferee::Initialise()
{
	//Empty

	return (true);
}

bool
CReferee::Deinitialise()
{
	//Empty

	return (true);
}

void
CReferee::Process(CTable* _pTable)
{
	EGameState eGameState = _pTable->GetGameState();

	switch (eGameState)
	{
	case GAMESTATE_BREAK:
		ProcessBreak(_pTable);
		break;

	case GAMESTATE_PLAYERTURN:
		ProcessPlayerTurn(_pTable);
		break;
	}

	_pTable->SetNewRound();
}

void
CReferee::Draw()
{
	//Emtpy
}

void
CReferee::ProcessBreak(CTable* _pTable)
{
	EPlayer ePlayerTurn = _pTable->GetPlayerTurn();
	int bNumBallPocketed = GetRoundNumPocketedBalls(_pTable);
	int iNumCushionHits = GetRoundNumCushionCollisions(_pTable);
	bool bEightPocketed = IsEightBallPocketed(_pTable);
	bool bCuePocketed = IsCueBallPocketed(_pTable);

	if (m_bBreakFinished == false)
	{
		if (bNumBallPocketed == 0 && iNumCushionHits < 4)
		{
			ChangePlayerTurn(_pTable);
			_pTable->RackBalls();
			_pTable->SetCueStartPosition();
			_pTable->ResetActiveBalls();
		}
		else if (bCuePocketed == true && bEightPocketed == false || bCuePocketed == true && bEightPocketed == true)
		{
			ChangePlayerTurn(_pTable);
			_pTable->RackBalls();
			_pTable->SetCueStartPosition();
			_pTable->ResetActiveBalls();
		}
		else if (bCuePocketed == false && bEightPocketed == true)
		{
			_pTable->RackBalls();
			_pTable->SetCueStartPosition();
			_pTable->ResetActiveBalls();
		}
		else
		{
			m_bBreakFinished = true;
		}
	}
	else
	{
		if (bEightPocketed == true)
		{
			EPlayer CurrentPlayer = (ePlayerTurn == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
			SetWinner(_pTable, CurrentPlayer);
		}
		else if (bCuePocketed == true)
		{
			ChangePlayerTurn(_pTable);
			_pTable->SetCueStartPosition();
		}
		else
		{
			if (bNumBallPocketed == 0)
			{
				ChangePlayerTurn(_pTable);
			}
			else
			{
				EPlayer eCurrentPlayerTurn = _pTable->GetPlayerTurn();

				EBallType eFirstPocketedBallType = GetFirstPocketedBallType(_pTable);

				_pTable->SetBallTypeOwner(eCurrentPlayerTurn, eFirstPocketedBallType);
				
				bool bRoundPocketedBallsPlayerOwned = IsRoundPocketedBallsPlayerOwned(_pTable, eCurrentPlayerTurn);

				if (bRoundPocketedBallsPlayerOwned == true)
				{
					_pTable->SetGameState(GAMESTATE_PLAYERTURN);
				}
				else
				{
					ChangePlayerTurn(_pTable);
					_pTable->SetGameState(GAMESTATE_PLAYERTURN);
				}
			}
		}
	}
}

void
CReferee::ProcessPlayerTurn(CTable* _pTable)
{
	EPlayer ePlayerTurn = _pTable->GetPlayerTurn();
	int bNumBallPocketed = GetRoundNumPocketedBalls(_pTable);
	int iNumCushionHits = GetRoundNumCushionCollisions(_pTable);
	bool bEightPocketed = IsEightBallPocketed(_pTable);
	bool bCueBallPocketed = IsCueBallPocketed(_pTable);
	int iNumBallBallCollisions = _pTable->GetRoundNumBallBallHits();

	bool bRoundPocketedBallsPlayerOwned = IsRoundPocketedBallsPlayerOwned(_pTable, ePlayerTurn);
	//bool bFirstHitBallPlayerOwned = IsFirstHitBallPlayerOwned(_pTable, ePlayerTurn);

	bool bAllPlayerOwnedBallsPocketed = IsAllPlayersOwnedBallsPocketed(_pTable, ePlayerTurn);

	if (bEightPocketed == true)
	{
		if (bCueBallPocketed == true)
		{
			EPlayer WinningPlayer = (ePlayerTurn == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
			SetWinner(_pTable, WinningPlayer);
		}
		else
		{
			if (bAllPlayerOwnedBallsPocketed == true)
			{
				SetWinner(_pTable, ePlayerTurn);
			}
			else
			{
				EPlayer WinningPlayer = (ePlayerTurn == PLAYER_ONE) ? PLAYER_TWO : PLAYER_ONE;
				SetWinner(_pTable, WinningPlayer);
			}
		}
	}
	else if (iNumBallBallCollisions < 0 || bCueBallPocketed == true)
	{
		ChangePlayerTurn(_pTable);
		_pTable->SetGameState(GAMESTATE_CUEINHAND);
	}
	else if (bNumBallPocketed > 0 && bRoundPocketedBallsPlayerOwned == true)
	{
		_pTable->SetGameState(GAMESTATE_PLAYERTURN);
	}
	else if (bNumBallPocketed > 0 && bRoundPocketedBallsPlayerOwned == false)
	{
		ChangePlayerTurn(_pTable);
		_pTable->SetGameState(GAMESTATE_CUEINHAND);
	}
	else
	{
		ChangePlayerTurn(_pTable);
		_pTable->SetGameState(GAMESTATE_PLAYERTURN);
	}
}


void
CReferee::ChangePlayerTurn(CTable* _pTable)
{
	EPlayer eCurrentPlayerTurn = _pTable->GetPlayerTurn();

	if (eCurrentPlayerTurn == PLAYER_ONE)
	{
		_pTable->SetPlayerTurn(PLAYER_TWO);
	}
	else
	{
		_pTable->SetPlayerTurn(PLAYER_ONE);
	}
}


bool
CReferee::IsCueBallPocketed(CTable* _pTable)
{
	std::vector<CBall*> vecPocketedBalls = _pTable->GetRoundPocketedBallsList();
	std::vector<CBall*>::iterator iterBall = vecPocketedBalls.begin();

	for (iterBall; iterBall != vecPocketedBalls.end(); ++iterBall)
	{
		EBallType _eBallType = (*iterBall)->GetBallType();

		if (_eBallType == BALLTYPE_CUE)
		{
			return (true);
		}
	}

	return (false);
}	

bool
CReferee::IsEightBallPocketed(CTable* _pTable)
{
	std::vector<CBall*> vecPocketedBalls = _pTable->GetPocketedBalls();
	std::vector<CBall*>::iterator iterBall = vecPocketedBalls.begin();

	for (iterBall; iterBall != vecPocketedBalls.end(); ++iterBall)
	{
		EBallType _eBallType = (*iterBall)->GetBallType();

		if (_eBallType == BALLTYPE_BLACK)
		{
			return (true);
		}
	}

	return (false);
}

bool
CReferee::IsFirstPocketedBallPlayerOwned(CTable* _pTable, EPlayer _ePlayer)
{
	std::vector<CBall*> vecBallPocketedList = _pTable->GetRoundPocketedBallsList();
	std::vector<CBall*>::iterator iterBall = vecBallPocketedList.begin();

	CPlayer& rPlayer = _pTable->GetPlayer(_ePlayer);

	EBallType _eBallType = (*iterBall)->GetBallType();
	EBallType _ePlayerBallType = rPlayer.GetBallOwnerType();

	if (_ePlayerBallType == _eBallType)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool
CReferee::IsFirstHitBallPlayerOwned(CTable* _pTable, EPlayer _ePlayer)
{
	std::vector<CBall*> vecCueBallHitList = _pTable->GetRoundCueBallHitList();

	if (vecCueBallHitList.empty() == true)
	{
		return (false);
	}

	std::vector<CBall*>::iterator iterHitBall = vecCueBallHitList.begin();

	CPlayer& rPlayer = _pTable->GetPlayer(_ePlayer);

	EBallType _eBallType = (*iterHitBall)->GetBallType();
	EBallType _ePlayerBallType = rPlayer.GetBallOwnerType();

	if (_ePlayerBallType == _eBallType)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}

bool
CReferee::IsRoundPocketedBallsPlayerOwned(CTable* _pTable, EPlayer _ePlayer)
{
	std::vector<CBall*> vecRoundPocketedBalls = _pTable->GetRoundPocketedBallsList();
	std::vector<CBall*>::iterator iterBall = vecRoundPocketedBalls.begin();

	CPlayer& rPlayer = _pTable->GetPlayer(_ePlayer);
	EBallType _ePlayerBallType = rPlayer.GetBallOwnerType();

	for (iterBall; iterBall != vecRoundPocketedBalls.end(); ++iterBall)
	{
		EBallType _eBallType = (*iterBall)->GetBallType();

		if (_eBallType != _ePlayerBallType)
		{
			return (false);
		}
	}

	return (true);
}

bool
CReferee::IsAllPlayersOwnedBallsPocketed(CTable* _pTable, EPlayer _ePlayer)
{
	std::vector<CBall*> vecActiveBalls = _pTable->GetActiveBalls();
	std::vector<CBall*>::iterator iterBall = vecActiveBalls.begin();

	CPlayer& rPlayer = _pTable->GetPlayer(_ePlayer);
	EBallType _ePlayerBallType = rPlayer.GetBallOwnerType();

	for (iterBall; iterBall != vecActiveBalls.end(); ++iterBall)
	{
		EBallType _eBallType = (*iterBall)->GetBallType();

		if (_eBallType == _ePlayerBallType)
		{
			return (false);
		}
	}

	return (true);
}

EBallType
CReferee::GetFirstPocketedBallType(CTable* _pTable)
{
	std::vector<CBall*> vecRoundPocketedBalls = _pTable->GetRoundPocketedBallsList();
	std::vector<CBall*>::iterator iterBall = vecRoundPocketedBalls.begin();

	if (iterBall == vecRoundPocketedBalls.end())
	{
		return (BALLTYPE_INVALID);
	}
	else
	{
		return ((*iterBall)->GetBallType());
	}
}

int
CReferee::GetRoundNumCushionCollisions(CTable* _pTable)
{
	int iValue = _pTable->GetRoundNumBallCushionHits();

	return (iValue);
}

int
CReferee::GetRoundNumPocketedBalls(CTable* _pTable)
{
	std::vector<CBall*> vecRoundPocketedBalls = _pTable->GetRoundPocketedBallsList();

	return (static_cast<int>(vecRoundPocketedBalls.size()));
}

int
CReferee::GetNumPlayerOwnedBallsRemaining(CTable* _pTable, EPlayer _ePlayer)
{
	std::vector<CBall*> vecActiveBalls = _pTable->GetActiveBalls();
	std::vector<CBall*>::iterator iterBall = vecActiveBalls.begin();

	CPlayer& rPlayer = _pTable->GetPlayer(_ePlayer);
	EBallType _ePlayerBallType = rPlayer.GetBallOwnerType();

	int iNumRemainingBalls = 0;
	for (iterBall; iterBall != vecActiveBalls.end(); ++iterBall)
	{
		EBallType _eBallType = (*iterBall)->GetBallType();

		if (_eBallType == _ePlayerBallType)
		{
			++ iNumRemainingBalls;
		}
	}

	return (iNumRemainingBalls);
}
	
void
CReferee::SetWinner(CTable* _pTable, EPlayer _ePlayer)
{
	char cBuffer[128];
	CText& rWinningText = _pTable->GetWinnerText();

	sprintf_s(cBuffer, 128, "PLAYER %d WINS!", _ePlayer + 1);

	rWinningText.SetText(cBuffer);
	rWinningText.SetDisplay(true);

	_pTable->SetStopGame(true);
}