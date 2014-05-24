//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Table.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cmath>
#include <map>
#include <vector>

// Local Includes
#include "Resource.h"

// Framework
#include "IniParser.h"
#include "LogManager.h"
#include "Application.h"
#include "MessageManager.h"
#include "GameWindow.h"
#include "Sprite.h"
#include "Utilities.h"
#include "BackBuffer.h"

// Core
#include "Plane.h"
#include "Ball.h"
#include "PhysicsEngine.h"
#include "Line.h"
#include "Text.h"

// Scene
#include "Player.h"
#include "Cue.h"
#include "GameDefines.h"
#include "Referee.h"

// This Include
#include "Table.h"

// Static Variables

// Static Function Prototypes

// Implementation

CTable::CTable()
: m_pTableSprite(0)
, m_iNumCushions(0)
, m_pCue(0)
, m_ePlayerTurn(PLAYER_INVALID)
, m_eMouseLeftState(MBS_IDLE)
, m_fCueForce(0)
, m_pTableSpriteParser(0)
, m_iNumPockets(0)
, bLockCueDirection(false)
, m_eCueState(CUESTATE_CHOOSEANGLE)
, m_fCueImpactTime(0)
, m_iNumBallsPocketed(0)
, m_iRoundNumBallCushionHits(0)
, m_bShowDebugCushions(false)
, m_bStopGame(false)
{
	//Empty
}

CTable::~CTable()
{
	Deinitialise();
}

bool
CTable::Initialise()
{
	m_eGameState = GAMESTATE_INITIALISE;

	int iTableType = 1;

	CIniParser& rIniGameSettings = CApplication::GetInstance().GetIniParser();
	rIniGameSettings.GetValue("Table", "TableType", iTableType);
	rIniGameSettings.GetValue("Table", "DebugCushions", m_bShowDebugCushions);

	if (iTableType == 1 || iTableType == 2)
	{
		m_eTableType = (iTableType == 1) ? TABLETYPE_REGULAR : TABLETYPE_ALTERNATE;
	}
	else
	{
		m_eTableType = TABLETYPE_REGULAR;
	}

	InitialiseTableSprite();
	
	m_pTableSpriteParser = new CIniParser();
	m_pTableSpriteParser->LoadIniFile("TableData.ini");

	bool bTableScanCached = false;
	m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], "Scanned", bTableScanCached);

	if (bTableScanCached == false)
	{
		ScanTable();
	}

	InitialiseBalls();
	InitialiseCushions();
	InitialisePockets();
	InitialisePlayers();
	InitialisePlayerBallTypeText();
	InitialiseCue();
	InitialiseTurnText();
	InitialisePocketedBallsText();
	IntiialiseWinnerText();

	m_pReferee = new CReferee();
	m_pReferee->Initialise();

	CMessageManager& rMessageManager = CApplication::GetInstance().GetGameWindow().GetMsgManager();
	rMessageManager.AddMsgTarget(MSG_MOUSE_MOVE, this);
	rMessageManager.AddMsgTarget(MSG_MOUSE_LBUTTONDWN, this);
	rMessageManager.AddMsgTarget(MSG_MOUSE_LBUTTONUP, this);

	m_eGameState = GAMESTATE_BREAK;

	return (true);
}

bool
CTable::Deinitialise()
{
	DeinitialiseBalls();
	DeinitialiseCushions();
	DeinitialisePockets();

	delete m_pWinnerText;
	m_pWinnerText = 0;

	delete m_pPlayer[PLAYER_ONE];
	m_pPlayer[PLAYER_ONE] = 0;

	delete m_pPlayer[PLAYER_TWO];
	m_pPlayer[PLAYER_TWO] = 0;
	
	delete m_pTableSprite;
	m_pTableSprite = 0;

	delete m_pCue;
	m_pCue = 0;

	m_pTableSpriteParser->CloseFile(true);
	delete m_pTableSpriteParser;
	m_pTableSpriteParser = 0;

	delete m_pPlayerBallType[PLAYER_ONE];
	m_pPlayerBallType[PLAYER_ONE] = 0;

	delete m_pPlayerBallType[PLAYER_TWO];
	m_pPlayerBallType[PLAYER_TWO] = 0;

	delete m_pReferee;
	m_pReferee = 0;

	delete m_pTurnText;
	m_pTurnText = 0;

	delete m_pTextPocketedBalls;
	m_pTextPocketedBalls = 0;

	CApplication::GetInstance().GetGameWindow().GetMsgManager().RemoveMsgTarget(this);

	return (true);
}

void
CTable::Process(float _fDeltaTick)
{
	if (m_bStopGame == true)
	{
		return ;
	}

	switch (m_eGameState)
	{
	case GAMESTATE_BREAK: //Fall through


	case GAMESTATE_PLAYERTURN:
		{
			m_pCue->SetDisplay(true);
			ProcessCue(_fDeltaTick);
			ProcessCueDirectionLine(_fDeltaTick);
			break;
		}

	case GAMESTATE_PROCESSINGPHYSICS:
		{
			ProcessPhysics(_fDeltaTick);

			if (IsBallsCurrentlyMoving() == false)
			{
				m_eGameState = m_ePrevGameState;
				m_pReferee->Process(this);
			}
			break;
		}

	case GAMESTATE_CUEINHAND:
		{
			ProcessCueInHand();
			break;
		}
	}

	m_pWinnerText->Process(_fDeltaTick);

	m_PrevMousePosition = m_MousePosition;
	m_ePrevMouseLeftState = m_eMouseLeftState;
	m_ePrevMouseRightState = m_eMouseRightState;

	if (m_eMouseLeftState == MBS_RELEASED)
	{
		m_eMouseLeftState = MBS_IDLE;
	}
}

void
CTable::Draw()
{
	m_pPlayer[PLAYER_ONE]->Draw();
	m_pPlayer[PLAYER_TWO]->Draw();
	m_pPlayerBallType[PLAYER_ONE]->Draw();
	m_pPlayerBallType[PLAYER_TWO]->Draw();
	m_pTurnText->Draw();
	m_pTableSprite->Draw();
	DrawReplacePixel();
	DrawBalls();

	if (m_bShowDebugCushions == true)
	{
		DrawCushions();
	}

	m_pTextPocketedBalls->Draw();

	m_pLogManager->WriteVariable("Game State", m_eGameState);

	switch (m_eGameState)
	{
	case GAMESTATE_BREAK: //Fall through
		
	case GAMESTATE_PLAYERTURN:
		{
			DrawCueDirectionLine();
			m_pCue->Draw();
			break;
		}

	case GAMESTATE_PROCESSINGPHYSICS:
		{

			break;
		}

	case GAMESTATE_CUEINHAND:
		{
			break;
		}
	}

	m_pWinnerText->Draw();
}

