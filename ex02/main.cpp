#include "PmergeMe.hpp"
#include <exception>

// Before: 3 5 9 7 4
// After: 3 4 5 7 9
// Time to process a range of 5 elements with std::[..] : 0.00031 us
// Time to process a range of 5 elements with std::[..] : 0.00014 us

int     main(int ac, char **av)
{
    long    start_time;
    long    elapsed_time;

    if (ac < 2)
    { 
        std::cout << "Invalid number of arguments" << std::endl;
        return (0);
    }
    try 
    {
        start_time = gettime();
        vector_implementation(av);
        elapsed_time = gettime();
        std::cout << elapsed_time - start_time << " us" << std::endl;
        start_time = gettime();
        list_implementation(av);
        elapsed_time = gettime();
        std::cout << elapsed_time - start_time << " us" << std::endl;
    }
    catch (const std::exception& exp)
    {
        std::cout << exp.what() << std::endl;
    }
}
