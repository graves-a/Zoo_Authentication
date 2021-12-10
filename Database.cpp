//****************************************************************************
// @file Database.cpp
//
//****************************************************************************
#include "Database.hpp"
#include "Validation.hpp"
#include <string>

// Constant directory location
const char* directory = "D:\\ZooDatabase.db";

// Global variables
sqlite3* DB;
char* messageError;
std::string sql;
int ID = 0;

//----------------------------------------------------------------------------
//! Creates the zoo database and inserts the table
//----------------------------------------------------------------------------
void Database::CreateDataBase()
{
	int exit = sqlite3_open( directory, &DB );
	Database::CreateTable();
	sqlite3_close( DB );
} // end function Database::CreateDataBase()

//----------------------------------------------------------------------------
//! Creates the table to be inserted into the zoo database
//----------------------------------------------------------------------------
void Database::CreateTable()
{
	sql = "CREATE TABLE IF NOT EXISTS ZOO("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"USERNAME	TEXT NOT NULL, "
		"PASSWORD	TEXT NOT NULL, "
		"FIRSTNAME  TEXT NOT NULL, "
		"LASTNAME   TEXT NOT NULL, "
		"EMAIL		TEXT NOT NULL, "
		"ROLE		TEXT NOT NULL );";

	try
	{
		int exit = 0;
		exit = sqlite3_open( directory, &DB );

		char* messageError;
		exit = sqlite3_exec( DB, sql.c_str(), NULL, 0, &messageError );

		if ( exit != SQLITE_OK )
		{
			std::cerr << "Error Create Table\n";
			sqlite3_free( messageError );
		}
		else
		{
			// uncomment to see if the table was created successfully
			//std::cout << "Table created successfully\n";
			sqlite3_close( DB );
		}
	}
	catch ( const std::exception& error )
	{
		std::cerr << error.what();
	}
	sqlite3_close( DB );
} // end function Database::CreateTable()

//----------------------------------------------------------------------------
//! Creates a user with their username, password, first name, last name,
//! email, and their role.
//----------------------------------------------------------------------------
void Database::CreateUser
	(
		  std::string username
		, std::string password
		, std::string firstName
		, std::string lastName
		, std::string email
		, std::string role
	)
{
	int exit = sqlite3_open( directory, &DB );

	sql = "INSERT INTO ZOO (USERNAME, PASSWORD, FIRSTNAME, LASTNAME, EMAIL, ROLE) VALUES('"
		+ username + "', '"
		+ sha256(password) + "', '"
		+ firstName + "', '"
		+ lastName + "', '"
		+ email + "', '"
		+ role + "');";


	exit = sqlite3_exec( DB, sql.c_str(), NULL, 0, &messageError );
	if ( exit != SQLITE_OK )
	{
		std::cerr << "Error Insert\n";
		sqlite3_free( messageError );
	}
	else
	{
		std::cout << "Account created successfully!\n";
	}
	sqlite3_close( DB );
} // end function Database::CreateUser()

//----------------------------------------------------------------------------
//! Used for testing purposed, will display the entire database
//----------------------------------------------------------------------------
void Database::SelectData()
{
	int exit = sqlite3_open( directory, &DB );
	sql = "SELECT * FROM ZOO";
	exit = sqlite3_exec( DB, sql.c_str(), Callback, NULL, NULL );
	sqlite3_close( DB );
}// end function Database::SelectData()

//----------------------------------------------------------------------------
//! Used to traverse the SELECT statements
//! argc: holds the number of results, argv: holds each value in an array,
//! azColName: holds each column returned in an array
//----------------------------------------------------------------------------
int Database::Callback( void* NotUsed, int argc, char** argv, char** azColName )
{
	for ( int i = 0; i < argc; i++ )
	{
		// column name and value
		std::cout << argv[i];
	}

	return 0;
} // end function Database::Callback()

int Database::CallbackID( void* NotUsed, int argc, char** argv, char** azColName )
{
	
	for ( int i = 0; i < argc; i++ )
	{
		ID = atoi(argv[i]);
	}
	Validation::SetUserID( ID );
	return 0;
}

//----------------------------------------------------------------------------
//! Gets the user's role given their username
//----------------------------------------------------------------------------
void Database::GetRole( int ID )
{
	int exit = sqlite3_open( directory, &DB );

	sql = "SELECT ROLE FROM ZOO WHERE ID = '" + std::to_string(ID) + "';";

	sqlite3_exec( DB, sql.c_str(), Callback, NULL, NULL );
	sqlite3_close( DB );
} // end function Database::GetRole()

