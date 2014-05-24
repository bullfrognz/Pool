//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Plane.h
//  Description :   --------------------------
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_Plane_H__
#define __IGFEB11_IG220_Plane_H__

// Library Includes
#include <windows.h>

// Local Includes
#include "Entity.h"
#include "Vector3.h"
#include "PhysicsTarget.h"

// Types

// Constants

// Prototypes


class CPlane : public CEntity, public IPhysicsTarget
{
	// Member Functions
public:
	         CPlane();
	virtual ~CPlane();
	
	virtual bool Initialise(CVector3& _rStartPoint, CVector3& _rEndPoint);
	virtual bool Deinitialise();
	virtual void Process(float _fDeltaTick);
	virtual void Draw();

	void DrawBounds();

	void CalculateNormal();
	void CaluclateD();
	void CalculateMiddlePoint();
	void CalculateLength();

	// Member inline Functions
	inline void SetStartPoint(float _fValueX, float _fValueY, float _fValueZ);
	inline void SetEndPoint(float _fValueX, float _fValueY, float _fValueZ);
	inline void SetColour(COLORREF _colrefColour);

	inline CVector3 GetStartPoint() const;
	inline CVector3 GetEndPoint() const;
	inline COLORREF GetColour();

	inline CVector3 GetNormal() const;
	inline float GetD();
	inline float GetLength();
	inline CVector3 GetMiddlePoint();

protected:

private:
	CPlane(const CPlane& _kr);
	CPlane& operator= (const CPlane& _kr);

	// Member Variables
public:

protected:

private:
	CVector3 m_StartPoint;
	CVector3 m_EndPoint;
	CVector3 m_MiddlePoint;
	CVector3 m_Normal;

	COLORREF m_colrefColour;

	float m_fD;

	float m_fLength;

};

#include "Plane.inl"

#endif // __IGFEB11_IG220_Plane_H__