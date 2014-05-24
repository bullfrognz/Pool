//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   LogTarget.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_LOGTARGET_H__
#define __IGFEB11_IG220_LOGTARGET_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes


class ILogTarget
{
    // Member Functions
public:
	         ILogTarget() {};
	virtual ~ILogTarget() {};

	virtual void Initialise() = 0;
	virtual void Deinitialise() = 0;
	virtual void Process(float _fDeltaTick) = 0;
	virtual void Draw() = 0;

	virtual void Write(const char* _pcMessage) = 0;

protected:

private:
	ILogTarget(const ILogTarget& _kr);
	ILogTarget& operator= (const ILogTarget& _kr);

    // Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_IG220_LOGTARGET_H__
