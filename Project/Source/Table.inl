//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   ------.inl
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework

// Core

// Content

// Static Variables

// Static Function Prototypes

// Implementation


void
CTable::SetGameState(EGameState _eGameState)
{
	m_ePrevGameState = m_eGameState;
	m_eGameState = _eGameState;
}

CPlayer&
CTable::GetPlayer(EPlayer _ePlayerId)
{
	return (*m_pPlayer[_ePlayerId]);
}

std::vector<CBall*>&
CTable::GetActiveBalls()
{
	return (m_vecActiveBalls);
}

std::vector<CBall*>&
CTable::GetPocketedBalls()
{
	return (m_vecPocketedBalls);
}

EGameState
CTable::GetGameState()
{
	return (m_eGameState);
}

EPlayer
CTable::GetPlayerTurn()
{
	return (m_ePlayerTurn);
}

int
CTable::GetRoundNumBallCushionHits()
{
	return (m_iRoundNumBallCushionHits);
}

int
CTable::GetRoundNumBallBallHits()
{
	return (m_iRoundNumBallBallHits);
}

std::vector<CBall*>&
CTable::GetRoundCueBallHitList()
{
	return (m_vecRoundCueBallHitList);
}

std::vector<CBall*>&
CTable::GetRoundPocketedBallsList()
{
	return (m_vecRoundPocketedBallsList);
}

void
CTable::SetPlaneLineDisplay(bool _bValue)
{
	m_bShowDebugCushions = _bValue;
}

void
CTable::SetStopGame(bool _bValue)
{
	m_bStopGame = _bValue;
}

CText&
CTable::GetWinnerText()
{
	return (*m_pWinnerText);
}