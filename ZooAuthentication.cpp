//****************************************************************************
// @file ZooAuthentication.cpp : This file includes the main function
//
//****************************************************************************

#include "Menu.hpp"
#include "Validation.hpp"
#include "Database.hpp"

//------------------------------------------------------------------------
// Main function
//------------------------------------------------------------------------
int main()
{
    int attempts = 0;
    bool logOff = false;
    unsigned short int selection = 0;

    // Creates the zoo database if one doesn't exist
    Database::CreateDataBase();

    // limits password attempts to 3
    while ( selection != 3 )
    {
        Menu::DisplayMenu();
        selection = Menu::GetSelection();
        switch (selection)
        {
        case 1:
            while ( !Validation::GetCredentials() )
            {
                attempts++;
                if ( attempts == 3 )
                {
                    std::cout << "Too many failed attempts, goodbye\n";
                    selection = 3;
                    break;
                }
            }

            // Greet the user and display role
            std::cout << "Hello ";
            Database::GetFirstName( Validation::GetUserID() );
            std::cout << "!\n\n";
            Database::GetRole( Validation::GetUserID() );
            std::cout << "\n\n";

            // Resets selection to 0
            selection = 0;

            // user credentials verified, prompt to log off
            while ( selection!= 9 && attempts != 3 )
            {
                Menu::UserDisplay();
                std::cin >> selection;
                switch ( selection )
                {
                // Update role
                case 1:
                    Database::UpdateRole();
                    break;

                // Update email
                case 2:
                    Database::UpdateEmail();
                    break;

                // update username
                case 3:
                    Database::UpdateUsername();
                    break;

                // Update password
                case 4:
                    Database::UpdatePassword();
                    break;

                // Logoff
                case 9:
                    Validation::ClearUserID();
                    break;

                default:
                    Menu::UserDisplay();
                    std::cin >> selection;
                }
            }

            std::cout << "\n";
            attempts = 0;
            
            break;

        // creates new user
        case 2:
            Menu::CreateUser();
            break;

        // exits the program
        case 3:
            std::cout << "Goobye!\n";
            break;
        }
    }

    // clears cin
    std::cin.clear();
    std::cin.ignore( 256, '\n' );
} // end of function main()
