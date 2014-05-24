//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Game.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_Game_H__
#define __IGFEB11_IG220_Game_H__

// Library Includes

// Local Includes
#include "MessageTarget.h"
#include "GameDefines.h"
#include "Scene.h"

// Types

// Constants

// Prototypes
class CTable;
class CLogManager;
class CDebugDialog;
class CButton;
class CText;

class CGame : public IScene, public IMessageTarget
{
    // Member Functions
public:
	 CGame();
	~CGame();

	virtual bool Initialise();
	virtual bool Deinitialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	bool InitialiseTextBuffer();
	bool InitialiseDebugDialog();
	bool InitialiseLogManager();
	bool IntiialiseMessageTarget();
	bool IntiailiseTable();
	bool InitialiseControlText();

	bool DeinitialiseTextBuffer();
	bool DeinitialiseDebugDialog();
	bool DeinitialiseLogManager();
	bool DeinitialiseMessageTarget();
	bool DeinitialiseTable();

	void ProcessDebugDialog();

	virtual void HandleMessage(EKeyCode _EKeyCode, WPARAM _wParam, LPARAM _lParam);

	// Member inline Functions

protected:

private:
	CGame(const CGame& _kr);
	CGame& operator= (const CGame& _kr);

    // Member Variables
public:

protected:

private:
	static const int s_kiTextBufferSize = 64;
	char* m_cpTextBuffer;

	CDebugDialog* m_pDebugDialog;
	CLogManager* m_pLogManager;

	CTable* m_pTable;

	CButton* m_pResetButton;

	CText* m_pTextControls1;
	CText* m_pTextControls2;
	CText* m_pTextControls3;

};

#include "Game.inl"

#endif // __IGFEB11_IG220_Game_H__
