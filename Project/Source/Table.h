//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Table.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_TABLE_H__
#define __IGFEB11_IG220_TABLE_H__

// Library Includes
#include <vector>

// Local Includes
#include "MessageTarget.h"
#include "GameDefines.h"
#include "Vector3.h"

// Types

// Constants

// Prototypes
class CLogManager;
class CSprite;
class CBall;
class CSphere;
class CPlane;
class CPlayer;
class CCue;
class CLine;
class CIniParser;
class CText;
class CReferee;
enum EGameState;
enum EPlayer;
enum EMouseButtonState;


class CTable : public IMessageTarget
{
    // Member Functions
public:
	 CTable();
	~CTable();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	bool InitialiseTableSprite();
	bool InitialiseBalls();
	bool InitialiseCushions();
	bool InitialisePockets();
	bool InitialisePlayers();
	bool InitialisePlayerBallTypeText();
	bool InitialiseCue();
	bool InitialiseTurnText();
	bool InitialisePocketedBallsText();
	bool IntiialiseWinnerText();

	bool DeinitialiseBalls();
	bool DeinitialiseCushions();
	bool DeinitialisePockets();

	void ProcessCue(float _fDeltaTick);
	void ProcessCueDirectionLine(float _fDeltaTick);
	void ProcessCueInHand();
	void ProcessPhysics(float _fDeltaTick);
	void ProcessBallPocket();

	void DrawBalls();
	void DrawCushions();
	void DrawCueDirectionLine();
	void DrawReplacePixel();

	void GetLowestImpactTimeSpherePlane(CSphere* _pSphere, float _fDeltaTick, CPlane*& _pImpactPlane ,float& _fLowestImpactTime);
	void GetLowestImpactTimeSphereSphere(CSphere* _pSphere, float _fDeltaTick, CSphere*& _pImpactSphere, float& _fLowestImpactTime);
	void GetLowestImpactTimeSpherePocketSphere(CSphere* _pSphere, float _fDeltaTick, CSphere*& _pImpactPocket, float& _fLowestImpactTime);
	void GetLowestImpactTimeLinePlane(CLine* _pLine, float _fDeltaTick, CPlane*& _pImpactPlane, float& _fLowestImpactTime);
	void GetLowestImpactTimeLineSphere(CLine* _pLine, float _fDeltaTick, CSphere*& _pImpactSphere, float& _fLowestImpactTime);

	void ProcessCueDirection();
	void ProcessCuePosition();
	void ProcessCueRelease(float _fDeltaTick);
	
	void ResetActiveBalls();
	void SetBallPocketed(CBall* _pBall);
	void ScanTable();
	void SetCueStartPosition();
	void RackBalls();
	void SetBallTypeOwner(EPlayer _ePlayer, EBallType _eBallType);
	void SetPlayerTurn(EPlayer _ePlayer);
	void SetNewRound();

	bool IsBallsCurrentlyMoving();
	bool IsBallPocketed(CBall* _pBall);
	bool AllowCuePlaement();
	bool AllowCuePlaementRegular();
	bool AllowCuePlaementAlternate();

	virtual void HandleMessage(EKeyCode _EKeyCode, WPARAM _wParam, LPARAM _lParam);

	// Inline Functions
	inline void SetLogManager(CLogManager* _pLogManager)
	{
		m_pLogManager = _pLogManager;
	}

	inline void SetGameState(EGameState _eGameState);

	inline CPlayer& GetPlayer(EPlayer _ePlayerId);
	inline std::vector<CBall*>& GetActiveBalls();
	inline std::vector<CBall*>&	GetPocketedBalls();
	inline EGameState GetGameState();
	inline EPlayer GetPlayerTurn();
	inline int GetRoundNumBallCushionHits();
	inline int GetRoundNumBallBallHits();
	inline std::vector<CBall*>& GetRoundCueBallHitList();
	inline std::vector<CBall*>& GetRoundPocketedBallsList();

	inline void SetPlaneLineDisplay(bool _bValue);

	inline void SetStopGame(bool _bValue);
	inline CText& GetWinnerText();

protected:

private:
	CTable(const CTable& _kr);
	CTable& operator= (const CTable& _kr);

    // Member Variables
public:

protected:

private:
	CText* m_pWinnerText;

	CLogManager* m_pLogManager;					// 4
	CSprite* m_pTableSprite;					// 4
	CPlayer* m_pPlayer[PLAYER_MAX];				// 8
	CText* m_pPlayerBallType[PLAYER_MAX];

	CReferee* m_pReferee;

	CText* m_pTurnText;
	CText* m_pTextPocketedBalls;
	
	CCue* m_pCue;								// 4
	float m_fCueForce;							// 4
	ECueState m_eCueState;
	bool bLockCueDirection;
	float m_fCueImpactTime;

	int m_iNumCushions;							// 4
	CPlane* m_pCushion[100];					// 400

	CBall* m_pBall[BALL_MAX];					// 64
	std::vector<CBall*> m_vecActiveBalls;
	std::vector<CBall*> m_vecPocketedBalls;

	CSphere* m_pPocket[100];					// 400
	int m_iNumPockets;							// 4

	EGameState m_eGameState;					// 4
	EGameState m_ePrevGameState;
	EPlayer	   m_ePlayerTurn;					// 4
	ETableType m_eTableType;					// 4

	CIniParser* m_pTableSpriteParser;			// 4

	int m_iNumBallsPocketed;

	CVector3 m_MousePosition;					// 12
	CVector3 m_PrevMousePosition;				// 12
	CVector3 m_MouseDownPosition;				// 12
	CVector3 m_MouseUpPosition;					// 12
	EMouseButtonState m_eMouseLeftState;		// 12
	EMouseButtonState m_ePrevMouseLeftState;	// 4
	EMouseButtonState m_eMouseRightState;		// 4
	EMouseButtonState m_ePrevMouseRightState;	// 4

	int m_iRoundNumBallCushionHits;
	int m_iRoundNumBallBallHits;
	std::vector<CBall*> m_vecRoundCueBallHitList;
	std::vector<CBall*> m_vecRoundPocketedBallsList;

	std::vector<COORD> m_vecReplacePixel;

	bool m_bShowDebugCushions;
	bool m_bStopGame;

};

#include "Table.inl"

#endif // __IGFEB11_IG220_TABLE_H__
