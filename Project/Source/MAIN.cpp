//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MAIN.cpp
//  Description :   Template for implementation (source) files
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>
#include <windowsx.h>
//#include <vld.h>
#include <vector>

// Local Includes
#include "Resource.h"

// Framework
#include "DebugDialog.h"
#include "Application.h"
#include "GameWindow.h"


// Core

// Scene
#include "Scene.h"

// Static Variables

// Static Function Prototypes
class CDebugDialog;

// Implementation
int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _1pCmdPlane, int _iCmdShow)
{
	// Application Setup
	CApplication& rApplication = CApplication::GetInstance();
	rApplication.Initialise(_hInstance);

	// Game Window Setup
	CGameWindow& rGameWindow = rApplication.GetGameWindow();
	rGameWindow.Initialise(L"Extreme Pool",
						   WS_BORDER | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
						   100, 100,
						   1152, 864);

	// Set Startup Game Window Scene
	rGameWindow.SetScene(SCENE_GAME);
	
	// Main Loop Default Variables
	std::vector<HWND>& rvecDialogHandles = rApplication.GetDialogHandles();
	std::vector<HWND>::iterator IterDialogHandle;
	bool bIsDialogMessage = false;

	MSG msgWindowsMessage;
	msgWindowsMessage.wParam = 0;

	bool bRunLoop = true;
	if (strcmp(_1pCmdPlane, "--testharness") == 0)
	{
		
		//bRunLoop = false;
	}

	// Main Loop
	while (bRunLoop == true)
	{
		if (PeekMessage(&msgWindowsMessage, NULL, 0, 0, PM_REMOVE))
		{
			// Check if the message contains the quit command
			if (msgWindowsMessage.message == WM_QUIT)
			{
				break;
			}

			// Reset Variables
			bIsDialogMessage = false;
			IterDialogHandle = rvecDialogHandles.begin();

			// Check if the message was for a dialog
			while (IterDialogHandle != rvecDialogHandles.end())
			{
				if (IsDialogMessage((*IterDialogHandle), &msgWindowsMessage))
				{
					bIsDialogMessage = true;
					break;
				}
				else
				{
					++ IterDialogHandle;
				}
			}

			// Send message to nessage pump
			if (bIsDialogMessage == false)
			{
				TranslateMessage(&msgWindowsMessage); //Translate any accesserator keys
				DispatchMessage(&msgWindowsMessage);  //Send the message to the window proc
			}
		}

		// Run the main game window loop once
		rGameWindow.ExecuteOneFrame();
	}

	CApplication::DestroyInstance();

	return (static_cast<int>(msgWindowsMessage.wParam)); //Return to windows
}