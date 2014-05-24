//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameDefines.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_GAMEDEFINES_H__
#define __IGFEB11_IG220_GAMEDEFINES_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
enum ETableType
{
	TABLETYPE_REGULAR,
	TABLETYPE_ALTERNATE,
	TABLETYPE_MAX
};

const char g_kcTableTypeName[TABLETYPE_MAX][32] = { "TableRegular", "TableAlternate" };

enum ECueState
{
	CUESTATE_INVALID,
	CUESTATE_CHOOSEANGLE,
	CUESTATE_CHOOSEPOWER,
	CUESTATE_RELEASEPOWER,
	CUESTATE_MAX
};

enum EBallType
{
	BALLTYPE_INVALID,
	BALLTYPE_CUE,
	BALLTYPE_BLACK,
	BALLTYPE_SOLID,
	BALLTYPE_STRIPE,
	BALLTYPE_MAX = 6
};

const char g_kcBallTypeName[BALLTYPE_MAX + 1][32] = { "INVALID", "CUE", "BLACK", "SOLID", "STRIPED", "BALL MAX" };

enum EBall
{
	BALL_CUE,
	BALL_01,
	BALL_02,
	BALL_03,
	BALL_04,
	BALL_05,
	BALL_06,
	BALL_07,
	BALL_08,
	BALL_09,
	BALL_10,
	BALL_11,
	BALL_12,
	BALL_13,
	BALL_14,
	BALL_15,
	BALL_MAX
};

enum EPlayer
{
	PLAYER_INVALID = -1,
	PLAYER_ONE,
	PLAYER_TWO,
	PLAYER_MAX
};

enum EGameState
{
	GAMESTATE_INVALID,
	GAMESTATE_INITIALISE,
	GAMESTATE_BREAK,
	GAMESTATE_PLAYERTURN,
	GAMESTATE_CUEINHAND,
	GAMESTATE_PROCESSINGPHYSICS,
	GAMESTATE_GAMEOVER,
	GAMESTATE_MAX
};

enum EMouseButtonState
{
	MBS_INVALID,
	MBS_IDLE,
	MBS_RELEASED,
	MBS_DOWN,
	MBS_MAX
};

enum ERefereeDecidion
{
};

#endif // __IGFEB11_IG220_GAMEDEFINES_H__