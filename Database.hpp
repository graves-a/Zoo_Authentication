//****************************************************************************
//
// HEADER NAME:
//      Database.hpp
//
//****************************************************************************
#pragma once
#include "sha256.h"
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <ostream>

class Database
{
public:
	//------------------------------------------------------------------------
    // Functions
	//------------------------------------------------------------------------	
	static int Callback( void* NotUsed, int argc, char** argv, char** azColName );

	static int CallbackID( void* NotUsed, int argc, char** argv, char** azColName );

	static void CreateDataBase();

	static void CreateTable();
	
	static void CreateUser
	(
	std::string username
	, std::string password
	, std::string firstName
	, std::string lastName
	, std::string email
	, std::string role
	);
	static void GetFirstName( int ID );

	static void GetUserID( std::string username );
	
	static void GetRole( int ID );

	static void SelectData();

	static void UpdateData( std::string item, std::string data, int ID );

	static void UpdateEmail();

	static void UpdatePassword();

	static void UpdateRole();

	static void UpdateUsername();

	static bool VerifyUser( std::string username, std::string password );
};

