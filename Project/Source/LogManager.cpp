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
#include <cassert>
#include <cstring>

// Local Includes
#include "LogTarget.h"
#include "LogGameWindow.h"
#include "LogOutputWindow.h"

// This Include
#include "LogManager.h"

// Static Variables

// Static Function Prototypes

// Implementation
CLogManager::CLogManager()
: m_cpTextBuffer(0)
{
}

CLogManager::~CLogManager()
{
	Deinitialise();
}

bool 
CLogManager::Initialise()
{
	m_cpTextBuffer = new char[s_kiTextBufferSize];

	return(true);
}

bool
CLogManager::Deinitialise()
{
	delete m_cpTextBuffer;
	m_cpTextBuffer = 0;

	std::vector<ILogTarget*>::iterator Iter;

	for(Iter = m_vecLogTargets.begin(); Iter != m_vecLogTargets.end(); ++Iter)
	{
		delete (*Iter);
		(*Iter) = 0;
	}

	return (true);
}

void
CLogManager::Process(float _fDeltaTick)
{
	std::vector<ILogTarget*>::iterator Iter;

	for(Iter = m_vecLogTargets.begin(); Iter != m_vecLogTargets.end(); ++Iter)
	{
		(*Iter)->Process(_fDeltaTick);
	}
}

void
CLogManager::Draw()
{
	std::vector<ILogTarget*>::iterator Iter;

	for(Iter = m_vecLogTargets.begin(); Iter != m_vecLogTargets.end(); ++Iter)
	{
		(*Iter)->Draw();
	}
}

bool 
CLogManager::AddLogTarget(ELogTarget _eLogTarget)
{
	ILogTarget* pLogTarget = 0;

	switch (_eLogTarget)
	{
	case LOGTARGET_FILE:
		break;

	case LOGTARGET_OUTPUT:
		pLogTarget = new CLogOutputWindow();
		break;

	case LOGTARGET_GAMEWINDOW:
		pLogTarget = new CLogGameWindow();
		break;
	}

	pLogTarget->Initialise();

	m_vecLogTargets.push_back(pLogTarget);

	return(false);
}

bool 
CLogManager::RemoveLogTarget(ELogTarget _eLogTarget)
{
	return(true);
}

void 
CLogManager::Write(const char* _pcMessage)
{
	std::vector<ILogTarget*>::iterator iter;

	iter = m_vecLogTargets.begin();

	(*iter)->Write(_pcMessage);
}

void 
CLogManager::WriteOutput(const char* _pcMessage)
{
	std::vector<ILogTarget*>::iterator iter;

	iter = m_vecLogTargets.begin() + 1;

	(*iter)->Write(_pcMessage);
}