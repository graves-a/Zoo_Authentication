//****************************************************************************
// @file Validation.cpp
//
//****************************************************************************
#include "Validation.hpp"
#include <regex>
#include <Windows.h>
#include <iostream>

// Global
int userID;

// retrieved from https://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt
HANDLE hStdin = GetStdHandle( STD_INPUT_HANDLE );
DWORD mode = 0;

//----------------------------------------------------------------------------
//! The user enters their username and password. Those credentials are checked
//! for SQL injection attempt and length of input is limited to 25 characters.
//! The credentials are then sent to the database.
//! @return bool verified
//----------------------------------------------------------------------------
bool Validation::GetCredentials()
{
	std::string username, password;
	size_t maxInput = 25;
	const std::regex regexReplace( "(or).*$" );
	const std::regex regexMatch( "\b(or)\s?(.+)=\s?\2.*" );
	
	std::cout << "Enter username: \n";
	std::cin >> username;
	std::cout << "\n";
	std::cout << "Enter password: \n";
	Validation::HideUserInput();
	std::cin >> password;
	std::cout << "\n";
	std::cin.clear();
	std::cin.ignore(256, '\n');
	

	// Checks the size of username/password -> max size = 25
	if (username.size() > maxInput || password.size() > maxInput)
	{
		std::cout << "Username/password too large\n";
	}

	// Checks for SQL Injection, if found, replace SQL characters
	if ( std::regex_match( username, regexMatch ) || std::regex_match( password, regexMatch ) )
	{
		username = std::regex_replace( username, regexReplace, "SQL Injection Detected!" );
		password = std::regex_replace( password, regexReplace, "SQL Injection Detected!" ); 
		std::cout << username << std::endl;
		std::cout << password << std::endl;
	}

	// Checks user credentials against database, true if verified, false if unverified
	bool verified = Database::VerifyUser( username, password ); 

	Validation::UnhideUserInput();
	return verified;
} // end of function Validation::GetCredentials()

//----------------------------------------------------------------------------
//! Sets the user ID to be used with other user options
//----------------------------------------------------------------------------
void Validation::SetUserID( int newID )
{
	userID = newID;
} // end of function Validation::SetUserID

//----------------------------------------------------------------------------
//! Gets the user ID to be used with other user options
//----------------------------------------------------------------------------
int Validation::GetUserID()
{
	return userID;
} // end of function Validation::GetUserID()

//----------------------------------------------------------------------------
//! Resets the userID
//----------------------------------------------------------------------------
void Validation::ClearUserID()
{
	userID = NULL;
} // end of function Validation::ClearUserID()

//----------------------------------------------------------------------------
//! Hides user input
//----------------------------------------------------------------------------
void Validation::HideUserInput()
{

	// retrieved from https://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt
	GetConsoleMode( hStdin, &mode );
	SetConsoleMode( hStdin, mode & ( ~ENABLE_ECHO_INPUT ) );
} // end function Validation::HideUserInput()

//----------------------------------------------------------------------------
//! Unhides user input
//----------------------------------------------------------------------------
void Validation::UnhideUserInput()
{
	// retrieved from https://stackoverflow.com/questions/6899025/hide-user-input-on-password-prompt
	SetConsoleMode( hStdin, mode  );
} // end function Validation::UnhideUserInput()
