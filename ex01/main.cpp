#include "RPN.hpp"
#include <exception>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Invalid number of arguments" << std::endl;
		return (0);
	} 
	try 
	{
		Rpn 	rpn;
		rpn.stackManip(av[1]);
	} 
	catch (const std::exception& exp) 
	{	
		std::cout << exp.what() << std::endl;
	}
	return (0);
}
