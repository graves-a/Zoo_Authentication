//****************************************************************************
// @file Menu.cpp
//
//****************************************************************************
#include "Menu.hpp"
#include "Database.hpp"
#include "Validation.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

//----------------------------------------------------------------------------
//! Displays the main menu 
//----------------------------------------------------------------------------
void Menu::DisplayMenu()
{
	std::cout << "1) Login\n";
	std::cout << "2) Create Accout\n";
	std::cout << "3) Exit\n";
} // end of function Menu::DisplayMenu()

//----------------------------------------------------------------------------
//! Gets the selection from the main menu
//! @return The selection
//----------------------------------------------------------------------------
unsigned int Menu::GetSelection()
{
	unsigned short int selection;

	std::cin >> selection;
	while( std::cin.fail() || selection < 1 || selection > 3 )
	{
		std::cout << "Error: Please enter valid selection\n";
		std::cin.clear();
		std::cin.ignore(256, '\n');
		std::cin >> selection;
	}
	std::cout << "\n";

	return selection;
} // end of function Menu::GetSelection()

//----------------------------------------------------------------------------
//! Creates a new user and inserts it into the database
//! Users inputs a username, password, first name, last name, email, and role
//----------------------------------------------------------------------------
void Menu::CreateUser()
{
	std::string username, password, password2, firstName, lastName, email, role;
	std::cout << "Enter a username\n";
	std::cin >> username;
	std::cout << "\n";
	std::cout << "Enter a password\n";
	Validation::HideUserInput();
	std::cin >> password;
	std::cout << "\n";
	std::cout << "Re-enter password\n";
	std::cin >> password2;
	std::cout << "\n";
	while ( password != password2 )
	{
		std::cout << "Your passwords didn't match up, please try again.\n\n";
		std::cout << "Enter a password\n";
		std::cin >> password;
		std::cout << "\n";
		std::cout << "Re-enter password\n";
		std::cin >> password2;
		std::cout << "\n";
	}
	Validation::UnhideUserInput();
	std::cout << "Enter your first name\n";
	std::cin >> firstName;
	std::cout << "\n";
	std::cout << "Enter your last name\n";
	std::cin >> lastName;
	std::cout << "\n";
	std::cout << "Enter an email\n";
	std::cin >> email;
	std::cout << "\n";
	std::cout << "Enter role description\n";
	std::cin.ignore();
	std::getline( std::cin, role );
	std::cout << "\n";

	Database::CreateUser( username, password, firstName, lastName, email, role );
} // end of function Menu::CreateUser()

//----------------------------------------------------------------------------
//! Menu to be displayed when the user is logged in
//----------------------------------------------------------------------------
void Menu::UserDisplay()
{
	std::cout << "1) Update role\n";
	std::cout << "2) Update email\n";
	std::cout << "3) Update username\n";
	std::cout << "4) Update password\n";
	std::cout << "9) Logoff\n";
} // end function Menu::UserDisplay()
