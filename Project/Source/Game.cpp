//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Game.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes
#include "Resource.h"

// Framework
#include "LogManager.h"
#include "MessageManager.h"
#include "Application.h"
#include "GameWindow.h"
#include "BackBuffer.h"
#include "Utilities.h"
#include "DebugDialog.h"
#include "TextField.h"
#include "PerformanceClock.h"
#include "TickBox.h"
#include "IniParser.h"

// Core
#include "Button.h"
#include "Text.h"

// Scene
#include "Table.h"

// This Include
#include "Game.h"

// Static Variables

// Static Function Prototypes

// Implementation
CGame::CGame()
: m_cpTextBuffer(0)
, m_pDebugDialog(0)
, m_pLogManager(0)
, m_pTable(0)
, m_pResetButton(0)
, m_pTextControls1(0)
, m_pTextControls2(0)
, m_pTextControls3(0)
{
}

CGame::~CGame()
{
	Deinitialise();
}

bool
CGame::Initialise()
{
	InitialiseTextBuffer();
	InitialiseDebugDialog();
	InitialiseLogManager();
	IntiialiseMessageTarget();
	IntiailiseTable();

	m_pResetButton = new CButton();
	m_pResetButton->Initialise(IDB_BUTTON_RESTART, IDB_BUTTON_RESTARTMASK);

	const int kiWindowWidth = CApplication::GetInstance().GetGameWindow().GetWidth();
	
	m_pResetButton->SetPosition(X, kiWindowWidth - 80);
	m_pResetButton->SetPosition(Y, 30);
	m_pResetButton->UpdateBounds();

	InitialiseControlText();

	return true;
}

bool
CGame::Deinitialise()
{
	DeinitialiseTextBuffer();
	DeinitialiseDebugDialog();
	DeinitialiseLogManager();
	DeinitialiseMessageTarget();
	DeinitialiseTable();

	delete m_pResetButton;
	m_pResetButton = 0;

	delete m_pTextControls1;
	m_pTextControls1 = 0;

	delete m_pTextControls2;
	m_pTextControls2 = 0;

	delete m_pTextControls3;
	m_pTextControls3 = 0;

	return (true);
}

void
CGame::Process(float _fDeltaTick)
{
	ProcessDebugDialog();

	m_pLogManager->Process(_fDeltaTick);
	m_pTable->Process(_fDeltaTick);

	m_pResetButton->Process(_fDeltaTick);

	if (m_pResetButton->HasBeenClicked() == true)
	{
		delete m_pTable;
		m_pTable = 0;
		
		IntiailiseTable();
	}

	m_pTextControls1->Process(_fDeltaTick);
	m_pTextControls2->Process(_fDeltaTick);
	m_pTextControls3->Process(_fDeltaTick);
}

void
CGame::Draw()
{
	m_pTable->Draw();
	m_pLogManager->Draw();
	m_pResetButton->Draw();
	m_pTextControls1->Draw();
	m_pTextControls2->Draw();
	m_pTextControls3->Draw();
}

bool
CGame::InitialiseTextBuffer()
{
	m_cpTextBuffer = new char[s_kiTextBufferSize];

	return (true);
}

bool
CGame::InitialiseDebugDialog()
{
	CApplication& rApplication = CApplication::GetInstance();

	HINSTANCE hInstance = rApplication.GetInstanceHandle();
	HWND hWindowHandle = rApplication.GetGameWindow().GetHandle();

	m_pDebugDialog = new CDebugDialog();
	m_pDebugDialog->Initialise(hInstance, hWindowHandle, IDD_DIALOG_DEBUG);

	HWND hDialogHandle = m_pDebugDialog->GetHandle();

	rApplication.InsertDialogHandle(hDialogHandle);

	CClock& rClock = CApplication::GetInstance().GetGameWindow().GetClock();
	float fStaticDeltaTick = rClock.GetStaticDeltatick();
	float fMaxFrames = rClock.GetMaxFrames();

	m_pDebugDialog->GetDeltaTickField().SetText(fStaticDeltaTick);
	m_pDebugDialog->GetMaxFramesField().SetText(fMaxFrames);

	return (true);
}

