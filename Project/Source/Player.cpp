//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Player.cpp
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <iostream>

// Local Includes

// Framework
#include "Application.h"
#include "GameWindow.h"

// Core
#include "Text.h"

// Content
#include "GameDefines.h"

// This Include
#include "Player.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlayer::CPlayer()
: m_eBallOwnerType(BALLTYPE_INVALID)
, m_pNameText(0)
{

	// Emtpty
}

CPlayer::~CPlayer()
{
	Deinitialise();
}

bool
CPlayer::Initialise(EPlayer _ePlayerId)
{
	sprintf_s(m_cPlayerName, 64, "Player %d", _ePlayerId + 1);

	const int kiWindowWidth = CApplication::GetInstance().GetGameWindow().GetWidth() - 140;
	const int kiTextWidth = 20;
	const int kiTextHeight = 40;

	m_pNameText = new CText();
	m_pNameText->Initialise();
	m_pNameText->SetText(m_cPlayerName);
	m_pNameText->SetFont(kiTextWidth, kiTextHeight, TEXTWEIGHT_HEAVY);
	m_pNameText->SetPosition(X, kiWindowWidth / 2.0f);
	m_pNameText->SetPosition(Y, 20 + 40 * _ePlayerId);
	m_pNameText->SetDisplay(true);

	return (true);
}

bool
CPlayer::Deinitialise()
{
	delete m_pNameText;
	m_pNameText = 0;

	return (true);
}

void
CPlayer::Process(float _fDeltaTick)
{
	//Empty
}

void
CPlayer::Draw()
{
	m_pNameText->Draw();
}