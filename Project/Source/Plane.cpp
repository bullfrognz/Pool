//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Plane.cpp
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include "windows.h"

// Local Includes

// Framework
#include "Application.h"
#include "GameWindow.h"
#include "BackBuffer.h"

// Core

// Content

// This Include
#include "Plane.h"

// Static Variables

// Static Function Prototypes

// Implementation

CPlane::CPlane()
: m_fD(0.0f)
{
}

CPlane::~CPlane()
{
	Deinitialise();
}

bool
CPlane::Initialise(CVector3& _rStartPoint, CVector3& _rEndPoint)
{
	CEntity::Initialise();

	m_StartPoint = _rStartPoint;
	m_EndPoint = _rEndPoint;

	CalculateNormal();
	CaluclateD();
	CalculateMiddlePoint();
	CalculateLength();

	return (true);
}

bool
CPlane::Deinitialise()
{
	CEntity::Deinitialise();

	return (true);
}

void
CPlane::Process(float _fDeltaTick)
{
	CEntity::Process(_fDeltaTick);
}

void
CPlane::Draw()
{
	CEntity::Draw();
	DrawBounds();
}

void
CPlane::DrawBounds()
{
	CBackBuffer& rBackBuffer = CApplication::GetInstance().GetGameWindow().GetBackBuffer();

	HPEN newpen = CreatePen(PS_SOLID, 1, m_colrefColour);
	HGDIOBJ oldpen = SelectObject(rBackBuffer.GetBFDC(),newpen);

	MoveToEx(rBackBuffer.GetBFDC(), (int)m_StartPoint[X], (int)m_StartPoint[Y], NULL);
	LineTo(rBackBuffer.GetBFDC(), (int)m_EndPoint[X], (int)m_EndPoint[Y]);

	SelectObject(rBackBuffer.GetBFDC(), oldpen);
	DeleteObject(newpen);

	//m_colrefColour = RGB(0, 0, 255);
}

void
CPlane::CalculateNormal()
{
	CVector3 PlanePoint3(m_EndPoint[X], m_EndPoint[Y], 100.0f);

	CVector3 PlanePoint4;
	PlanePoint4[X] = (m_StartPoint[X] - m_EndPoint[X]);
	PlanePoint4[Y] = (m_StartPoint[Y] - m_EndPoint[Y]);
	PlanePoint4[Z] = (m_StartPoint[Z] - m_EndPoint[Z]);

	CVector3 PlanePoint5;
	PlanePoint5[X] = (m_StartPoint[X] - PlanePoint3[X]);
	PlanePoint5[Y] = (m_StartPoint[Y] - PlanePoint3[Y]);
	PlanePoint5[Z] = (m_StartPoint[Z] - PlanePoint3[Z]);

	CVector3::Cross(PlanePoint5, PlanePoint4, m_Normal);
}

void
CPlane::CaluclateD()
{
	CVector3 Temp = m_Normal;
	Temp.Normalise();

	m_fD = CVector3::Dot(m_StartPoint, Temp);
}

void
CPlane::CalculateMiddlePoint()
{
	CVector3 Line;
	Line[X] = m_EndPoint[X] - m_StartPoint[X];
	Line[Y] = m_EndPoint[Y] - m_StartPoint[Y];
	Line[Z] = m_EndPoint[Z] - m_StartPoint[Z];

	Line.Scale(0.5f);

	Line[X] += m_StartPoint[X];
	Line[Y] += m_StartPoint[Y];
	Line[Z] += m_StartPoint[Z];

	m_MiddlePoint[X] = Line[X];
	m_MiddlePoint[Y] = Line[Y];
	m_MiddlePoint[Z] = Line[Z];
}

void
CPlane::CalculateLength()
{
	CVector3 Difference;

	Difference[X] = m_EndPoint[X] - m_StartPoint[X];
	Difference[Y] = m_EndPoint[Y] - m_StartPoint[Y];
	Difference[Z] = m_EndPoint[Z] - m_StartPoint[Z];

	m_fLength = CVector3::GetMagnitude(Difference);
}