bool
CGame::InitialiseLogManager()
{
	m_pLogManager = new CLogManager();
	m_pLogManager->Initialise();
	m_pLogManager->AddLogTarget(LOGTARGET_GAMEWINDOW);
	m_pLogManager->AddLogTarget(LOGTARGET_OUTPUT);

	return (true);
}

bool
CGame::IntiialiseMessageTarget()
{
	CMessageManager& rMessageManager = CApplication::GetInstance().GetGameWindow().GetMsgManager();
	rMessageManager.AddMsgTarget(MSG_KEY_ESC_DWN, this);

	return (true);
}

bool
CGame::IntiailiseTable()
{
	m_pTable = new CTable;
	m_pTable->Initialise();
	m_pTable->SetLogManager(m_pLogManager);

	return (true);
}

bool
CGame::InitialiseControlText()
{
	const int kiWindowHeight = CApplication::GetInstance().GetGameWindow().GetHeight();

	m_pTextControls1 = new CText();
	m_pTextControls1->SetText("Move mouse around cue ball to change the cue's angle");
	m_pTextControls1->SetPosition(X, 50);
	m_pTextControls1->SetPosition(Y, kiWindowHeight - 150);
	m_pTextControls1->SetDisplay(true);

	m_pTextControls2 = new CText();
	m_pTextControls2->SetText("Hold down left click and pull your mouse downwards to choose the amount of force");
	m_pTextControls2->SetPosition(X, 50);
	m_pTextControls2->SetPosition(Y, kiWindowHeight - 130);
	m_pTextControls2->SetDisplay(true);

	m_pTextControls3 = new CText();
	m_pTextControls3->SetText("Release left click to apply the force to the cue ball");
	m_pTextControls3->SetPosition(X, 50);
	m_pTextControls3->SetPosition(Y, kiWindowHeight - 110);
	m_pTextControls3->SetDisplay(true);

	return (false);
}

bool
CGame::DeinitialiseTextBuffer()
{
	delete m_cpTextBuffer;
	m_cpTextBuffer = 0;

	return (true);
}

bool
CGame::DeinitialiseDebugDialog()
{
	delete m_pDebugDialog;
	m_pDebugDialog = 0;

	return (true);
}

bool
CGame::DeinitialiseLogManager()
{
	delete m_pLogManager;
	m_pLogManager = 0;

	return (true);
}

bool
CGame::DeinitialiseMessageTarget()
{
	CApplication::GetInstance().GetGameWindow().GetMsgManager().RemoveMsgTarget(this);

	return (true);
}

bool
CGame::DeinitialiseTable()
{
	delete m_pTable;
	m_pTable = 0;

	return (true);
}

void
CGame::ProcessDebugDialog()
{
	bool bApplyPressed = m_pDebugDialog->IsApplyButtonPressed();

	if (bApplyPressed == true)
	{
		float fStaticDeltaTick = 0.0f;
		float fMaxFrames = 0.0f;

		m_pDebugDialog->GetDeltaTickField().GetValue(fStaticDeltaTick);
		m_pDebugDialog->GetMaxFramesField().GetValue(fMaxFrames);

		CClock& rClock = CApplication::GetInstance().GetGameWindow().GetClock();
		rClock.SetStaticDeltaTick(fStaticDeltaTick);
		rClock.SetMaxFrames(fMaxFrames);

	}
}

void
CGame::HandleMessage(EKeyCode _EKeyCode, WPARAM _wParam, LPARAM _lParam)
{
	switch (_EKeyCode)
	{
		case MSG_KEY_ESC_DWN:
		{
			m_pDebugDialog->SetDisplay(true);
			break;
		}

		default:
			break;
	}
}