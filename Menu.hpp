//****************************************************************************
//
// HEADER NAME:
//      Menu.hpp
//
//****************************************************************************

#pragma once
#ifndef _Menu_hpp
#define _Menu_hpp

class Menu
{
public:
	//------------------------------------------------------------------------
	// Functions
	//------------------------------------------------------------------------	
	static void CreateUser();

	static void DisplayMenu();

	static unsigned int GetSelection();

	static void UserDisplay();
};

#endif