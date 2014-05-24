//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Cue.cpp
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <cmath>

// Local Includes
#include "Resource.h"

// Framework
#include "Application.h"
#include "IniParser.h"

// Core
#include "RotationSprite.h"
#include "LogManager.h"
#include "Vector3.h"
#include "Ball.h"

// Content
#include "Line.h"

// This Include
#include "Cue.h"

// Static Variables

// Static Function Prototypes

// Implementation

CCue::CCue()
: m_pCueSprite(0)
, m_pDirectionLine(0)
, m_bDisplay(false)
{
	//Empty
}

CCue::~CCue()
{
	Deinitialise();
}

bool
CCue::Initialise()
{
	m_pCueSprite = new CRotationSprite;
	m_pCueSprite->Initialise(IDB_CUE, IDB_CUEMASK);
	m_pCueSprite->SetNumSpriteAngles(90);
	m_pCueSprite->SetAngleBetweenFrame(4);
	m_pCueSprite->SetFrameWidth(254);

	m_pCueSprite->SetFacingAngle(270);

	m_Position[X] = 500;
	m_Position[Y] = 400;

	m_pDirectionLine = new CLine();
	m_pDirectionLine->Initialise();

	m_pReboundLine = new CLine();
	m_pReboundLine->Initialise();

	float fBallMass = 10.0f;
	float fBallRadius = 8.0f;

	const char kcGroup[] = "Table";
	CIniParser& rIniGameSettings = CApplication::GetInstance().GetIniParser();
	rIniGameSettings.GetValue(kcGroup, "BallMass", fBallMass);
	rIniGameSettings.GetValue(kcGroup, "BallRadius", fBallRadius);

	m_pDummyBall = new CBall();
	m_pDummyBall->Initialise(IDB_BALL_CUEDUMMY, IDB_BALL_CUEDUMMYMASK);
	m_pDummyBall->SetMass(fBallMass);
	m_pDummyBall->SetRadius(fBallRadius);

	return (true);
}

bool
CCue::Deinitialise()
{
	delete m_pCueSprite;
	m_pCueSprite = 0;

	delete m_pDirectionLine;
	m_pDirectionLine = 0;

	delete m_pReboundLine;
	m_pReboundLine = 0;

	delete m_pDummyBall;
	m_pDummyBall = 0;

	return (true);
}

void
CCue::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}

void
CCue::Draw()
{
	if (m_bDisplay == true)
	{
		CalculateFacingAngle();

		const int kiPositionX = static_cast<int>(CEntity::m_Position[X]);
		const int kiPositionY = static_cast<int>(CEntity::m_Position[Y]);

		m_pCueSprite->SetPosition(kiPositionX, kiPositionY);
		m_pCueSprite->Draw();
	}
}

void
CCue::CalculateFacingAngle()
{
	float iX1 = CEntity::GetPosition(X);
	float iX2 = m_Origin[X];

	float iY1 = CEntity::GetPosition(Y);
	float iY2 = m_Origin[Y];

	float fDifferenceX = iX2 - iX1;
	float fDifferenceY = iY1 - iY2;

	float fDistance = sqrt( fDifferenceX * fDifferenceX + fDifferenceY * fDifferenceY );

	float fAnswer = abs(acos(fDifferenceY / fDistance) * 180.0f / 3.14159f);

	if (fDifferenceX >= 0 && fDifferenceY >= 0)
	{
		//Empty
	}
	else if (fDifferenceX <= 0 && fDifferenceY >= 0)
	{
		fAnswer = 270.0f + 90.0f - fAnswer;
	}
	else if (fDifferenceX <= 0 && fDifferenceY <= 0)
	{
		fAnswer = 270.0f + 90.0f - fAnswer;
	}
	else if (fDifferenceX >= 0 && fDifferenceY <= 0)
	{
		//Emtpy
	}

	m_pCueSprite->SetFacingAngle(fAnswer);
}