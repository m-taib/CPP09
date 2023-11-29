#include "BitcoinExchange.hpp"
#include <string>

int     main(int ac ,char **av)
{
    if (ac != 2)
    {
        std::cout << "Invalid number of arguments" << std::endl;
        return (0);
    }

    try 
    {
        BitcoinExchange     database(av[1]);
        
        database.extract_data("data.txt");
    } 
    catch (const char *exp) 
    {
        std::cout << exp << std::endl;   
    }
    return (0);
    //sscanf(const char *, const char *, ...);
    //find for string manipulation
    //substr
}