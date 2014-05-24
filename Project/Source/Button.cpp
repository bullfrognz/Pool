//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   "-----"
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework
#include "Application.h"
#include "GameWindow.h"
#include "MessageManager.h"
#include "Sprite.h"
#include "Utilities.h"
// Core

// Game

// This Include
#include "Button.h"

// Static Variables

// Static Function Prototypes

// Implementation
CButton::CButton()
: m_pSprite(0)
, m_bHasBeenClicked(false)
, m_bDisplay(false)
{
	ZeroMemory(&m_rectBounds, sizeof(RECT));
	ZeroMemory(&m_crdMousePositionUp, sizeof(_COORD));
	ZeroMemory(&m_crdMousePositionDwn, sizeof(_COORD));
}

CButton::~CButton()
{
	CApplication::GetInstance().GetGameWindow().GetMsgManager().RemoveMsgTarget(this);

	delete m_pSprite;
	m_pSprite = 0;
}

bool
CButton::Initialise(const int _kiSpriteId, const int _kiMaskId)
{
	m_pSprite = new CSprite();
	m_pSprite->Initialise(_kiSpriteId, _kiMaskId);

	CMessageManager& rMessageManager = CApplication::GetInstance().GetGameWindow().GetMsgManager();

	rMessageManager.AddMsgTarget(MSG_MOUSE_LBUTTONDWN, this);
	rMessageManager.AddMsgTarget(MSG_MOUSE_LBUTTONUP, this);

	m_bDisplay = true;

	return true;
}

void
CButton::Process(float _fDeltaTick)
{
	m_bHasBeenClicked = false;

	if (IsWithinBounds(m_rectBounds, m_crdMousePositionUp) == true)  //The up click postion was within the buttons' bounds
	{
		if (IsWithinBounds(m_rectBounds, m_crdMousePositionDwn) == true) //The down click postion was within the buttons' bounds
		{
			if (m_bDisplay == true)
			{
				m_bHasBeenClicked = true;
			}

			ZeroMemory(&m_crdMousePositionDwn, sizeof(COORD));
		}

		ZeroMemory(&m_crdMousePositionUp, sizeof(COORD));
	}

	m_pSprite->Process(_fDeltaTick);
}

void
CButton::Draw()
{
	if (m_bDisplay == true)
	{
		const int kiPositionX = static_cast<int>(CEntity::m_Position[X]);
		const int kiPositionY = static_cast<int>(CEntity::m_Position[Y]);

		m_pSprite->SetPosition(kiPositionX, kiPositionY);
		m_pSprite->Draw();
	}
}

void
CButton::UpdateBounds()
{
	int iHalfSpriteWidth  = m_pSprite->GetSpriteWidth() / 2;
	int iHalfSpriteHeight = m_pSprite->GetSpriteHeight() / 2;

	int iPositionX = static_cast<int>(CEntity::m_Position[X]);
	int iPositionY = static_cast<int>(CEntity::m_Position[Y]);

	m_rectBounds.top    = iPositionY - iHalfSpriteHeight;
	m_rectBounds.left   = iPositionX - iHalfSpriteWidth;
	m_rectBounds.right  = iPositionX + iHalfSpriteWidth;
	m_rectBounds.bottom = iPositionY + iHalfSpriteHeight;
}

void
CButton::HandleMessage(EKeyCode _eMessageCode, WPARAM _wParam, LPARAM _lParam)
{
	switch (_eMessageCode)
	{
		case MSG_MOUSE_LBUTTONDWN:
		{
			m_crdMousePositionDwn.X = static_cast<int>(LOWORD(_lParam));
			m_crdMousePositionDwn.Y = static_cast<int>(HIWORD(_lParam));
			break;
		}

		case MSG_MOUSE_LBUTTONUP:
		{
			m_crdMousePositionUp.X = static_cast<int>(LOWORD(_lParam));
			m_crdMousePositionUp.Y = static_cast<int>(HIWORD(_lParam));
			break;
		}

		default:
			break;
	}
}