bool
CTable::InitialiseTableSprite()
{
	const int kiWindowWidth = CApplication::GetInstance().GetGameWindow().GetWidth();
	const int kiWindowHeight = CApplication::GetInstance().GetGameWindow().GetHeight();

	m_pTableSprite = new CSprite;

	switch (m_eTableType)
	{
	case TABLETYPE_REGULAR:
		m_pTableSprite->Initialise(IDB_POOLTABLE, IDB_POOLTABLEMASK);
		break;

	case TABLETYPE_ALTERNATE:
		m_pTableSprite->Initialise(IDB_POOLTABLE_ALTERNATE, IDB_POOLTABLE_ALTERNATEMASK);
		break;

	}

	m_pTableSprite->SetPosition(kiWindowWidth / 2.0f, kiWindowHeight / 2.0f);

	return (true);
}

bool
CTable::InitialiseBalls()
{
	float fBallFriction = 60.0f;
	float fBallMass = 10.0f;
	float fBallRadius = 8.0f;

	const char kcGroup[] = "Table";
	CIniParser& rIniGameSettings = CApplication::GetInstance().GetIniParser();
	rIniGameSettings.GetValue(kcGroup, "BallFriction", fBallFriction);
	rIniGameSettings.GetValue(kcGroup, "BallMass", fBallMass);
	rIniGameSettings.GetValue(kcGroup, "BallRadius", fBallRadius);

	// Initialise ball instances
	for (int i = BALL_CUE; i < BALL_MAX; ++i)
	{
		m_pBall[i] = new CBall();
		m_pBall[i]->SetRadius(fBallRadius);
		m_pBall[i]->SetFriction(fBallFriction);
		m_pBall[i]->SetMass(fBallMass);

		m_vecActiveBalls.push_back(m_pBall[i]);
	}
	
	// Initialise ball sprite images
	m_pBall[BALL_CUE]->Initialise(IDB_BALLWHITE, IDB_BALLMASK);
	m_pBall[BALL_CUE]->SetBallType(BALLTYPE_CUE);
	m_pBall[BALL_01]->Initialise(IDB_BALL01, IDB_BALLMASK);
	m_pBall[BALL_01]->SetBallType(BALLTYPE_SOLID);
	m_pBall[BALL_02]->Initialise(IDB_BALL02, IDB_BALLMASK);
	m_pBall[BALL_02]->SetBallType(BALLTYPE_SOLID);
	m_pBall[BALL_03]->Initialise(IDB_BALL03, IDB_BALLMASK);
	m_pBall[BALL_03]->SetBallType(BALLTYPE_SOLID);
	m_pBall[BALL_04]->Initialise(IDB_BALL04, IDB_BALLMASK);
	m_pBall[BALL_04]->SetBallType(BALLTYPE_SOLID);
	m_pBall[BALL_05]->Initialise(IDB_BALL05, IDB_BALLMASK);
	m_pBall[BALL_05]->SetBallType(BALLTYPE_SOLID);
	m_pBall[BALL_06]->Initialise(IDB_BALL06, IDB_BALLMASK);
	m_pBall[BALL_06]->SetBallType(BALLTYPE_SOLID);
	m_pBall[BALL_07]->Initialise(IDB_BALL07, IDB_BALLMASK);
	m_pBall[BALL_07]->SetBallType(BALLTYPE_SOLID);
	m_pBall[BALL_08]->Initialise(IDB_BALL08, IDB_BALLMASK);
	m_pBall[BALL_08]->SetBallType(BALLTYPE_BLACK);
	m_pBall[BALL_09]->Initialise(IDB_BALL09, IDB_BALLMASK);
	m_pBall[BALL_09]->SetBallType(BALLTYPE_STRIPE);
	m_pBall[BALL_10]->Initialise(IDB_BALL10, IDB_BALLMASK);
	m_pBall[BALL_10]->SetBallType(BALLTYPE_STRIPE);
	m_pBall[BALL_11]->Initialise(IDB_BALL11, IDB_BALLMASK);
	m_pBall[BALL_11]->SetBallType(BALLTYPE_STRIPE);
	m_pBall[BALL_12]->Initialise(IDB_BALL12, IDB_BALLMASK);
	m_pBall[BALL_12]->SetBallType(BALLTYPE_STRIPE);
	m_pBall[BALL_13]->Initialise(IDB_BALL13, IDB_BALLMASK);
	m_pBall[BALL_13]->SetBallType(BALLTYPE_STRIPE);
	m_pBall[BALL_14]->Initialise(IDB_BALL14, IDB_BALLMASK);
	m_pBall[BALL_14]->SetBallType(BALLTYPE_STRIPE);
	m_pBall[BALL_15]->Initialise(IDB_BALL15, IDB_BALLMASK);
	m_pBall[BALL_15]->SetBallType(BALLTYPE_STRIPE);

	SetCueStartPosition();
	RackBalls();

	return (true);
}

bool
CTable::InitialiseCushions()
{
	int iPlaneStartX = 0;
	int iPlaneStartY = 0;
	int iPlaneEndX = 0;
	int iPlaneEndY = 0;

	char cBuffer[128];
	int iMaxPlanes = 100;
	
	for (int i = 0; i < iMaxPlanes; ++i)
	{
		iPlaneStartX = 0;
		iPlaneStartY = 0;
		iPlaneEndX = 0;
		iPlaneEndY = 0;

		sprintf_s(cBuffer, 128, "Plane%dStartX", i);
		m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], cBuffer, iPlaneStartX);

		sprintf_s(cBuffer, 128, "Plane%dStartY", i);
		m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], cBuffer, iPlaneStartY);

		sprintf_s(cBuffer, 128, "Plane%dEndX", i);
		m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], cBuffer, iPlaneEndX);

		sprintf_s(cBuffer, 128, "Plane%dEndY", i);
		m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], cBuffer, iPlaneEndY);

		if (iPlaneStartX != false && iPlaneStartY != false && iPlaneEndX != false && iPlaneEndY != false)
		{
			m_pCushion[i] = new CPlane();

			CVector3 StartPoint(static_cast<float>(iPlaneStartX), static_cast<float>(iPlaneStartY), 0);
			CVector3 EndPoint  (static_cast<float>(iPlaneEndX) ,static_cast<float>(iPlaneEndY), 0);
			m_pCushion[i]->Initialise(StartPoint, EndPoint);

			COORD crdStart;
			crdStart.X = iPlaneStartX;
			crdStart.Y = iPlaneStartY;
			COORD crdEnd;
			crdEnd.X = iPlaneEndX;
			crdEnd.Y = iPlaneEndY;

			m_vecReplacePixel.push_back(crdStart);
			m_vecReplacePixel.push_back(crdEnd);

			++ m_iNumCushions;
		}
		else
		{
			break;
		}
	}

	return (true);
}

