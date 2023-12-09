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

    // 20 10 9 1 6 21 13 19 14 5 8 7 3 9 19 2 16 5 21 13 13
    (void)ac;
    while (av[i])
    {
        v.push_back(std::atoi(av[i++]));
    }
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
