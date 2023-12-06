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
int     main()
{
    int arr[] = {1466,1308,1263,1494,910,2114,2418,1876,1706,960,310,1655,2843,2199,2005,1785,1214,618,1865,
            2941,1549,1037,297,1100,875, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
 
    std::vector<int> v(arr, arr + n);
    
    PmergeMe a;
   
    // std::cout << "original vector before : " << std::endl;
    
    // while (++i < (int)v.size())
    // {
	//     std::cout << v[i] << " ";
    // }
    // std::cout << std::endl;
    a.merge_sort(v);
     int		i = -1;
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