bool
CTable::InitialisePockets()
{
	CIniParser& rIniGameSettings = CApplication::GetInstance().GetIniParser();

	int iPocketX = 0;
	int iPocketY = 0;

	char cBuffer[128];
	int iMaxPockets = 100;
	
	for (int i = 0; i < iMaxPockets; ++i)
	{
		iPocketX = 0;
		iPocketY = 0;

		sprintf_s(cBuffer, 128, "Pocket%dX", i);
		m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], cBuffer, iPocketX);

		sprintf_s(cBuffer, 128, "Pocket%dY", i);
		m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], cBuffer, iPocketY);

		if (iPocketX != false && iPocketY != false)
		{
			m_pPocket[i] = new CSphere();
			m_pPocket[i]->Initialise();
			m_pPocket[i]->SetPosition(X, iPocketX);
			m_pPocket[i]->SetPosition(Y, iPocketY);

			COORD crdPosition;
			crdPosition.X = iPocketX;
			crdPosition.Y = iPocketY;

			m_vecReplacePixel.push_back(crdPosition);

			float fPocketRadius = 15.0f;
			if (m_eTableType == TABLETYPE_ALTERNATE)
			{
				sprintf_s(cBuffer, 128, "TableType%dPocketRadius", m_eTableType + 1);
				rIniGameSettings.GetValue("Table", cBuffer, fPocketRadius);

				m_pPocket[i]->SetRadius(15.0f);
			}
			else
			{
				sprintf_s(cBuffer, 128, "TableType%dPocketRadius", m_eTableType + 1);
				rIniGameSettings.GetValue("Table", cBuffer, fPocketRadius);

				m_pPocket[i]->SetRadius(fPocketRadius);
			}

			++ m_iNumPockets;
		}
		else
		{
			break;
		}
	}

	return (true);
}

bool
CTable::InitialisePlayers()
{
	const int kiTextMarginTop = 30;
	const int kiTextMarginLeft = 70;

	m_pPlayer[PLAYER_ONE] = new CPlayer;
	m_pPlayer[PLAYER_ONE]->Initialise(PLAYER_ONE);


	m_pPlayer[PLAYER_TWO] = new CPlayer;
	m_pPlayer[PLAYER_TWO]->Initialise(PLAYER_TWO);

	int iRandomNumber = GenerateRandomNumber(1, 2);

	if (iRandomNumber == 1)
	{
		m_ePlayerTurn = PLAYER_ONE;
	}
	else
	{
		m_ePlayerTurn = PLAYER_TWO;
	}

	return (true);
}

bool
CTable::InitialisePlayerBallTypeText()
{
	const int kiFontWidth = m_pPlayer[PLAYER_ONE]->GetNameText().GetFontWidth();
	const int kiFontHeight = m_pPlayer[PLAYER_ONE]->GetNameText().GetFontHeight();
	const int kiFontWeight = m_pPlayer[PLAYER_ONE]->GetNameText().GetFontWeight();

	const float kfP1PositionX = m_pPlayer[PLAYER_ONE]->GetNameText().GetPosition(X) + 180.0f;
	const float kfP1PositionY = m_pPlayer[PLAYER_ONE]->GetNameText().GetPosition(Y);

	const float kfP2PositionX = m_pPlayer[PLAYER_TWO]->GetNameText().GetPosition(X) + 180.0f;
	const float kfP2PositionY = m_pPlayer[PLAYER_TWO]->GetNameText().GetPosition(Y);

	m_pPlayerBallType[PLAYER_ONE] = new CText();
	m_pPlayerBallType[PLAYER_ONE]->Initialise();
	m_pPlayerBallType[PLAYER_ONE]->SetFontWidth(kiFontWidth);
	m_pPlayerBallType[PLAYER_ONE]->SetFontHeight(kiFontHeight);
	m_pPlayerBallType[PLAYER_ONE]->SetFontWeight(kiFontWeight);
	m_pPlayerBallType[PLAYER_ONE]->SetTextColour(TEXTCOLOUR_ORANGE);
	m_pPlayerBallType[PLAYER_ONE]->SetText("Break Round");
	m_pPlayerBallType[PLAYER_ONE]->SetPosition(X, kfP1PositionX);
	m_pPlayerBallType[PLAYER_ONE]->SetPosition(Y, kfP1PositionY);
	m_pPlayerBallType[PLAYER_ONE]->SetDisplay(true);

	m_pPlayerBallType[PLAYER_TWO] = new CText();
	m_pPlayerBallType[PLAYER_TWO]->Initialise();
	m_pPlayerBallType[PLAYER_TWO]->SetFontWidth(kiFontWidth);
	m_pPlayerBallType[PLAYER_TWO]->SetFontHeight(kiFontHeight);
	m_pPlayerBallType[PLAYER_TWO]->SetFontWeight(kiFontWeight);
	m_pPlayerBallType[PLAYER_TWO]->SetTextColour(TEXTCOLOUR_ORANGE);
	m_pPlayerBallType[PLAYER_TWO]->SetText("Break Round");
	m_pPlayerBallType[PLAYER_TWO]->SetPosition(X, kfP2PositionX);
	m_pPlayerBallType[PLAYER_TWO]->SetPosition(Y, kfP2PositionY);
	m_pPlayerBallType[PLAYER_TWO]->SetDisplay(true);

	return (true);
}

bool
CTable::InitialiseCue()
{
	m_pCue = new CCue();
	m_pCue->Initialise();

	m_pCue->SetDisplay(true);
	m_pCue->SetPosition(X, 512);
	m_pCue->SetPosition(Y, 512);

	return (true);
}

bool
CTable::InitialiseTurnText()
{
	const int kiFontWidth = m_pPlayer[m_ePlayerTurn]->GetNameText().GetFontWidth();
	const int kiFontHeight = m_pPlayer[m_ePlayerTurn]->GetNameText().GetFontHeight();
	const int kiFontWeight = m_pPlayer[m_ePlayerTurn]->GetNameText().GetFontWeight();
		
	m_pTurnText = new CText;
	m_pTurnText->Initialise();
	m_pTurnText->SetText("TURN");
	m_pTurnText->SetFontWidth(kiFontWidth);
	m_pTurnText->SetFontHeight(kiFontHeight);
	m_pTurnText->SetFontWeight(kiFontWeight);
	m_pTurnText->SetTextColour(TEXTCOLOUR_GREEN);
	m_pTurnText->SetTextAlign(TEXTALIGN_RIGHT);

	m_pTurnText->SetDisplay(true);

	const float kfPositionX = m_pPlayer[m_ePlayerTurn]->GetNameText().GetPosition(X) - 25.0f;
	const float kfPositionY = m_pPlayer[m_ePlayerTurn]->GetNameText().GetPosition(Y);

	m_pTurnText->SetPosition(X, kfPositionX);
	m_pTurnText->SetPosition(Y, kfPositionY);

	return (true);
}

