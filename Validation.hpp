//****************************************************************************
//
// HEADER NAME:
//      Validation.hpp
//
//****************************************************************************

#pragma once
#ifndef _Validation_hpp
#define _Validation_hpp

#include "Database.hpp"
#include <iostream>
#include <regex>
#include <string>

class Validation
{	
//------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------	
public:
	static bool GetCredentials();

	static void SetUserID( int newID );

	static int GetUserID();

	static void ClearUserID();

	static void HideUserInput();

	static void UnhideUserInput();
};

#endif