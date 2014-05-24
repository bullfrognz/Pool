//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   LogManager.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_LOGMANAGER_H__
#define __IGFEB11_IG220_LOGMANAGER_H__

// Library Includes
#include <vector>

// Local Includes
#include "LogTarget.h"

// Types
enum ELogTarget
{
	LOGTARGET_INVALID,
	LOGTARGET_FILE,
	LOGTARGET_OUTPUT,
	LOGTARGET_GAMEWINDOW,
	LOGTARGET_MAX
};


// Constants

// Prototypes


class CLogManager
{
    // Member Functions
public:
	 CLogManager();
	~CLogManager();

	bool Initialise();
	bool Deinitialise();
	void Process(float _fDeltaTick);
	void Draw();

	bool AddLogTarget(ELogTarget _eLogTarget);
	bool RemoveLogTarget(ELogTarget _eLogTarget);

	void Write(const char* _kcpMessage);
	void WriteOutput(const char* _kcpMessage);

	// Member inline Function
	inline void WriteVariable(const char* _kcpTitle, int _piValue);
	inline void WriteVariable(const char* _kcpTitle, float _pfValue);
	inline void WriteVariable(const char* _kcpTitle, char _pcValue);
	inline void WriteVariable(const char* _kcpTitle, bool _pbValue);

protected:

private:
	CLogManager(const CLogManager& _kr);
	CLogManager& operator= (const CLogManager& _kr);

    // Member Variables
public:

protected:

private:
	static const int s_kiTextBufferSize = 128;
	char* m_cpTextBuffer;

	std::vector<ILogTarget*> m_vecLogTargets;

};

#include "LogManager.inl"

#endif // __IGFEB11_IG220_LOGMANAGER_H__