bool
CTable::InitialisePocketedBallsText()
{
	const int kiStartRowX = 420;
	const int kiStartRowY = 120;
		
	m_pTextPocketedBalls = new CText();
	m_pTextPocketedBalls->Initialise();
	m_pTextPocketedBalls->SetPosition(X, kiStartRowX);
	m_pTextPocketedBalls->SetPosition(Y, kiStartRowY - 8);
	m_pTextPocketedBalls->SetTextAlign(TEXTALIGN_RIGHT);
	m_pTextPocketedBalls->SetFontWeight(TEXTWEIGHT_HEAVY);
	m_pTextPocketedBalls->SetText("Pocketed Balls:");
	m_pTextPocketedBalls->SetDisplay(true);

	return (true);
}

bool
CTable::IntiialiseWinnerText()
{
	const int kiWindowWidth = CApplication::GetInstance().GetGameWindow().GetWidth();
	const int kiWindowHeight = CApplication::GetInstance().GetGameWindow().GetHeight();

	m_pWinnerText = new CText();
	m_pWinnerText->Initialise();
	m_pWinnerText->SetPosition(X, kiWindowWidth / 2);
	m_pWinnerText->SetPosition(Y, kiWindowHeight / 2 - 50);
	m_pWinnerText->SetTextAlign(TEXTALIGN_CENTER);
	m_pWinnerText->SetFont(40, 80, TEXTWEIGHT_HEAVY);
	m_pWinnerText->SetTextColour(TEXTCOLOUR_BLUE);
	m_pWinnerText->SetText("PLAYER ONE WINS!");

	return (true);
}

bool
CTable::DeinitialiseBalls()
{
	// Destroy ball instances
	for (int i = 0; i < BALL_MAX; ++i)
	{
		delete m_pBall[i];
		m_pBall[i] = 0;
	}

	return (true);
}

bool
CTable::DeinitialiseCushions()
{
	// Destroy cushion instances
	for (int i = 0; i < m_iNumCushions; ++i)
	{
		delete m_pCushion[i];
		m_pCushion[i] = 0;
	}
	return (true);
}

bool
CTable::DeinitialisePockets()
{
	// Destroy pocket instances
	for (int i = 0; i < m_iNumPockets; ++i)
	{
		delete m_pPocket[i];
		m_pPocket[i] = 0;
	}
	return (true);
}

void
CTable::ProcessCue(float _fDeltaTick)
{
	if (m_eMouseLeftState == MBS_DOWN)
	{
		m_fCueForce = m_MousePosition[Y] - m_MouseDownPosition[Y];

		if (m_fCueForce < 0.0f)
		{
			m_fCueForce = 0.0f;
		}
		else if (m_fCueForce > 250.0f)
		{
			m_fCueForce = 250.0f;
		}

		m_eCueState = CUESTATE_CHOOSEPOWER;
	}

	if (m_eMouseLeftState == MBS_RELEASED && m_ePrevMouseLeftState == MBS_DOWN)
	{
		if (m_fCueForce > 10.0f)
		{
			m_eCueState = CUESTATE_RELEASEPOWER;
		}
		else
		{
			m_eCueState = CUESTATE_CHOOSEANGLE;
		}
	}

	switch (m_eCueState)
	{
	case CUESTATE_CHOOSEANGLE:
		ProcessCueDirection();
		ProcessCuePosition();
		break;

	case CUESTATE_CHOOSEPOWER:
		ProcessCuePosition();
		break;

	case CUESTATE_RELEASEPOWER:
		ProcessCueRelease(_fDeltaTick);
		break;
	}
}

void
CTable::ProcessCueDirectionLine(float _fDeltaTick)
{
	CVector3 CueBallPosition = m_pBall[BALL_CUE]->GetPosition();
	CVector3 CuePosition     = m_pCue->GetPosition();

	m_pCue->GetLine().SetPosition(CueBallPosition);

	CVector3 LineDirection;
	CVector3::Minus(CuePosition, CueBallPosition, LineDirection);
	LineDirection.Invert();
	LineDirection.Normalise();

	m_pCue->GetLine().SetDirection(LineDirection);
}

void
CTable::SetPlayerTurn(EPlayer _ePlayer)
{
	m_ePlayerTurn = (_ePlayer == PLAYER_ONE) ? PLAYER_ONE : PLAYER_TWO;

	CVector3 TextPosition = m_pPlayer[m_ePlayerTurn]->GetNameText().GetPosition();

	TextPosition[X] -= 10;

	m_pTurnText->SetPosition(TextPosition);
}

void
CTable::SetNewRound()
{
	m_iRoundNumBallCushionHits = 0;
	m_iRoundNumBallBallHits = 0;

	m_vecRoundCueBallHitList.clear();
	m_vecRoundPocketedBallsList.clear();
	m_vecRoundCueBallHitList.clear();
}

void
CTable::ProcessCueInHand()
{
	std::vector<CBall*> m_vecPocketedBalls;
	std::vector<CBall*>::iterator iterPocketedBalls;
	iterPocketedBalls = m_vecPocketedBalls.begin();

	for (iterPocketedBalls; iterPocketedBalls != m_vecPocketedBalls.end();)
	{
		if ((*iterPocketedBalls)->GetBallType() == BALLTYPE_CUE)
		{
			iterPocketedBalls = m_vecPocketedBalls.erase(iterPocketedBalls);
			break;
		}
		else
		{
			++ iterPocketedBalls;
		}
	}


	m_pBall[BALL_CUE]->SetPosition(X, m_MousePosition[X]);
	m_pBall[BALL_CUE]->SetPosition(Y, m_MousePosition[Y]);

	if (m_eMouseLeftState == MBS_RELEASED && AllowCuePlaement() == true)
	{
		std::vector<CBall*> m_vecActiveBalls;
		std::vector<CBall*>::iterator iterActiveBalls;
		iterActiveBalls = m_vecActiveBalls.begin();

		bool bIsActive = false;
		for (iterActiveBalls; iterActiveBalls != m_vecActiveBalls.end();)
		{
			if ((*iterActiveBalls)->GetBallType() == BALLTYPE_CUE)
			{
				bIsActive = true;

				break;
			}
			else
			{
				++ iterActiveBalls;
			}
		}

		if (bIsActive == false)
		{
			m_vecActiveBalls.push_back(m_pBall[BALL_CUE]);
		}

		m_eGameState = GAMESTATE_PLAYERTURN;
	}
}

