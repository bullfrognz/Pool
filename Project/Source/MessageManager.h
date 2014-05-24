//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MessageManager.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_MESSAGEMANAGER_H__
#define __IGFEB11_IG220_MESSAGEMANAGER_H__

// Library Includes
#include <windows.h>
#include <map>

// Local Includes

// Types
enum EKeyCode
{
	MSG_INVALID = 0,
	MSG_MOUSE_MOVE = 1000,
	MSG_MOUSE_LBUTTONUP  = 1100,
	MSG_MOUSE_LBUTTONDWN = 1101,
	MSG_MOUSE_RBUTTONUP  = 1200,
	MSG_MOUSE_RBUTTONDWN = 1201,

	MSG_KEY_W_UP  = 1501,
	MSG_KEY_W_DWN = 1502,
	MSG_KEY_S_UP  = 1511,
	MSG_KEY_S_DWN = 1512,
	MSG_KEY_A_UP  = 1521,
	MSG_KEY_A_DWN = 1522,
	MSG_KEY_D_UP  = 1531,
	MSG_KEY_D_DWN = 1532,

	MSG_KEY_R_UP  = 1541,
	MSG_KEY_R_DWN = 1542,

	MSG_KEY_Q_DWN = 1601,
	MSG_KEY_E_DWN = 1602,
	MSG_KEY_T_DWN = 1603,
	MSG_KEY_Y_DWN = 1604,
	MSG_KEY_U_DWN = 1605,
	MSG_KEY_I_DWN = 1606,
	MSG_KEY_O_DWN = 1607,
	MSG_KEY_P_DWN = 1608,
	MSG_KEY_F_DWN = 1609,
	MSG_KEY_G_DWN = 1610,
	MSG_KEY_H_DWN = 1611,
	MSG_KEY_J_DWN = 1612,
	MSG_KEY_K_DWN = 1613,
	MSG_KEY_L_DWN = 1614,
	MSG_KEY_Z_DWN = 1615,
	MSG_KEY_X_DWN = 1616,
	MSG_KEY_C_DWN = 1617,
	MSG_KEY_V_DWN = 1618,
	MSG_KEY_B_DWN = 1619,
	MSG_KEY_N_DWN = 1620,
	MSG_KEY_M_DWN = 1621,
	MSG_KEY_ESC_DWN = 1650,
	MSG_KEY_BACKSPACE_DWN = 1651,
	MSG_KEY_ENTER_DWN = 1652,

	MSG_KEY_Q_UP = 1701,
	MSG_KEY_E_UP = 1702,
	MSG_KEY_T_UP = 1703,
	MSG_KEY_Y_UP = 1704,
	MSG_KEY_U_UP = 1705,
	MSG_KEY_I_UP = 1706,
	MSG_KEY_O_UP = 1707,
	MSG_KEY_P_UP = 1708,
	MSG_KEY_F_UP = 1709,
	MSG_KEY_G_UP = 1710,
	MSG_KEY_H_UP = 1711,
	MSG_KEY_J_UP = 1712,
	MSG_KEY_K_UP = 1713,
	MSG_KEY_L_UP = 1714,
	MSG_KEY_Z_UP = 1715,
	MSG_KEY_X_UP = 1716,
	MSG_KEY_C_UP = 1717,
	MSG_KEY_V_UP = 1718,
	MSG_KEY_B_UP = 1719,
	MSG_KEY_N_UP = 1720,
	MSG_KEY_M_UP = 1721,
	MSG_KEY_ESC_UP = 1750,
	MSG_KEY_BACKSPACE_UP = 1751,
	MSG_KEY_ENTER_UP = 1752,

	MSG_MAX
};

// Constants

// Prototypes
class IMessageTarget;

class CMessageManager
{
    // Member Functions
public:
	 CMessageManager();
	~CMessageManager();

	bool AddMsgTarget(EKeyCode _iMsgCommand, IMessageTarget* _pLogTarget);
	bool RemoveMsgTarget(IMessageTarget* _pLogTarget);

	bool ClearMsgTargets();

	void SendMsgToTargets(EKeyCode _EKeyCode, WPARAM _wParam, LPARAM _lParam); 

protected:

private:
	CMessageManager(const CMessageManager& _kr);
	CMessageManager& operator= (const CMessageManager& _kr);

    // Member Variables
public:

protected:

private:
	std::multimap<EKeyCode, IMessageTarget*> m_mmapTargetContainer;

};

#endif // __IGFEB11_IG220_MESSAGEMANAGER_H__
