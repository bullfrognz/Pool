//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Scene.h
//  Description :   Template for decoration (header) file
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_IG220_SCENE_H__
#define __IGFEB11_IG220_SCENE_H__

// Library Includes

// Local Includes

// Types


// Constants

// Prototypes


class IScene
{
    // Member Functions
public:
		     IScene() {};
	virtual ~IScene() {};

	virtual bool Initialise() = 0;
	virtual bool Deinitialise() = 0;
	virtual void Process(float _fDeltatick) = 0;
	virtual void Draw() = 0;

protected:

private:
	IScene(const IScene& _kr);
	IScene& operator= (const IScene& _kr);

    // Member Variables
public:

protected:

private:

};

#endif // __IGFEB11_IG220_SCENE_H__