void
CTable::ProcessPhysics(float _fDeltaTick)
{
	float fDeltaTickLeft = _fDeltaTick;
	std::vector<CBall*>::iterator iterActiveBalls;
	iterActiveBalls = m_vecActiveBalls.begin();

	while (iterActiveBalls != m_vecActiveBalls.end())
	{
		CBall* pBall = (*iterActiveBalls);

		float fLowestImpactTimePlane = 1000.0f;
		float fLowestImpactTimeSphere = 1000.0f;
		float fLowestImpactTimePocket = 1000.0f;

		// Plane Collision
		CPlane* pCollidedPlane = 0;
		GetLowestImpactTimeSpherePlane(pBall, fDeltaTickLeft, pCollidedPlane, fLowestImpactTimePlane);

		// Sphere Collision
		CSphere* pCollidedSphere = 0;
		GetLowestImpactTimeSphereSphere(pBall, fDeltaTickLeft, pCollidedSphere, fLowestImpactTimeSphere);

		// Sphere Collision
		CSphere* pCollidedPocket = 0;
		GetLowestImpactTimeSpherePocketSphere(pBall, fDeltaTickLeft, pCollidedPocket, fLowestImpactTimePocket);

		// Collision Processing
		if (pCollidedPlane != 0 || pCollidedSphere != 0 || pCollidedPocket != 0)
		{
			float fLowestImpactTime = 0.0f;	
			
			if (pCollidedPocket != 0)
			{
				SetBallPocketed(pBall);

				fDeltaTickLeft = _fDeltaTick;

				if (pBall->GetBallType() != BALLTYPE_CUE)
				{
					iterActiveBalls = m_vecActiveBalls.erase(iterActiveBalls);
				}
				else
				{
					m_pBall[BALL_CUE]->SetVelocity(X, 0.0f);
					m_pBall[BALL_CUE]->SetVelocity(Y, 0.0f);
					++ iterActiveBalls;
				}
			}
			else if (fLowestImpactTimePlane <= fLowestImpactTimeSphere)
			{
				fDeltaTickLeft -= fLowestImpactTimePlane;
				fLowestImpactTime = floor(fLowestImpactTimePlane * 10000.0f) / 10000.0f;

				//pBall->Process(fLowestImpactTime);

				pBall->ReflectAgainstPlane(pCollidedPlane);

				pCollidedPlane->SetColour(RGB(255,0,0));
				++ m_iRoundNumBallCushionHits;

				//if (pBall->GetBallType() == BALLTYPE_CUE)
				//{
				//	m_vecRoundCueBallHitList.push_back(pCollidedSphere);
				//}
			}
			else
			{
				fDeltaTickLeft -= fLowestImpactTimeSphere;
				fLowestImpactTime = floor(fLowestImpactTimeSphere * 10000.0f) / 10000.0f;
				//pBall->Process(fLowestImpactTime);
				pBall->ReflectAgainstSphere(pCollidedSphere);

				++ m_iRoundNumBallBallHits;
			}
		}
		else
		{
			fDeltaTickLeft = floor(fDeltaTickLeft * 10000.0f) / 10000.0f;
			pBall->Process(fDeltaTickLeft);

			++ iterActiveBalls;
			fDeltaTickLeft = _fDeltaTick;
		}
	}
}

void
CTable::DrawBalls()
{
	// Draw the balls
	for (int i = 0; i < BALL_MAX; ++i)
	{
		m_pBall[i]->Draw();
	}
}

void
CTable::DrawCushions()
{
	// Draw the cushions
	for (int i = 0; i < m_iNumCushions; ++i)
	{
		m_pCushion[i]->Draw();
	}
}

void
CTable::DrawCueDirectionLine()
{
	float fLowestImpactTimePlane = 1000.0f;
	float fLowestImpactTimeSphere = 1000.0f;

	CSphere* pCollidedSphere = 0;
	GetLowestImpactTimeLineSphere(&m_pCue->GetLine(), 1.0f, pCollidedSphere, fLowestImpactTimeSphere);

	CPlane* pCollidedPlane = 0;
	GetLowestImpactTimeLinePlane(&m_pCue->GetLine(), 1.0f, pCollidedPlane, fLowestImpactTimePlane);

	if (pCollidedSphere != 0 || pCollidedPlane != 0)
	{
		CVector3 LineDirection = m_pCue->GetLine().GetDirection();

		if (fLowestImpactTimePlane < fLowestImpactTimeSphere)
		{
			LineDirection.Scale(fLowestImpactTimePlane);
		}
		else
		{
			LineDirection.Scale(fLowestImpactTimeSphere);
		}
		
		CVector3 BallPosition = m_pBall[BALL_CUE]->GetPosition();

		CVector3 HitPosition;
		CVector3::Add(LineDirection, BallPosition, HitPosition);

		CBackBuffer& rBackBuffer = CApplication::GetInstance().GetGameWindow().GetBackBuffer();
		rBackBuffer.DrawLine(BallPosition[X], BallPosition[Y], HitPosition[X], HitPosition[Y]);

		if (fLowestImpactTimePlane > fLowestImpactTimeSphere)
		{
			CBall& rDummyBall = m_pCue->GetDummyBall();
			rDummyBall.SetPosition(HitPosition);

			rDummyBall.Draw();
		}
	}
}

void
CTable::DrawReplacePixel()
{
	std::vector<COORD>::iterator iterPixels;
	iterPixels = m_vecReplacePixel.begin();

	CBackBuffer& rBackBuffer = CApplication::GetInstance().GetGameWindow().GetBackBuffer();

	BITMAP hSpriteBitmap = m_pTableSprite->GetSpriteBitmap();
	const int kiSpriteWidth  = hSpriteBitmap.bmWidth;
	const int kiSpriteHeight = hSpriteBitmap.bmHeight;
	const int kiTablePositionX = m_pTableSprite->GetPositionX();
	const int kiTablePositionY = m_pTableSprite->GetPositionY();

	COLORREF crPixelColour;
	int iPositionX = 0;
	int iPositionY = 0;
	for (iterPixels; iterPixels != m_vecReplacePixel.end(); ++iterPixels)
	{
		COORD crdPosition = (*iterPixels);

		iPositionX = static_cast<int>(crdPosition.X);
		iPositionY = static_cast<int>(crdPosition.Y);

		crPixelColour = m_pTableSprite->GetPixelColour(iPositionX - (kiTablePositionX - kiSpriteWidth / 2) + 1, 
													   iPositionY - (kiTablePositionY - kiSpriteHeight / 2));

		::SetPixel(rBackBuffer.GetBFDC(), iPositionX, iPositionY, crPixelColour);
	}
}

void
CTable::SetCueStartPosition()
{
	int iCueStartX = m_pTableSprite->GetPositionX() - 200;
	int iCueStartY = m_pTableSprite->GetPositionY();

	// Row 3 Setup
	// Set ball 8 position, all balls will position themself around this ball
	m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], "CueStartX", iCueStartX);
	m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], "CueStartY", iCueStartY);

	m_pBall[0]->SetPosition(X, iCueStartX);
	m_pBall[0]->SetPosition(Y, iCueStartY);

	std::vector<CBall*> m_vecActiveBalls;
	std::vector<CBall*>::iterator iterActiveBalls;
	iterActiveBalls = m_vecActiveBalls.begin();

	/*
	bool bIsActive = false;
	for (iterActiveBalls; iterActiveBalls != m_vecActiveBalls.end();)
	{
		if ((*iterActiveBalls)->GetBallType() == BALLTYPE_CUE)
		{
			bIsActive = true;

			break;
		}
		else
		{
			++ iterActiveBalls;
		}
	}

	if (bIsActive == false)
	{
		m_vecActiveBalls.push_back(m_pBall[BALL_CUE]);
	}
	*/
}

