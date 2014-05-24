//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   ------.inl
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// Framework

// Core

// Content

// Static Variables

// Static Function Prototypes

// Implementation

void
CPlayer::SetBallOwnerType(EBallType m_eType)
{
	m_eBallOwnerType = m_eType;
}


EBallType
CPlayer::GetBallOwnerType()
{
	return (m_eBallOwnerType);
}

CText&
CPlayer::GetNameText()
{
	return (*m_pNameText);
}