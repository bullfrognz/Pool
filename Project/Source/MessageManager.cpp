//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MessageManager.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "MessageTarget.h"

// This Include
#include "MessageManager.h"

// Static Variables

// Static Function Prototypes

// Implementation
CMessageManager::CMessageManager()
{
	//Empty
}

CMessageManager::~CMessageManager()
{
	//Empty
}

bool
CMessageManager::AddMsgTarget(EKeyCode _iMsgCommand, IMessageTarget* _pLogTarget)
{
	m_mmapTargetContainer.insert( std::pair<EKeyCode,IMessageTarget*>(_iMsgCommand,_pLogTarget) );

	return (true);
}

bool
CMessageManager::RemoveMsgTarget(IMessageTarget* _pLogTarget)
{

	std::multimap<EKeyCode,IMessageTarget*>::iterator Iter;

	for (Iter = m_mmapTargetContainer.begin(); Iter != m_mmapTargetContainer.end();  )
	{
		if ((*Iter).second == _pLogTarget)
		{
			Iter = m_mmapTargetContainer.erase(Iter);
		}
		else
		{
			++Iter;
		}
	}

	return (true);
}

bool
CMessageManager::ClearMsgTargets()
{
	m_mmapTargetContainer.clear();

	return true;
}

void
CMessageManager::SendMsgToTargets(EKeyCode _EKeyCode, WPARAM _wParam, LPARAM _lParam)
{
	std::multimap<EKeyCode,IMessageTarget*>::iterator Iter;

	for (Iter = m_mmapTargetContainer.begin(); Iter != m_mmapTargetContainer.end(); ++Iter )
	{
		if ((*Iter).first == _EKeyCode)
		{
			(*Iter).second->HandleMessage(_EKeyCode, _wParam, _lParam);
		}
	}
}