void
CTable::RackBalls()
{
	int iRackStartX = m_pTableSprite->GetPositionX() + 150;
	int iRackStartY = m_pTableSprite->GetPositionY();

	// Row 3 Setup
	// Set ball 8 position, all balls will position themself around this ball
	m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], "RackCenterX", iRackStartX);
	m_pTableSpriteParser->GetValue(g_kcTableTypeName[m_eTableType], "RackCenterY", iRackStartY);

	m_pBall[8]->SetPosition(X, iRackStartX);
	m_pBall[8]->SetPosition(Y, iRackStartY);

	const float fBall8PositionX = m_pBall[8]->GetPosition(X);
	const float fBall8PositionY = m_pBall[8]->GetPosition(Y);
	const float fRadiusDoubled = m_pBall[8]->GetRadius() * 2.0f;

	m_pBall[BALL_15]->SetPosition(X, fBall8PositionX);
	m_pBall[BALL_15]->SetPosition(Y, fBall8PositionY + fRadiusDoubled + 1.0f);
	
	m_pBall[BALL_01]->SetPosition(X, fBall8PositionX);
	m_pBall[BALL_01]->SetPosition(Y, fBall8PositionY - fRadiusDoubled - 1.0f);

	// Row 1 Setup
	m_pBall[BALL_09]->SetPosition(X, fBall8PositionX - fRadiusDoubled * 2.0f + 2.0f);
	m_pBall[BALL_09]->SetPosition(Y, fBall8PositionY);

	// Row 2 Setup
	m_pBall[BALL_07]->SetPosition(X, fBall8PositionX - fRadiusDoubled + 1.0f);
	m_pBall[BALL_07]->SetPosition(Y, fBall8PositionY + fRadiusDoubled / 2.0f + 1.0f);

	m_pBall[BALL_12]->SetPosition(X, fBall8PositionX - fRadiusDoubled + 1.0f);
	m_pBall[BALL_12]->SetPosition(Y, fBall8PositionY - fRadiusDoubled / 2.0f - 1.0f);

	// Row 4 Setup
	m_pBall[BALL_14]->SetPosition(X, fBall8PositionX + fRadiusDoubled - 1.0f);
	m_pBall[BALL_14]->SetPosition(Y, fBall8PositionY - fRadiusDoubled - fRadiusDoubled / 2.0f - 2.0f);

	m_pBall[BALL_03]->SetPosition(X, fBall8PositionX + fRadiusDoubled - 1.0f);
	m_pBall[BALL_03]->SetPosition(Y, fBall8PositionY - fRadiusDoubled / 2.0f - 1.0f);

	m_pBall[BALL_10]->SetPosition(X, fBall8PositionX + fRadiusDoubled - 1.0f);
	m_pBall[BALL_10]->SetPosition(Y, fBall8PositionY + fRadiusDoubled / 2.0f + 1.0f);

	m_pBall[BALL_06]->SetPosition(X, fBall8PositionX + fRadiusDoubled - 1.0f);
	m_pBall[BALL_06]->SetPosition(Y, fBall8PositionY + fRadiusDoubled + fRadiusDoubled / 2.0f + 2.0f);

	// Row 5 Setup
	m_pBall[BALL_05]->SetPosition(X, fBall8PositionX + fRadiusDoubled * 2.0f - 2.0f);
	m_pBall[BALL_05]->SetPosition(Y, fBall8PositionY - fRadiusDoubled * 2.0f - 2.0f);

	m_pBall[BALL_04]->SetPosition(X, fBall8PositionX + fRadiusDoubled * 2.0f - 2.0f);
	m_pBall[BALL_04]->SetPosition(Y, fBall8PositionY - fRadiusDoubled - 1.0f);

	m_pBall[BALL_13]->SetPosition(X, fBall8PositionX + fRadiusDoubled * 2.0f - 2.0f);
	m_pBall[BALL_13]->SetPosition(Y, fBall8PositionY);

	m_pBall[BALL_11]->SetPosition(X, fBall8PositionX + fRadiusDoubled * 2.0f - 2.0f);
	m_pBall[BALL_11]->SetPosition(Y, fBall8PositionY + fRadiusDoubled * 2.0f + 2.0f);

	m_pBall[BALL_02]->SetPosition(X, fBall8PositionX + fRadiusDoubled * 2.0f - 2.0f);
	m_pBall[BALL_02]->SetPosition(Y, fBall8PositionY + fRadiusDoubled + 1.0f);

	m_pBall[BALL_CUE]->GetVelocity().Zero();
	m_pBall[BALL_01]->GetVelocity().Zero();
	m_pBall[BALL_02]->GetVelocity().Zero();
	m_pBall[BALL_03]->GetVelocity().Zero();
	m_pBall[BALL_04]->GetVelocity().Zero();
	m_pBall[BALL_05]->GetVelocity().Zero();
	m_pBall[BALL_06]->GetVelocity().Zero();
	m_pBall[BALL_07]->GetVelocity().Zero();
	m_pBall[BALL_08]->GetVelocity().Zero();
	m_pBall[BALL_09]->GetVelocity().Zero();
	m_pBall[BALL_10]->GetVelocity().Zero();
	m_pBall[BALL_11]->GetVelocity().Zero();
	m_pBall[BALL_12]->GetVelocity().Zero();
	m_pBall[BALL_13]->GetVelocity().Zero();
	m_pBall[BALL_14]->GetVelocity().Zero();
	m_pBall[BALL_15]->GetVelocity().Zero();
}

