#include "Hash.hpp"
#include <iostream>
#include <sstream>
#include "sha256.h"

std::string hashPassword( std::string data )
{
	std::string hashedPassword = sha256( data );

	return hashedPassword;
}
