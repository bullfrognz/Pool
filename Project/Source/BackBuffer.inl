//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Backbuffer.inl
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
HDC
CBackBuffer::GetBFDC() const
{	
	return (m_hDC);
}

int
CBackBuffer::GetWidth() const
{

	return (m_iWidth);
}

int
CBackBuffer::GetHeight() const
{

	return (m_iHeight);
}