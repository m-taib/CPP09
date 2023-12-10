#include "PmergeMe.hpp"
#include <vector>

void    print_elements(std::vector<int>& v)
{
    int		i = -1;
    while (++i < (int)v.size())
    {
        std::cout << v[i] << " ";
    }
}
int     main(int ac, char **av)
{
    std::vector<int> v;
    int     i = 1;

    
    (void)ac;
    while (av[i])
    {
        std::cout << av[i] << " ";
        v.push_back(std::atoi(av[i++]));
    }
    std::cout << std::endl;
    PmergeMe a;

    a.merge_sort(v);
    i = -1;
    std::cout << "sorted : " ;
    while (++i < (int)v.size())
    {
        if (i + 1 == (int)v.size())
            break ;
	    if (v[i] > v[i + 1])
        {
                std::cout << "no" << std::endl;
                print_elements(v);
                return (1);
        }
    }
    std::cout << "yes" << std::endl;
    print_elements(v);
    std::cout << "\nnumber of comparisons : " << a.getComparisonsNum() << std::endl;
}
