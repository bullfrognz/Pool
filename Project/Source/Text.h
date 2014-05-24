//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Text.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_TEXT_H__
#define __IGFEB11_IG220_TEXT_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "Entity.h"

// Types
enum ETextColour
{
	TEXTCOLOUR_INVALID,
	TEXTCOLOUR_WHITE,
	TEXTCOLOUR_BLACK,
	TEXTCOLOUR_RED,
	TEXTCOLOUR_GREEN,
	TEXTCOLOUR_BLUE,
	TEXTCOLOUR_LRED,
	TEXTCOLOUR_LGREEN,
	TEXTCOLOUR_LBLUE,
	TEXTCOLOUR_ORANGE,
	TEXTCOLOUR_MAX
};

enum ETextAlign
{
	TEXTALIGN_INVALID,
	TEXTALIGN_LEFT,
	TEXTALIGN_CENTER,
	TEXTALIGN_RIGHT,
	TEXTALIGN_MAX
};

enum ETextWeight
{
	TEXTWEIGHT_INVALID,
	TEXTWEIGHT_NORMAL,
	TEXTWEIGHT_HEAVY,
	TEXTWEIGHT_MAX
};

// Constants

// Prototypes

class CText : public CEntity
{
    // Member Functions
public:
	         CText();
	virtual ~CText();

	virtual bool Initialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	void ProcessTimeLifeSpan(float _fDeltaTick);

	void SetText(const char* _kcpText);
	void SetTextColour(ETextColour _eColour);
	void SetTextAlign(ETextAlign _eTextAlign);

	void UpdateFont();

	// Member inline Functions
	inline void SetFontWidth(int _iWidth);
	inline void SetFontHeight(int _iHeight);
	inline void SetFontWeight(ETextWeight _eWeight);
	inline void SetFontWeight(int _iWeight);
	inline void SetFont(int _iWidth, int _iHeight, ETextWeight _eWeight);
	inline void SetFontItalic(bool _bItalic);
	inline void SetFontUnderPlane(bool _bUnderPlane);
	inline void SetFontStrikeOut(bool _bStrikeOut);
	inline void SetTimeLifeSpan(float _fFrameSpan);
	inline void SetDisplay(bool _bDisplay);

	inline int GetFontWidth() const;
	inline int GetFontHeight() const;
	inline int GetFontWeight() const;

	inline bool IsFontItalic() const;
	inline bool IsFontUnderPlane() const;
	inline bool IsFontStrikeOut() const;

	inline bool IsDisplaying() const;

protected:

private:
	CText(const CText& _kr);
	CText& operator= (const CText& _kr);

    // Member Variables
public:

protected:

private:
	HFONT m_hFont;

	wchar_t* m_wchrpText;
	int m_iTextLength;
	int m_iTextAlign;
	int m_iTextColour;

	int m_iFontWidth;
	int m_iFontHeight;
	int m_iFontWeight;

	float m_fTimeLifeSpan;
	float m_fTimeElapsed;

	BYTE m_byteItalic;
	BYTE m_byteUnderPlane;
	BYTE m_byteStrikeOut;

	bool m_bDisplay;

};

#include "Text.inl"

#endif // __IGFEB11_IG220_TEXT_H__