void
CTable::ScanTable()
{
	COLORREF crPocket = RGB(255, 0, 0);
	COLORREF crCueStartPosition = RGB(0, 0, 255);
	COLORREF crRackCenterPosition = RGB(200, 0, 200);

	BITMAP hSpriteBitmap = m_pTableSprite->GetSpriteBitmap();
	const int kiSpriteWidth  = hSpriteBitmap.bmWidth;
	const int kiSpriteHeight = hSpriteBitmap.bmHeight;
	const int kiSpritePositionX = m_pTableSprite->GetPositionX();
	const int kiSpritePositionY = m_pTableSprite->GetPositionY();

	const int kiMaxCushions = 100;

	int iPocketCount = 0;
	int iCushionCount = 0;
	char cBuffer[128];
	COLORREF crPixelColour = RGB(0,0,0);
	for (int iY = 0; iY < kiSpriteHeight; ++iY)
	{
		for (int iX = 0; iX < kiSpriteWidth; ++iX)
		{
			crPixelColour = m_pTableSprite->GetPixelColour(iX, iY);

			const int kiPixelPositionX = iX + kiSpritePositionX - kiSpriteWidth / 2;
			const int kiPixelPositionY = iY + kiSpritePositionY - kiSpriteHeight / 2;

			if (crPixelColour == crPocket)
			{
				sprintf_s(cBuffer, 128, "Pocket%dX", iPocketCount);
				m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], cBuffer, kiPixelPositionX);

				sprintf_s(cBuffer, 128, "Pocket%dY", iPocketCount);
				m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], cBuffer, kiPixelPositionY);

				++ iPocketCount;

				continue;
			}
			
			if (crPixelColour == crCueStartPosition)
			{
				m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], "CueStartX", kiPixelPositionX);
				m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], "CueStartY", kiPixelPositionY);

				continue;
			}

			if (crPixelColour == crRackCenterPosition)
			{
				m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], "RackCenterX", kiPixelPositionX);
				m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], "RackCenterY", kiPixelPositionY);

				continue;
			}

			for (int iPlane = 0; iPlane < kiMaxCushions; ++iPlane)
			{
				if (crPixelColour == RGB(0, 200, 200 + 2*iPlane))
				{
					sprintf_s(cBuffer, 128, "Plane%dStartX", iPlane);
					m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], cBuffer, kiPixelPositionX);

					sprintf_s(cBuffer, 128, "Plane%dStartY", iPlane);
					m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], cBuffer, kiPixelPositionY);
				}
				else if (crPixelColour == RGB(0, 200, 201 + 2*iPlane))
				{
					sprintf_s(cBuffer, 128, "Plane%dEndX", iPlane);
					m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], cBuffer, kiPixelPositionX);

					sprintf_s(cBuffer, 128, "Plane%dEndY", iPlane);
					m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], cBuffer, kiPixelPositionY);

					++ iCushionCount;
				}
			}
		}
	}

	m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], "PocketCount", iPocketCount);
	m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], "CushionCount", iCushionCount);
	m_pTableSpriteParser->AddValue(g_kcTableTypeName[m_eTableType], "Scanned", true);
}


void
CTable::HandleMessage(EKeyCode _EKeyCode, WPARAM _wParam, LPARAM _lParam)
{
	switch (_EKeyCode)
	{
		case MSG_MOUSE_MOVE:
		{
			m_MousePosition[X] = static_cast<float>(LOWORD(_lParam));
			m_MousePosition[Y] = static_cast<float>(HIWORD(_lParam));
			break;
		}

		case MSG_MOUSE_LBUTTONUP:
		{
			m_MouseUpPosition[X] = m_MousePosition[X];
			m_MouseUpPosition[Y] = m_MousePosition[Y];
			m_ePrevMouseLeftState = m_eMouseLeftState;
			m_eMouseLeftState = MBS_RELEASED;
			break;
		}

		case MSG_MOUSE_LBUTTONDWN:
		{
			m_MouseDownPosition[X] = m_MousePosition[X];
			m_MouseDownPosition[Y] = m_MousePosition[Y];
			m_ePrevMouseLeftState = m_eMouseLeftState;
			m_eMouseLeftState = MBS_DOWN;
			break;
		}

		default:
			break;
	}
}

void
CTable::GetLowestImpactTimeSpherePlane(CSphere* _pSphere, float _fDeltaTick, CPlane*& _pImpactPlane ,float& _fLowestImpactTime)
{
	for (int i = 0; i < m_iNumCushions; ++i)
	{
		float fImpactTime = 0.0f;
		bool bResult = _pSphere->IsGoingToCollidePlane(m_pCushion[i], _fDeltaTick, fImpactTime);

		if (bResult == true && fImpactTime < _fLowestImpactTime)
		{
			_pImpactPlane = m_pCushion[i];
			_fLowestImpactTime = fImpactTime;
		}
	}
}

void
CTable::GetLowestImpactTimeSphereSphere(CSphere* _pSphere, float _fDeltaTick, CSphere*& _pImpactSphere, float& _fLowestImpactTime)
{
	std::vector<CBall*>::iterator iterActiveBalls;
	iterActiveBalls = m_vecActiveBalls.begin();
		
	while (iterActiveBalls != m_vecActiveBalls.end())
	{
		CBall* pBall = (*iterActiveBalls);
		float fImpactTime = 0.0f;
		bool bResult = _pSphere->IsGoingToCollideSphere(pBall, _fDeltaTick, fImpactTime);

		if (bResult == true && fImpactTime < _fLowestImpactTime)
		{
			_fLowestImpactTime = fImpactTime;
			_pImpactSphere = pBall;
		}

		++ iterActiveBalls;
	}
}

void
CTable::GetLowestImpactTimeSpherePocketSphere(CSphere* _pSphere, float _fDeltaTick, CSphere*& _pImpactPocket, float& _fLowestImpactTime)
{
	for (int i = 0; i < m_iNumPockets; ++i)
	{
		CSphere* pPocket = m_pPocket[i];
		float fImpactTime = 0.0f;
		bool bResult = _pSphere->IsGoingToCollideSphere(pPocket, _fDeltaTick, fImpactTime);

		if (bResult == true && fImpactTime < _fLowestImpactTime)
		{
			_fLowestImpactTime = fImpactTime;
			_pImpactPocket = pPocket;
		}
	}
}

void
CTable::GetLowestImpactTimeLinePlane(CLine* _pLine, float _fDeltaTick, CPlane*& _pImpactPlane, float& _fLowestImpactTime)
{
	for (int i = 0; i < m_iNumCushions; ++i)
	{
		float fImpactTime = 0.0f;
		bool bResult = _pLine->IsGoingToCollidePlane(m_pCushion[i], _fDeltaTick, fImpactTime);

		if (bResult == true && fImpactTime < _fLowestImpactTime)
		{
			_fLowestImpactTime = fImpactTime;
			_pImpactPlane = m_pCushion[i];
		}
	}
}

void
CTable::GetLowestImpactTimeLineSphere(CLine* _pLine, float _fDeltaTick, CSphere*& _pImpactSphere, float& _fLowestImpactTime)
{
	std::vector<CBall*>::iterator iterActiveBalls;
	iterActiveBalls = m_vecActiveBalls.begin();

	while (iterActiveBalls != m_vecActiveBalls.end())
	{
		CBall* pBall = (*iterActiveBalls);

		float fImpactTime = 0.0f;
		bool bResult = _pLine->IsGoingToCollideSphere(pBall, _fDeltaTick, fImpactTime);

		if (bResult == true && fImpactTime < _fLowestImpactTime)
		{
			_fLowestImpactTime = fImpactTime;
			_pImpactSphere = pBall;
		}

		++ iterActiveBalls;
	}
}