//----------------------------------------------------------------------------
//! Gets the user's first name for the greeting after login
//----------------------------------------------------------------------------
void Database::GetFirstName( int ID )
{
	int exit = sqlite3_open( directory, &DB );
	sql = "SELECT FIRSTNAME FROM ZOO WHERE ID = '" + std::to_string( ID ) + "';";
	sqlite3_exec( DB, sql.c_str(), Callback, NULL, NULL );
	sqlite3_close( DB );
} // end function Database::GetFirstName()

//----------------------------------------------------------------------------
//! Used to update data given the username, what they want to change, and the
//! new data
//----------------------------------------------------------------------------
void Database::UpdateData( std::string item, std::string data, int ID )
{
	int exit = sqlite3_open( directory, &DB );

	sql = "UPDATE ZOO SET " + item + " = '" + data + "' WHERE ID = '" + std::to_string(ID) + "';";

	exit = sqlite3_exec( DB, sql.c_str(), NULL, 0, &messageError );
	if ( exit != SQLITE_OK )
	{
		std::cerr << "Error Insert\n";
		sqlite3_free( messageError );
	}
	else
	{
		std::cout << item << " successfully updated!\n";
	}
	sqlite3_close( DB );
} // end function Database::UpdateData()

//----------------------------------------------------------------------------
//! Verifies the user's credentials and displays their role
//----------------------------------------------------------------------------
bool Database::VerifyUser( std::string username, std::string password )
{
	struct sqlite3_stmt *selectstmt = NULL;
	bool verified = false;
	int exit = sqlite3_open( directory, &DB );	

	sql = "SELECT ROLE FROM ZOO WHERE USERNAME = '" + username + "' AND PASSWORD = '" + sha256( password) + "'";
	int result = sqlite3_prepare_v2( DB, sql.c_str(), -1, &selectstmt, NULL );

	if ( result == SQLITE_OK )
	{
		if ( sqlite3_step( selectstmt ) == SQLITE_ROW )
		{
			verified = true;
		}
		else
		{
			std::cout << "Username/password incorrect, please try again\n";
			verified = false;
		}
	}
	Database::GetUserID( username );

	sqlite3_finalize(selectstmt);
	sqlite3_close( DB );

	return verified;
} // end function Database::VerifyUser()

//----------------------------------------------------------------------------
//! Gets the user ID when the user logs in
//----------------------------------------------------------------------------
void Database::GetUserID( std::string username )
{
	int exit = sqlite3_open( directory, &DB );

	sql = "SELECT ID FROM ZOO WHERE USERNAME = '" + username + "';";

	sqlite3_exec( DB, sql.c_str(), CallbackID, NULL, NULL );
	sqlite3_close( DB );
} // end function Database::GetUserID()

//----------------------------------------------------------------------------
//! Updates the user's role
//----------------------------------------------------------------------------
void Database::UpdateRole()
{
	std::string newRole;
	std::cout << "Enter your new role\n";
	std::cin.ignore();
	std::getline( std::cin, newRole );
	std::cout << "\n";
	Database::UpdateData( "ROLE", newRole, Validation::GetUserID() );
} // end function Database::UpateRole()

//----------------------------------------------------------------------------
//! Updates the user's email
//----------------------------------------------------------------------------
void Database::UpdateEmail()
{
	std::string newEmail;
	std::cout << "Enter your new email\n";
	std::cin >> newEmail;
	std::cout << "\n";
	Database::UpdateData( "EMAIL", newEmail, Validation::GetUserID() );
} // end function Database::UpdateEmail()

//----------------------------------------------------------------------------
//! Updates the user's password
//----------------------------------------------------------------------------
void Database::UpdatePassword()
{
	std::string newPassword, newPassword2;
	std::cout << "Enter your new password\n";
	std::cin >> newPassword;
	std::cout << "\n";
	std::cout << "Re-enter password\n";
	std::cin >> newPassword2;
	std::cout << "\n";
	while ( newPassword != newPassword2 )
	{
		std::cout << "Your passwords didn't match up, please try again.\n\n";
		std::cout << "Enter a password\n";
		std::cin >> newPassword;
		std::cout << "\n";
		std::cout << "Re-enter password\n";
		std::cin >> newPassword2;
		std::cout << "\n";
	}
	Database::UpdateData( "PASSWORD", sha256(newPassword), Validation::GetUserID() );
} // end function Database::UpdatePassword()

//----------------------------------------------------------------------------
//! Updates the user's username
//----------------------------------------------------------------------------
void Database::UpdateUsername()	
{
	std::string newUsername;
	std::cout << "Enter your new username\n";
	std::cin >> newUsername;
	std::cout << "\n";
	Database::UpdateData( "USERNAME", newUsername, Validation::GetUserID() );
} // end function Database::UpdateUsername()
