//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Button.inl
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

void
CButton::SetDisplay(bool _bDisplay)
{
	m_bDisplay = _bDisplay;
}

bool
CButton::HasBeenClicked() const
{
	return (m_bHasBeenClicked);
}

bool
CButton::IsDisplaying() const
{
	return (m_bDisplay);
}