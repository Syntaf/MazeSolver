#ifndef CLS_HPP_
#define CLS_HPP_

#include <iostream>
#include <string>

//If you came here to see what CLS does, I'm sorry
//you had to see this. But it's portable so who cares
inline void CLS()
{
	std::cout << std::string( 100, '\n' );
}

#endif