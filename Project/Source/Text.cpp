//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Text.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>

// Local Includes

// Framework
#include "Application.h"
#include "GameWindow.h"
#include "BackBuffer.h"

// Core

// Scene

// This Include
#include "Text.h"

// Static Variables

// Static Function Prototypes

// Implementation
CText::CText()
: m_wchrpText(0)
, m_iTextLength(0)
, m_iTextAlign(0)
, m_iTextColour(0)
, m_iFontWidth(0)
, m_iFontHeight(0)
, m_iFontWeight(0)
, m_fTimeLifeSpan(0.0f)
, m_fTimeElapsed(0.0f)
, m_byteItalic(FALSE)
, m_byteUnderPlane(FALSE)
, m_byteStrikeOut(FALSE)
, m_bDisplay(false)
{
}

CText::~CText()
{
	delete m_wchrpText;
	m_wchrpText = 0;

	DeleteObject(m_hFont);
}

bool
CText::Initialise()
{
	CEntity::Initialise();

	SetTextAlign(TEXTALIGN_LEFT);
	SetTextColour(TEXTCOLOUR_BLACK);

	m_iFontWidth = 8;
	m_iFontHeight = 16;
	m_iFontWeight = 100;

	UpdateFont();

	return (true);
}

void 
CText::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
	ProcessTimeLifeSpan(_fDeltaTick);
}

void
CText::Draw()
{
	if (m_bDisplay == true && m_iTextLength != 0)
	{
		CBackBuffer& rBackBuffer = CApplication::GetInstance().GetGameWindow().GetBackBuffer();

		::SetTextColor(rBackBuffer.GetBFDC(), m_iTextColour);
		::SetTextAlign(rBackBuffer.GetBFDC(), m_iTextAlign);
		
		HGDIOBJ hOldFont = SelectObject(rBackBuffer.GetBFDC(), m_hFont);
	              
		TextOut(rBackBuffer.GetBFDC(), static_cast<int>(CEntity::m_Position[X]), static_cast<int>(CEntity::m_Position[Y]), m_wchrpText, m_iTextLength);

		SelectObject(rBackBuffer.GetBFDC(), hOldFont);
	}
}


void
CText::ProcessTimeLifeSpan(float _fDeltaTick)
{
	if (m_fTimeLifeSpan != 0)
	{
		m_fTimeElapsed += _fDeltaTick;

		if (m_fTimeElapsed > m_fTimeLifeSpan)
		{
			m_fTimeLifeSpan = 0.0f;
			m_fTimeElapsed = 0.0f;
			m_bDisplay = false;

			return ;
		}
	}
}

void
CText::SetTextAlign(ETextAlign _eTextAlign)
{
	switch (_eTextAlign)
	{
		case TEXTALIGN_CENTER:
			m_iTextAlign = TA_CENTER;
			break;

		case TEXTALIGN_RIGHT:
			m_iTextAlign = TA_RIGHT;
			break;

		default:
			m_iTextAlign = TA_LEFT;
			break;
	}
}

void
CText::SetText(const char* _kcpText)
{
	m_iTextLength = static_cast<int>(strlen(_kcpText));

	if (m_wchrpText != 0)
	{
		delete m_wchrpText;
		m_wchrpText = 0;
	}

	m_wchrpText = ConvertConstCharToWchart(_kcpText);
}

void
CText::SetTextColour(ETextColour _eColor)
{
	switch (_eColor)
	{
		case TEXTCOLOUR_WHITE:
			m_iTextColour = RGB(255,255,255);
			break;

		case TEXTCOLOUR_BLACK:
			m_iTextColour = RGB(0,0,0);
			break;

		case TEXTCOLOUR_RED:
			m_iTextColour = RGB(172,23,23);
			break;

		case TEXTCOLOUR_GREEN:
			m_iTextColour = RGB(60,146,50);
			break;

		case TEXTCOLOUR_BLUE:
			m_iTextColour = RGB(0,0,255);
			break;

		case TEXTCOLOUR_LRED:
			m_iTextColour = RGB(255,0,0);
			break;

		case TEXTCOLOUR_LGREEN:
			m_iTextColour = RGB(0,255,0);
			break;

		case TEXTCOLOUR_LBLUE:
			m_iTextColour = RGB(70,163,255);
			break;

		case TEXTCOLOUR_ORANGE:
			m_iTextColour = RGB(240,96,0);
			break;

		default:
			assert(false); //Unknown colour.
			break;
	}
}

void
CText::UpdateFont()
{
	DeleteObject(m_hFont);

	m_hFont = CreateFont(m_iFontHeight,
						 m_iFontWidth,
						 0,0,
						 m_iFontWeight,
						 m_byteItalic, m_byteUnderPlane, m_byteStrikeOut,
						 DEFAULT_CHARSET,
						 OUT_DEFAULT_PRECIS,
						 CLIP_DEFAULT_PRECIS,
						 ANTIALIASED_QUALITY,
						 FF_MODERN,TEXT("Arial"));
}