bool
CTable::IsBallsCurrentlyMoving()
{
	std::vector<CBall*>::iterator iterActiveBalls;
	iterActiveBalls = m_vecActiveBalls.begin();

	while (iterActiveBalls != m_vecActiveBalls.end())
	{
		CBall* pBall = (*iterActiveBalls);

		if (pBall->IsMoving() == true)
		{
			return (true);
		}

		++ iterActiveBalls;
	}

	return (false);
}

bool
CTable::IsBallPocketed(CBall* _pBall)
{
	CVector3 BallPosition = _pBall->GetPosition();

	CVector3 PocketPosition;
	float fPocketRadius = 0.0f;

	CVector3 Displacement;

	for (int i = 0; i < m_iNumPockets; ++i)
	{
		PocketPosition = m_pPocket[i]->GetPosition();
		fPocketRadius = m_pPocket[i]->GetRadius();

		CVector3::Minus(PocketPosition, BallPosition, Displacement);

		float fDistance = CVector3::GetMagnitude(Displacement);

		if (fDistance < fPocketRadius)
		{
			return (true);
		}
	}

	return (false);
}

void
CTable::ProcessCueDirection()
{
	CVector3 CueBallPosition = m_pBall[BALL_CUE]->GetPosition();

	CVector3 MousePosition;
	if (bLockCueDirection == true)
	{
		MousePosition = m_MouseDownPosition;
	}
	else
	{
		MousePosition = m_MousePosition;
	}

	CVector3 Direction;
	CVector3::Minus(MousePosition, CueBallPosition, Direction);
	Direction.Normalise();

	m_pCue->SetDirection(Direction);
}

void
CTable::ProcessCuePosition()
{
	CVector3 Displacement = m_pCue->GetDirection();

	if (m_eCueState == CUESTATE_CHOOSEANGLE)
	{
		Displacement.Scale(135);
	}
	else if (m_eCueState == CUESTATE_CHOOSEPOWER)
	{
		Displacement.Scale(135 + m_fCueForce / 2.0f);
	}

	CVector3 CueBallPosition = m_pBall[BALL_CUE]->GetPosition();
	CVector3::Add(Displacement, CueBallPosition, Displacement);

	m_pCue->SetOrigin(CueBallPosition);
	m_pCue->SetPosition(Displacement);
}

void
CTable::ProcessCueRelease(float _fDeltaTick)
{
	CVector3 Direction = m_pCue->GetDirection();
	Direction.Scale(m_fCueForce * 3.0f);
	Direction.Invert();

	m_pBall[BALL_CUE]->SetVelocity(Direction);


	SetGameState(GAMESTATE_PROCESSINGPHYSICS);
	m_eCueState = CUESTATE_CHOOSEANGLE;
	m_fCueForce = 0.0f;
}

void
CTable::SetBallTypeOwner(EPlayer _ePlayer, EBallType _eBallType)
{
	EBallType Player1BallType = BALLTYPE_INVALID;
	EBallType Player2BallType = BALLTYPE_INVALID;

	if (_eBallType == BALLTYPE_SOLID || _eBallType == BALLTYPE_STRIPE)
	{
		if (_ePlayer == PLAYER_ONE)
		{
			Player1BallType = _eBallType;
			Player2BallType = (_eBallType == BALLTYPE_SOLID) ? BALLTYPE_STRIPE : BALLTYPE_SOLID;
		}
		else
		{
			Player1BallType = (_eBallType == BALLTYPE_SOLID) ? BALLTYPE_STRIPE : BALLTYPE_SOLID;
			Player2BallType = _eBallType;
		}

		m_pPlayer[PLAYER_ONE]->SetBallOwnerType(Player1BallType);
		m_pPlayer[PLAYER_TWO]->SetBallOwnerType(Player2BallType);

		m_pPlayerBallType[PLAYER_ONE]->SetText(g_kcBallTypeName[Player1BallType]);
		m_pPlayerBallType[PLAYER_TWO]->SetText(g_kcBallTypeName[Player2BallType]);
	}
}

void
CTable::ResetActiveBalls()
{
	m_vecActiveBalls.clear();
	m_vecPocketedBalls.clear();

	for(int i = BALL_CUE; i < BALL_MAX; ++i)
	{
		m_vecActiveBalls.push_back(m_pBall[i]);
	}

	m_iNumBallsPocketed = 0;
}

void
CTable::SetBallPocketed(CBall* _pBall)
{
	EBallType eBallType = _pBall->GetBallType();

	_pBall->SetPocketed(true);

	++ m_iNumBallsPocketed;

	const int kiStartRowX = 420;
	const int kiStartRowY = 120;

	_pBall->SetPosition(X, kiStartRowX + m_iNumBallsPocketed * 20);
	_pBall->SetPosition(Y, kiStartRowY);

	_pBall->GetVelocity().Zero();
	
	std::vector<CBall*>::iterator iterActiveBalls;
	iterActiveBalls = m_vecActiveBalls.begin();

	m_vecPocketedBalls.push_back(_pBall);
	m_vecRoundPocketedBallsList.push_back(_pBall);
}

bool
CTable::AllowCuePlaement()
{
	bool bAllowed = false;
	
	if (m_eTableType == TABLETYPE_REGULAR)
	{
		bAllowed = AllowCuePlaementRegular();
	}
	else if (m_eTableType == TABLETYPE_ALTERNATE)
	{
		bAllowed = AllowCuePlaementAlternate();
	}

	return (bAllowed);
}

bool
CTable::AllowCuePlaementRegular()
{
	const int m_iPadding = 40;

	BITMAP hSpriteBitmap = m_pTableSprite->GetSpriteBitmap();
	const int kiSpriteWidth  = hSpriteBitmap.bmWidth;
	const int kiSpriteHeight = hSpriteBitmap.bmHeight;
	const int kiTablePositionX = m_pTableSprite->GetPositionX();
	const int kiTablePositionY = m_pTableSprite->GetPositionY();

	RECT TableBounds;

	TableBounds.top = kiTablePositionY - kiSpriteHeight / 2 + m_iPadding;
	TableBounds.bottom = kiTablePositionY + kiSpriteHeight / 2 - m_iPadding;

	TableBounds.left = kiTablePositionX - kiSpriteWidth / 2 + m_iPadding;
	TableBounds.right = kiTablePositionX + kiSpriteWidth / 2 - m_iPadding;

	const int kiCuePositionX = static_cast<int>(m_pBall[BALL_CUE]->GetPosition(X));
	const int kiCuePositionY = static_cast<int>(m_pBall[BALL_CUE]->GetPosition(Y));

	bool bWithinBounds = false;
	COORD crdPosition;

	crdPosition.X = kiCuePositionX;
	crdPosition.Y = kiCuePositionY;

	return (IsWithinBounds(TableBounds, crdPosition));
}

bool
CTable::AllowCuePlaementAlternate()
{
	return (true);
}